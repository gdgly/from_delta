# -*- coding: utf-8 -*-
"""
Created on Sat Sep  2 20:59:11 2017

@author: fanxu
"""
import numpy as np
import numpy.random as random
import math
from pykalman import KalmanFilter
import matplotlib.pyplot as plt
import pylab as pl
import openpyxl
import matplotlib, sys
from numpy import arange
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
from tkinter import *
from tkinter import ttk
import ast
from PIL import Image, ImageTk
matplotlib.use("TkAgg")

#---------------------------------------------
#initial,only for input=2,output=1
#----------------------------------------------

global f
global dataPlot
#global str_a, str_b, str_c, str_d, str_q, str_r
global str_F, str_H, str_Q, str_R, str_x0, str_N
global str_Qfilter, str_Rfilter,str_x0filter, str_P0filter, str_Nopt
global str_unF, str_start, str_end, str_unQfilter
global y

class SystemModel:
    def __init__(self, F, H, QReal, QFilter, R, x, N):
        self.F = F
        self.H = H
        self.QReal = QReal
        self.QFilter = QFilter
        self.R = R
        self.x = x
        self.N = N

class FilterModel:
    def __init__(self, Qfilter, Rfilter, x0filter, P0filter, Nopt):
        self.QFilter=QFilter
        self.Rfilter=Rfilter
        self.x0filter=x0filter
        self.P0filter=P0filter
        self.Nopt=Nopt

def chooseExcelFile():#y值的读取
    global y
    filename = filedialog.askopenfilename(filetypes=[("Excel格式(.xlsx)","xlsx")])
    wb = openpyxl.load_workbook(filename)
    sheet_names = wb.get_sheet_names()
    sheet = wb.get_sheet_by_name(sheet_names[0])
    y = []
    for row in sheet.rows:
        for cell in row:
            y.append(cell.value)
    print(y)
    
def Kalman(systemModel,smoothingFlag):
    F=systemModel.F
    H=systemModel.H
    QFilter=systemModel.QFilter
    QReal=systemModel.QReal
    R = systemModel.R
    x = systemModel.x
    N = systemModel.N
    nx = max(x.shape)
    ny = min(H.shape)
    Pplus=1000 * np.mat(np.eye(nx))
    xhatplus=x+np.sqrt(np.diag(Pplus).reshape(2,1))
    xArr=np.mat(np.zeros((nx,N)))
    PplusArr=np.zeros((nx,nx,N))
    PminusArr = np.zeros((nx, nx, N))
    xhatminusArr = np.mat(np.zeros((nx, N)))
    xhatplusArr = np.mat(np.zeros((nx, N)))
    xhatplusError = np.mat(np.zeros((nx, N)))
    PKalmanElements = np.mat(np.zeros((nx, N)))
    JArr = np.zeros((nx, nx, N))
    JInvArr = np.zeros((nx, nx, N))
    KArr = np.mat(np.zeros((nx, N)))
    yArr = np.mat(np.zeros((ny, N)))
    FArr = np.zeros((nx, nx, N))
    HArr = np.mat(np.zeros((N, nx)))
    SArr = np.mat(np.zeros((ny, N)))
    MeasResidual = np.mat(np.zeros((ny, N)))
    Inx = np.mat(np.eye(nx))
    for k in range(0, N):
        FArr[:, :, k] = F
        HArr[k, :] = H
        x = F * x + np.sqrt(QReal) * np.random.randn(nx, 1)
        y = H * x + np.sqrt(R) * np.random.randn()
        xArr[:, k] = x
        yArr[:, k] = y
        y=yArr[:, k]
        #Kalman filter
        Pminus=F*Pplus*F.T+QFilter
        K=Pminus*H.T*(H * Pminus * H.T + R).I
        xhatminus = F * xhatplus
        xhatplus = xhatminus + K * (y - H * xhatminus)
        Pplus = Pminus - K * H * Pminus
        
        PminusArr[:, :, k] = Pminus
        PplusArr[:, :, k] = Pplus
        PKalmanElements[0, k] = Pplus[0, 0]
        PKalmanElements[1, k] = Pplus[1, 1]
        xhatminusArr[:, k] = xhatminus
        xhatplusArr[:, k] = xhatplus
        xhatplusError[:, k] = x - xhatplus
        JArr[:, :, k] = Inx - K * H
        JInvArr[:, :, k] =  (Inx - K * H).I
        KArr[:, k] = K
        SArr[:, k] = H * Pminus * H.T + R
        MeasResidual[:, k] = y - H * xhatminus
    
    #Kalman smoother
    xhatSmooth = xhatplus
    PSmooth = Pplus
    xhatSmoothArr = np.mat(np.zeros((nx, N)))
    xhatSmoothError = np.mat(np.zeros((nx, N)))
    xhatSmoothArr[:, N-1] = xhatSmooth
    xhatSmoothError[:, N-1] = xArr[:, N-1] - xhatSmooth
    KSmootherArr = np.zeros((nx, nx, N-1))
    PSmootherElements = np.mat(np.zeros((nx, N)))
    PSmootherElements[:, N-1] = PKalmanElements[:, N-1]
    if smoothingFlag:
        for k in range(N-2 , 0 , -1):
            K = PplusArr[:, :, k] * F.T * np.mat(PminusArr[:, :, k+1]).I
            PSmooth = PplusArr[:, :, k] - K * (PminusArr[:, :, k+1] - PSmooth) * K.T
            xhatSmooth = xhatplusArr[: ,k] + K * (xhatSmooth - xhatminusArr[:, k+1])
            # Save data in arrays
            xhatSmoothArr[: ,k] = xhatSmooth
            xhatSmoothError[:, k] = xArr[:, k] - xhatSmooth
            KSmootherArr[:, :, k] = K
            PSmootherElements[0, k] = PSmooth[0, 0]
            PSmootherElements[1, k] = PSmooth[1, 1]
    return xArr,yArr,xhatplusArr,xhatplusError, xhatSmoothError, PKalmanElements, PSmootherElements, MeasResidual, PminusArr 


def UFIR(systemModel, smoothingFlag, nOpt):
    F = systemModel.F
    H = systemModel.H
    QReal = systemModel.QReal
    R = systemModel.R
    x = systemModel.x
    N = systemModel.N
    nx = max(x.shape)
    ny = min(H.shape)
    if smoothingFlag:
        p = int(nOpt / 2 + 0.5)
        iLowerLimit = max(nOpt + 1, nOpt + p - nx)
        iUpperLimit = min(N - 1, N + nOpt - nx - 1)
        NArr = np.arange(iLowerLimit, N - p, 1)
    else:
        p = 0
        iLowerLimit = nOpt + 2 - nx
        iUpperLimit = min(N - 1, N + nOpt - nx - 1)
        NArr = np.arange(nOpt + 2 - nx, iUpperLimit + 1, 1)
    xArr = np.mat(np.zeros((nx, N)))
    xhatArr = np.mat(np.zeros((nx, N)))
    xhatError = np.mat(np.zeros((nx, N)))
    PElements = np.mat(np.zeros((nx, N)))
    yArr = np.mat(np.zeros((ny, N)))
    FArr = np.zeros((nx, nx, N))
    HArr = np.mat(np.zeros((N, nx)))
    MeasResidual = np.mat(np.zeros((ny, N)))
    Inx = np.mat(np.eye(nx))
    FExpMinusP = F.I ** p
    for k in range(0, N):
        FArr[:, :, k] = F
        HArr[k, :] = H
        x = F * x + np.sqrt(QReal) * np.random.randn(2, 1)
        y = H * x + np.sqrt(R) * np.random.randn()
        xArr[:, k] = x
        yArr[:, k] = y
    Ysm = np.mat(np.zeros((1, nx * ny)))
    FsmT = np.mat(np.zeros((nx, nx ** 2)))
    HsmBar = np.mat(np.zeros((nx * ny, nx ** 2)))
    for i in range(iLowerLimit, iUpperLimit + 1):
        m = i - nOpt + 1
        s = m + nx - 1
        Yindex = nx * ny
        for j in range(m, s + 1):
            Ysm[Yindex-ny+1-1 : Yindex] = yArr[:, j-1].T
            Yindex = Yindex - ny
        for j in range(1, nx + 1):
            temp = Inx
            for iii in range(j - 1, nx - 1):
                temp = temp * FArr[:, :, s - iii - 1]
            FsmT[:, (j - 1) * nx + 1-1 : j * nx] = temp.T
        for iii in range(s, m - 1, -1):
            HsmBar[(s-iii)*ny+1-1 : (s-iii+1)*ny, (s-iii)*nx+1-1 : (s-iii+1)*nx] = HArr[s, :]
        Hsm = HsmBar * FsmT.T
        alpha = Inx
        if p >= nx:
            for iii in range(1, p - nx):
                alpha = alpha * (np.mat(FArr[:, :, s-p+iii - 1]).I)
        else:
            for iii in range(0, nx - 1 - p):
                alpha = alpha * FArr[:, :, s-p-iii - 1]
        xhat = alpha * (Hsm.T * Hsm).I * Hsm.T * Ysm.T
        TempPord = Inx
        for i1 in range(0, nx - 1):
            TempPord = TempPord * FArr[:, : ,s-i1 - 1]
        G = TempPord * (Hsm.T * Hsm).I * TempPord.T
        gamma = Inx
        for i1 in range(0, p + 1):
            gamma = gamma *FArr[:, : ,i-nOpt+nx+1-i1 - 1]
        for el in range(i-nOpt+nx+1,i+1):
            G = (HArr[el-1,:].T * HArr[el-1,:] + (FArr[:,:,el - 1] * G * np.mat(FArr[:, :, el - 1]).T).I).I
            K = FArr[:,:,el-p - 1] * gamma.I * G * HArr[el-1,:].T
            xhat = FArr[:,:,el-p - 1] * xhat + K * (yArr[:,el-1] - HArr[el-1,:] * gamma * xhat)
            if el < i:
                gamma = FArr[:,:,el+1 - 1] * gamma * (np.mat(FArr[:,:,el-p - 1]).I)
        xhatArr[:, i-p-1] = xhat;
        xhatError[:, i-p-1] = xArr[:, i-p-1] - xhat;
        Covariance = R * FExpMinusP * G * FExpMinusP.T;
        PElements[0, i-p-1] = Covariance[0, 0];
        PElements[1, i-p-1] = Covariance[1, 1];
        MeasResidual[:, i-p-1] = yArr[:, i-p-1] - HArr[i-p-1, :] * xhat;
    return xArr,yArr,xhatArr,xhatError, PElements, NArr, MeasResidual


def horizon():
    pass
    return Nopt

def rmse(systemModel,nMonte,Nopt,smoothingFlag):
    N=systemModel.N
    ErrorFilter=np.zeros((nMonte,2,N))
    ErrorSmoother=np.zeros((nMonte,2,N))
    ErrorFIRFilter=np.zeros((nMonte,2,N))
    ErrorFIRSmoother=np.zeros((nMonte,2,N))
    for i in range(0,nMonte):
        print('%d%%'%(100*i/nMonte))
        returnK= Kalman(systemModel,smoothingFlag)
        xhatplusError=np.array(returnK[3])
        xhatSmoothError=np.array(returnK[4])
        PKalman=np.array(returnK[5])
        PSmoother=np.array(returnK[6])
        ErrorFilter[i,:,:]=xhatplusError
        ErrorSmoother[i,:,:]=xhatSmoothError
        
        #UFIR filter
        resultFF=UFIR(systemModel, False, Nopt)
        xhatFIRError=np.array(resultFF[3])
        ErrorFIRFilter[i,:,:]=xhatFIRError
        
        #UFIR smoother
        if smoothingFlag:
            resultFS=UFIR(systemModel, True, Nopt)
            xhatFIRError=np.array(resultFF[3])
            ErrorFIRSmoother[i,:,:]=xhatFIRError
    
    
    nMonte=max(nMonte,2)
    PKalman=np.sqrt(PKalman)
    ErrorFilter=np.sum(np.multiply(ErrorFilter,ErrorFilter),axis=0)
    ErrorFilter=np.squeeze(np.sqrt(ErrorFilter/(nMonte-1)))

    PSmoother=np.sqrt(PSmoother)
    ErrorSmoother=np.sum(np.multiply(ErrorSmoother,ErrorSmoother),axis=0)
    ErrorSmoother=np.squeeze(np.sqrt(ErrorSmoother/(nMonte-1)))
    
#    for i in range(0,nMonte):
#        resultFF=UFIR(systemModel, False, Nopt)
#        xhatFIRError=np.array(resultFF[3])
#        ErrorFIRFilter[i,:,:]=xhatFIRError
    PFIRFilter=np.sqrt(np.array(resultFF[5]))
    ErrorFIRFilter=np.sum(np.multiply(ErrorFIRFilter,ErrorFIRFilter),axis=0)
    ErrorFIRFilter=np.squeeze(np.sqrt(ErrorFIRFilter/(nMonte-1)))

#    if smoothingFlag:
#        for i in range(0,nMonte):
#            resultFS=UFIR(systemModel, True, Nopt)
#            xhatFIRError=np.array(resultFF[3])
#            ErrorFIRSmoother[i,:,:]=xhatFIRError
#        PFIRSmoother=np.sqrt(np.array(resultFS[5]))
#        ErrorFIRSmoother=np.sum(np.multiply(ErrorFIRSmoother,ErrorFIRSmoother),axis=0)
#        ErrorFIRSmoother=np.squeeze(np.sqrt(ErrorFIRSmoother/(nMonte-1)))
    if smoothingFlag:
        PFIRSmoother=np.sqrt(np.array(resultFS[5]))
        ErrorFIRSmoother=np.sum(np.multiply(ErrorFIRSmoother,ErrorFIRSmoother),axis=0)
        ErrorFIRSmoother=np.squeeze(np.sqrt(ErrorFIRSmoother/(nMonte-1)))
    return ErrorFilter, ErrorSmoother, ErrorFIRFilter, ErrorFIRSmoother



def Initial():
    QFactorArr = 1
    Nopt = 12
    F = np.mat([[1, 0.1], [0, 1]])
    H = np.mat([1, 0]);
    QReal = np.mat([[0, 0], [0, 1**2]])
    QFilter = QFactorArr*QReal;
    R = 1**2#0.833**2
    x = np.mat([[1], [1]])
    N = 500
    nMonte=20
    systemModel = SystemModel(F, H, QReal, QFilter, R, x, N)


#    resultF=UFIR(systemModel, False, Nopt)
#    resultK=Kalman(systemModel,False)
#    x=np.array(resultF[0])
#    y=np.array(resultF[1])
#    xhat=np.array(resultF[2])
#    xhaterror=np.array(resultF[3])
#    xhatKerror=np.array(resultK[3])
    
    
    resultrmse=rmse(systemModel,nMonte,Nopt,False)
    xhaterror=resultrmse[2]
    xhatKerror=resultrmse[0]
    
    return xhaterror, xhatKerror,systemModel,Nopt


(xhaterror, xhatKerror,systemModel,Nopt)=Initial()
N=systemModel.N




master = Tk()
master.title('Kalman Filter')
f = Figure(figsize=(7,4), dpi=100)
a = f.add_subplot(1,1,1)
a.plot(xhaterror[0,:],label='Ffilter',color='black',linewidth=2)
a.plot(xhatKerror[0,:],label='Kfilter')
a.legend(loc = 'upper right')
a.set_xlabel('Time')
a.grid()
a.set_xlim(0,N-1)
a.set_title('Kalman & Measurement')
dataPlot = FigureCanvasTkAgg(f, master=master)
dataPlot.show()
dataPlot.get_tk_widget().pack(side=TOP, fill=BOTH, expand=1)
#-------------------------------------------------------------------------------
master.mainloop()












