# -*- coding: utf-8 -*-
"""
Created on Sat Sep  2 20:59:11 2017

@author: fanxu
"""
import numpy as np
import numpy.random as random
import math
import matplotlib.pyplot as plt
import pylab as pl
import openpyxl
import matplotlib, sys
from numpy import arange
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
import ast
from PIL import Image, ImageTk
matplotlib.use("TkAgg")

#---------------------------------------------
#only for input=2,output=1
#----------------------------------------------
global str_F, str_H, str_QReal, str_R, str_x0, str_N
global str_Qfilter, str_Rfilter,str_x0filter, str_P0filter, str_Nopt
global str_unF, str_unQ, str_start, str_end
global str_NN,str_Nmin,str_Nmax
global y,nMonte
global Nmin,Nmax


class SystemModel:
    def __init__(self, F, H, QReal,R, x0, N):
        self.F = F
        self.H = H
        self.QReal = QReal
        self.R = R
        self.x0 = x0
        self.N = N

class FilterModel:
    def __init__(self, Qfilter, Rfilter, x0filter, P0filter, Nopt):
        self.Qfilter=Qfilter
        self.Rfilter=Rfilter
        self.x0filter=x0filter
        self.P0filter=P0filter
        self.Nopt=Nopt

class unSystemModel:
    def __init__(self,unF, unQ, start, end, unFflag, unQflag):
        self.unFflag=unFflag
        self.unQflag=unQflag
        self.start=start
        self.end=end
        self.unF=unF
        self.unQ=unQ


#y值的读取
def chooseExcelFile():
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
    
def Kalman(systemModel,filterModel,unsystemModel,smoothingFlag):
    F=systemModel.F
    H=systemModel.H
    QFilter=filterModel.Qfilter
    QReal=systemModel.QReal
    R = systemModel.R
    x = systemModel.x0
    N = systemModel.N
    nx = max(x.shape)
    ny = min(H.shape)
    Pplus=filterModel.P0filter
    xhatplus=filterModel.x0filter
    
    start_time=unsystemModel.start
    end_time=unsystemModel.end
    unF=unsystemModel.unF
    unQ=unsystemModel.unQ
    unFflag=unsystemModel.unFflag
    unQflag=unsystemModel.unQflag 
    
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
        
        if unFflag==1 and unQflag==0:
            if start_time<=k and k<=end_time:
                x = unF * x + np.sqrt(QReal) * np.random.randn(nx, 1)
            else:
                x = F * x + np.sqrt(QReal) * np.random.randn(nx, 1)
        if unFflag==0 and unQflag==1:
            if start_time<=k and k<=end_time:
                x = F * x + np.sqrt(unQ) * np.random.randn(nx, 1)
            else:
                x = F * x + np.sqrt(QReal) * np.random.randn(nx, 1)
        if unFflag==0 and unQflag==0:
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


def UFIR(systemModel,filterModel,unsystemModel,smoothingFlag):
    F = systemModel.F
    H = systemModel.H
    QReal = systemModel.QReal
    R = systemModel.R
    x = systemModel.x0
    N = systemModel.N
    nx = max(x.shape)
    ny = min(H.shape)
    nOpt=filterModel.Nopt

    start_time=unsystemModel.start
    end_time=unsystemModel.end
    unF=unsystemModel.unF
    unQ=unsystemModel.unQ
    unFflag=unsystemModel.unFflag
    unQflag=unsystemModel.unQflag 
    
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
    
#    print(unF, unQ, start_time, end_time, unFflag, unQflag)
    for k in range(0, N):
        FArr[:, :, k] = F
        HArr[k, :] = H
        if unFflag==1 and unQflag==0:
            if start_time<=k and k<=end_time:
                x = unF * x + np.sqrt(QReal) * np.random.randn(nx, 1)
            else:
                x = F * x + np.sqrt(QReal) * np.random.randn(nx, 1)
        if unFflag==0 and unQflag==1:
            if start_time<=k and k<=end_time:
                x = F * x + np.sqrt(unQ) * np.random.randn(nx, 1)
            else:
                x = F * x + np.sqrt(QReal) * np.random.randn(nx, 1)
        if unFflag==0 and unQflag==0:
            x = F * x + np.sqrt(QReal) * np.random.randn(nx, 1)
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
                alpha = alpha * FArr[:, :, s-p+iii - 1].I
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
        Covariance = R * FExpMinusP * G * FExpMinusP.T
        PElements[0, i-p-1] = Covariance[0, 0]
        PElements[1, i-p-1] = Covariance[1, 1]
        MeasResidual[:, i-p-1] = yArr[:, i-p-1] - HArr[i-p-1, :] * xhat
    return xArr,yArr,xhatArr,xhatError, PElements, NArr, MeasResidual


def Initial():
    QFactorArr = 1
    nMonte=20
    
    F = np.mat([[0.995,0.098], [-0.098,0.995]])
    H = np.mat([1, 0]);
    QReal = np.mat([[0.01,0.1], [0.1,1]])
    R = 10
    x0 = np.mat([[1], [0.1]])
    N = 500
#    F=np.mat(ast.literal_eval(str_F.get()))
#    H=np.mat(ast.literal_eval(str_H.get()))
#    QReal=np.mat(ast.literal_eval(str_Q.get()))
#    R=ast.literal_eval(str_R.get())
#    x0=np.mat(ast.literal_eval(str_x0.get()))
#    N=ast.literal_eval(str_N.get())

    nx = max(x0.shape)
    Qfilter = QFactorArr*QReal
    Rfilter=10
    x0filter=np.mat([[1], [1]])
    P0filter=np.mat(np.eye(nx))
#    Nopt =14
#    Qfilter=np.mat(ast.literal_eval(str_Qfilter.get()))
#    Rfilter=ast.literal_eval(str_Rfilter.get())
#    x0filter=np.mat(ast.literal_eval(str_x0filter.get()))
#    P0filter=np.mat(ast.literal_eval(str_P0filter.get()))
    if int(chVarUF.get())==1:
        Nopt=ast.literal_eval(str_Nopt.get())
    else:
        Nopt=1



#    unF=np.mat(ast.literal_eval(str_unF.get()))
#    unQ=np.mat(ast.literal_eval(str_unQ.get()))
#    start=ast.literal_eval(str_start.get())
#    end=ast.literal_eval(str_end.get())
    unFflag=chVarunF.get()
    unQflag=chVarnoise.get()
    print(unFflag,unQflag)
    if unFflag or unQflag==1:
        start=150
        end=300
    if unFflag==1 and unQflag==0:
        unF=np.mat([[0.995,0.098+0.4], [-0.098+0.4,0.995]])
        unQ=QReal
    if unFflag==0 and unQflag==1:
        unF=F
        unQ=100*QReal
    if unFflag==0 and unQflag==0:
        start=150
        end=300
        unF=F
        unQ=QReal

    systemModel = SystemModel(F, H, QReal,R, x0, N)
    filterModel = FilterModel(Qfilter, Rfilter, x0filter, P0filter, Nopt)
    unsystemModel=unSystemModel(unF, unQ, start, end, unFflag, unQflag)
    
#    nx = max(F.shape)
#    ny = min(H.shape)
#    xArr=np.mat(np.zeros((nx, N)))
#    yArr=np.mat(np.zeros((ny, N)))
#    for k in range(0,N):
#        x = F * x + np.sqrt(QReal) * np.random.randn(nx, 1)
#        y = H * x + np.sqrt(R) * np.random.randn()
#        xArr[:, k] = x
#        yArr[:, k] = y
    return systemModel,filterModel,unsystemModel,nMonte



def draw(flag):#画图
    global nMonte
    (systemModel,filterModel,unsystemModel,nMonte)=Initial()
    N=systemModel.N
    Nopt=filterModel.Nopt
    #进度条
    p1['value']=100*1/(nMonte+2)
    choice_frame.update()
    
    if chVarUF.get()==1:
        resultF=UFIR(systemModel,filterModel, unsystemModel,False)
        x=np.array(resultF[0])
        y=np.array(resultF[1])
        xhat=np.array(resultF[2])
        xhatFerror=np.array(resultF[3])
    
    if chVarKal.get()==1:
        resultK=Kalman(systemModel,filterModel,unsystemModel,False)
        xhatKerror=np.array(resultK[3])

############RMSE#####################
    smoothingFlag=False
    ErrorFilter=np.zeros((nMonte,2,N))
    ErrorSmoother=np.zeros((nMonte,2,N))
    ErrorFIRFilter=np.zeros((nMonte,2,N))
    ErrorFIRSmoother=np.zeros((nMonte,2,N))
    for i in range(0,nMonte):
        print(i)
        #进度条
        p1['value']=100*(i+2)/(nMonte+2)
        choice_frame.update()
        
        if chVarKal.get()==1:
            #Kalman filter
            resultK= Kalman(systemModel,filterModel,unsystemModel,smoothingFlag)
            xhatplusError=np.array(resultK[3])
            xhatSmoothError=np.array(resultK[4])
            PKalman=np.array(resultK[5])
            PSmoother=np.array(resultK[6])
            ErrorFilter[i,:,:]=xhatplusError
            ErrorSmoother[i,:,:]=xhatSmoothError
        
        if chVarUF.get()==1:
            #UFIR filter
            resultF=UFIR(systemModel, filterModel,unsystemModel,False)
            xhatFIRError=np.array(resultF[3])
            ErrorFIRFilter[i,:,:]=xhatFIRError
        
        #UFIR smoother
        if smoothingFlag:
            resultFS=UFIR(systemModel, filterModel,unsystemModel,True)
            xhatFIRError=np.array(resultF[3])
            ErrorFIRSmoother[i,:,:]=xhatFIRError
    
    if chVarKal.get()==1:
        nMonte=max(nMonte,2)
        PKalman=np.sqrt(PKalman)
        ErrorFilter=np.sum(np.multiply(ErrorFilter,ErrorFilter),axis=0)
        ErrorFilter=np.squeeze(np.sqrt(ErrorFilter/(nMonte-1)))
    
        PSmoother=np.sqrt(PSmoother)
        ErrorSmoother=np.sum(np.multiply(ErrorSmoother,ErrorSmoother),axis=0)
        ErrorSmoother=np.squeeze(np.sqrt(ErrorSmoother/(nMonte-1)))
    
    if chVarUF.get()==1:
        PFIRFilter=np.sqrt(np.array(resultF[5]))
        ErrorFIRFilter=np.sum(np.multiply(ErrorFIRFilter,ErrorFIRFilter),axis=0)
        ErrorFIRFilter=np.squeeze(np.sqrt(ErrorFIRFilter/(nMonte-1)))

    if smoothingFlag:
        PFIRSmoother=np.sqrt(np.array(resultFS[5]))
        ErrorFIRSmoother=np.sum(np.multiply(ErrorFIRSmoother,ErrorFIRSmoother),axis=0)
        ErrorFIRSmoother=np.squeeze(np.sqrt(ErrorFIRSmoother/(nMonte-1)))
#    resultrmse=rmse(systemModel,filterModel,unsystemModel,nMonte,False)
    xhatFrmse=ErrorFIRFilter
    xhatKrmse=ErrorFilter
##################################################
    f.clf()
    if flag==1:
        a = f.add_subplot(2,1,1)
        #a.plot(xhat[0,:],label='filter',color='black',linewidth=2)
        #a.plot(y[0,:],label='measurement')
        #a.plot(x[0,:],label='true')
        #a.plot(y[0,:]-x[0,:],label='measurement')
        a.plot(xhatFerror[0,:],label='Ffilter',color='black',linewidth=0.5)
        a.plot(xhatKerror[0,:],label='Kfilter',linewidth=0.5)
        a.legend(loc = 'upper right')
        a.set_xlabel('Time')
        a.set_ylabel('Error')
        a.grid()
        a.set_xlim(0,N-1)
#        a.set_title('Kalman & UFIR')
        
        b=f.add_subplot(2,1,2)
        b.plot(xhatFerror[1,:],label='Ffilter',color='black',linewidth=0.5)
        b.plot(xhatKerror[1,:],label='Kfilter',linewidth=0.5)
        b.legend(loc = 'upper right')
        b.set_xlabel('Time')
        b.set_ylabel('Error')
        b.grid()
        b.set_xlim(0,N-1)
        f_dataPlot.show()
    elif flag==2:
        a = f.add_subplot(2,1,1)
        a.plot(xhatKerror[0,:],label='Kfilter',linewidth=0.5)
        a.legend(loc = 'upper right')
        a.set_xlabel('Time')
        a.set_ylabel('Error')
        a.grid()
        a.set_xlim(0,N-1)
#        a.set_title('Kalman')
        
        b=f.add_subplot(2,1,2)
        b.plot(xhatKerror[1,:],label='Kfilter',linewidth=0.5)
        b.legend(loc = 'upper right')
        b.set_xlabel('Time')
        b.set_ylabel('Error')
        b.grid()
        b.set_xlim(0,N-1)
        f_dataPlot.show()
    elif flag==3:
        a = f.add_subplot(2,1,1)
        a.plot(xhatFerror[0,:],label='Ffilter',color='black',linewidth=0.5)
        a.legend(loc = 'upper right')
        a.set_xlabel('Time')
        a.set_ylabel('Error')
        a.grid()
        a.set_xlim(0,N-1)
#        a.set_title('UFIR')
        
        b=f.add_subplot(2,1,2)
        b.plot(xhatFerror[1,:],label='Ffilter',color='black',linewidth=1)
        b.legend(loc = 'upper right')
        b.set_xlabel('Time')
        b.set_ylabel('Error')
        b.grid()
        b.set_xlim(0,N-1)
        f_dataPlot.show()
    
    g.clf()
    if flag==1:
        a = g.add_subplot(2,1,1)
        #a.plot(xhat[0,:],label='filter',color='black',linewidth=2)
        #a.plot(y[0,:],label='measurement')
        #a.plot(x[0,:],label='true')
        #a.plot(y[0,:]-x[0,:],label='measurement')
        a.plot(xhatFrmse[0,:],label='Ffilter',color='black',linewidth=0.5)
        a.plot(xhatKrmse[0,:],label='Kfilter',linewidth=0.5)
        a.legend(loc = 'upper right')
        a.set_xlabel('Time')
        a.set_ylabel('RMSEs')
        a.grid()
        a.set_xlim(0,N-1)
#        a.set_title('Kalman & UFIR')
        
        b=g.add_subplot(2,1,2)
        b.plot(xhatFrmse[1,:],label='Ffilter',color='black',linewidth=0.5)
        b.plot(xhatKrmse[1,:],label='Kfilter',linewidth=0.5)
        b.legend(loc = 'upper right')
        b.set_xlabel('Time')
        b.set_ylabel('RMSEs')
        b.grid()
        b.set_xlim(0,N-1)
        g_dataPlot.show()
    elif flag==2:
        a = g.add_subplot(2,1,1)
        a.plot(xhatKrmse[0,:],label='Kfilter',linewidth=0.5)
        a.legend(loc = 'upper right')
        a.set_xlabel('Time')
        a.set_ylabel('RMSEs')
        a.grid()
        a.set_xlim(0,N-1)
#        a.set_title('Kalman')
        
        b=g.add_subplot(2,1,2)
        b.plot(xhatKrmse[1,:],label='Kfilter',linewidth=0.5)
        b.legend(loc = 'upper right')
        b.set_xlabel('Time')
        b.set_ylabel('RMSEs')
        b.grid()
        b.set_xlim(0,N-1)
        g_dataPlot.show()
    elif flag==3:
        a = g.add_subplot(2,1,1)
        a.plot(xhatFrmse[0,:],label='Ffilter',color='black',linewidth=0.5)
        a.legend(loc = 'upper right')
        a.set_xlabel('Time')
        a.set_ylabel('RMSEs')
        a.grid()
        a.set_xlim(0,N-1)
#        a.set_title('UFIR')
        
        b=g.add_subplot(2,1,2)
        b.plot(xhatFrmse[1,:],label='Ffilter',color='black',linewidth=1)
        b.legend(loc = 'upper right')
        b.set_xlabel('Time')
        b.set_ylabel('RMSEs')
        b.grid()
        b.set_xlim(0,N-1)
        g_dataPlot.show()


def main():
    if int(chVarKal.get())==1 and int(chVarUF.get())==1:
        draw(1)
    elif int(chVarKal.get())==1 and int(chVarUF.get())==0:
        draw(2)
    elif int(chVarKal.get())==0 and int(chVarUF.get())==1:
        draw(3)
    elif int(chVarKal.get())==0 and int(chVarUF.get())==0:
        messagebox.showwarning("Error", "Please select filter method")

    #进度条100%
    p1['value']=100
    choice_frame.update()



#对一个pil_image对象进行缩放，让它在一个矩形框内，还能保持比例 
def resize(w, h, w_box, h_box, pil_image):
  f1 = 1.0*w_box/w
  f2 = 1.0*h_box/h  
  factor = min([f1, f2])  
  width = int(w*factor)  
  height = int(h*factor)  
  return pil_image.resize((width, height), Image.ANTIALIAS)  


# Main window
master = Tk()
master.resizable(False,False) 
master.title('Estimation Simulation')

############################################################
#------------------------模型建立------------------------#
############################################################
#model_frame=Frame(master)
model_frame=LabelFrame(master,text='Model Parameters',fg='red',padx=0,pady=0)
model_frame.grid(column=0,row=0,sticky=N+S)

#label1=Label(model_frame,text='Model Parameters',font=('Times'))
#label1.grid(column=0, columnspan=3, row=0, rowspan=1)

label_F = Label(model_frame, text='Transition matrix F=')
label_F.grid(column=0, columnspan=1, row=0, rowspan=1,sticky=E)
label_H = Label(model_frame, text='Observation matrix H=')
label_H.grid(column=0, columnspan=1, row=1, rowspan=1,sticky=E)
label_Q = Label(model_frame, text='State noise variance Q=')
label_Q.grid(column=0, columnspan=1, row=2, rowspan=1,sticky=E)
label_R = Label(model_frame, text='Observation\nnoise variance R=')
label_R.grid(column=0, columnspan=1, row=3, rowspan=1,sticky=E)
label_N = Label(model_frame, text='Simulation interval N=')
label_N.grid(column=0, columnspan=1, row=4, rowspan=1,sticky=E)
label_x0 = Label(model_frame, text='Initial state x0=')
label_x0.grid(column=0, columnspan=1, row=5, rowspan=1,sticky=E)
label_y = Label(model_frame, text='Observation y\n(cannot use now)=',fg='gray')
label_y.grid(column=0, columnspan=1, row=6, rowspan=1,sticky=E)

label_remark=Label(model_frame,text='Remarks:',fg='blue',
                  font=('Times'))
label_remark.grid(column=0, columnspan=3, row=7, rowspan=1)
label_model=Label(model_frame,text='状态空间模型：')
label_model.grid(column=0, columnspan=1, row=8, rowspan=1,sticky=E)
label_matrix=Label(model_frame,text='矩阵输入方式：')
label_matrix.grid(column=0, columnspan=1, row=9, rowspan=1,sticky=E)

str_F = StringVar()
entry_F = Entry(model_frame,textvariable = str_F)
entry_F.grid(column=1, columnspan=2, row=0, rowspan=1)
str_H = StringVar()
entry_H = Entry(model_frame, textvariable = str_H)
entry_H.grid(column=1, columnspan=2, row=1, rowspan=1)
str_Q = StringVar()
entry_Q = Entry(model_frame, textvariable = str_Q)
entry_Q.grid(column=1, columnspan=2, row=2, rowspan=1)
str_R = StringVar()
entry_R = Entry(model_frame, textvariable = str_R)
entry_R.grid(column=1, columnspan=2, row=3, rowspan=1)
str_N = StringVar()
entry_N = Entry(model_frame, textvariable = str_N)
entry_N.grid(column=1, columnspan=2, row=4, rowspan=1)
str_x0 = StringVar()
entry_x0 = Entry(model_frame, textvariable = str_x0)
entry_x0.grid(column=1, columnspan=2, row=5, rowspan=1)

button_import = Button(model_frame, text='Import',fg='gray', command = chooseExcelFile,state='disabled')
button_import.grid(column=1, columnspan=2, row=6, rowspan=1, sticky=E+W)


#canvas=Canvas(model_frame,width=150,height=200)
#canvas.grid(column=1,row=7)
#canvas.create_text(50,40,text='Remarks:',fill='blue',
#                   font=('Times',12))

image_model=Image.open('fig1.emf')
w,h=image_model.size
image_model_resized=resize(w,h,100,100,image_model)
tk_image_model=ImageTk.PhotoImage(image_model_resized)

image_matrix=Image.open('fig2.emf')
w,h=image_matrix.size
image_matirx_resized=resize(w,h,120,100,image_matrix)
tk_image_matrix=ImageTk.PhotoImage(image_matirx_resized)

#canvas.create_image(10,70,anchor=NW,image=tk_image_model)
#canvas.create_image(10,120,anchor=NW,image=tk_image_matrix)

label_imagemodel=Label(model_frame,image=tk_image_model)
label_imagemodel.grid(column=1, columnspan=2, row=8, rowspan=1,sticky=W)

label_imagematirx=Label(model_frame,image=tk_image_matrix)
label_imagematirx.grid(column=1, columnspan=2, row=9, rowspan=1,sticky=W)


############################################################
#------------------------滤波参数设置------------------------#
############################################################
#filter_frame=Frame(master)
filter_frame=LabelFrame(master,text='Filter Parameters',fg='red',padx=0,pady=0)
filter_frame.grid(column=1,row=0,sticky=N+S)

#label2=Label(filter_frame,text='Filter Parameters',font=('Times'))
#label2.grid(column=0, columnspan=3, row=0, rowspan=1)

label_Qfilter = Label(filter_frame, text='Filter Q=')
label_Qfilter.grid(column=0, columnspan=1, row=0, rowspan=1,sticky=E)
label_Rfilter = Label(filter_frame, text='Filter R=')
label_Rfilter.grid(column=0, columnspan=1, row=1, rowspan=1,sticky=E)
label_x0filter = Label(filter_frame, text='Filter x0=')
label_x0filter.grid(column=0, columnspan=1, row=2, rowspan=1,sticky=E)
label_P0filter = Label(filter_frame, text='Filter initial\nvariance P0=')
label_P0filter.grid(column=0, columnspan=1, row=3, rowspan=1,sticky=E)


def window_Nopt():
    def horizon():
        (systemModel,filterModel,unsystemModel,nMonte)=Initial()
#        Nmin=ast.literal_eval(str_Nmin.get())
#        Nmax=ast.literal_eval(str_Nmax.get())
#        print(type(Nmin),type(Nmax))
#        NoptArr=arange(Nmin,Nmax+1)
        NoptArr=arange(3,29+1)
        RMSMeasResidual=np.mat(np.zeros((1,len(NoptArr))))
        RMSEstError=np.mat(np.zeros((1,len(NoptArr))))
        for i in range(0,len(NoptArr)):
            filterModel.Nopt=NoptArr[i]
            systemModel.N=5000
    #        systemModel.R=0.833**2
    #        systemModel.QReal=np.mat([[0, 0], [0, 1**2]])
            print(filterModel.Nopt)
            result_horizon=UFIR(systemModel,filterModel,unsystemModel,False)
            NArr=result_horizon[5]
            xhatError=result_horizon[3]
            MeasResidual=result_horizon[6][:,NArr[0]:NArr[-1]]
            RMSMeasResidual[:,i]=np.sqrt(np.sum(np.multiply(MeasResidual,MeasResidual))/MeasResidual.size)
            RMSEstError[:,i]=np.sqrt(np.linalg.norm(xhatError,'fro')/(xhatError.size))
            
            p2['value']=100*i/len(NoptArr)
            choice_frame.update()
        RMSMeasResDeriv=(RMSMeasResidual[:,-(RMSMeasResidual.size)+2:]-RMSMeasResidual[:,0:-1-1])/2
        a=np.array(RMSMeasResDeriv)
        b=np.array(RMSEstError)
        i=np.argmin(a)
        Nopt_com=NoptArr[i+1]
        label_NoptValue['text']=Nopt_com
        label_NoptValue['text']=NoptArr[np.argmin(b)+1]
    
        figure_nopt.clf()
        fignopt=figure_nopt.add_subplot(111)
#        fignopt.plot(NoptArr[1:-1],a[0,:],label='Derivate of V(N)')
        fignopt.plot(NoptArr[1:-1],b[0,1:-1],label='RMS Estimation Error')
        fignopt.legend(loc = 'upper right')
        fignopt.set_xlabel('horizon length N')
        fignopt.grid()
        
        canvas.show()
        
        p2['value']=100
        choice_frame.update()
        return Nopt_com
    
    
    master2=Tk()
    master2.title('Optimal horizon computing')
    master2.resizable(False,False) 
################参数设置#####################################
    Nopt_parameter_frame=LabelFrame(master2,text='Necessary Parameter',fg='red',padx=0,pady=0)
    Nopt_parameter_frame.grid(column=0,row=0,sticky=N+S)
    
    label_Nopt_N=Label(Nopt_parameter_frame,text='Simulation\ninterval N=')
    label_Nopt_N.grid(column=0, columnspan=1, row=0, rowspan=1,sticky=E)
    label_Nopt_Nmin=Label(Nopt_parameter_frame,text='Minimum\nfilter horizon=')
    label_Nopt_Nmin.grid(column=0, columnspan=1, row=1, rowspan=1,sticky=E)
    label_Nopt_Nmax=Label(Nopt_parameter_frame,text='Maximum\nfilter horizon=')
    label_Nopt_Nmax.grid(column=0, columnspan=1, row=2, rowspan=1,sticky=E)
    label_Nopt=Label(Nopt_parameter_frame,text='Optimal horizon=')
    label_Nopt.grid(column=0,columnspan=1,row=5,rowspan=1,sticky=E)
    
    str_NN = StringVar()
    entry_Nopt_N = Entry(Nopt_parameter_frame, textvariable =str_NN ,state='normal',width = 10)
    entry_Nopt_N.grid(column=1, columnspan=1, row=0, rowspan=1,padx=5,sticky=W)
    str_Nmin = IntVar()
    entry_Nopt_Nmin = Entry(Nopt_parameter_frame, textvariable = str_Nmin,state='normal',width = 10)
    entry_Nopt_Nmin.grid(column=1, columnspan=1, row=1, rowspan=1,padx=5,sticky=W)    
    str_Nmax = IntVar()
    entry_Nopt_Nmax = Entry(Nopt_parameter_frame, textvariable = str_Nmax,state='normal',width = 10)
    entry_Nopt_Nmax.grid(column=1, columnspan=1, row=2, rowspan=1,padx=5,sticky=W)

#    NoptValue=12
    label_NoptValue=Label(Nopt_parameter_frame,text=0,fg='blue',font=('Times',15,'bold'))
    label_NoptValue.grid(column=1, columnspan=1, row=5, rowspan=1,sticky=W)
    #进度条组件
    p2 = ttk.Progressbar(Nopt_parameter_frame,  mode="determinate", orient=HORIZONTAL)
    p2.grid(row=4,column=0,columnspan=2,sticky=E+W,padx=5,pady=5)
    p2["maximum"] = 100
    p2["value"] = 0


    
    Nopt_run=Button(Nopt_parameter_frame,text='Run',command=lambda:horizon())
    Nopt_run.grid(column=0,columnspan=2,row=3,padx=5,sticky=W+E)

    label_Nopt_remark=Label(Nopt_parameter_frame,text='在此之前请务必将\nModel Parameters栏填写完整',fg='red')
    label_Nopt_remark.grid(column=0,columnspan=2,row=6,padx=5,sticky=W+E)
#################Figure################
    Nopt_figure_frame=LabelFrame(master2,text='Figure',fg='red',padx=0,pady=0)
    Nopt_figure_frame.grid(column=1,row=0,sticky=N+S)
    
    figure_nopt = Figure(figsize=(4,3), dpi=100)
    canvas = FigureCanvasTkAgg(figure_nopt,Nopt_figure_frame)
    canvas.get_tk_widget().pack(anchor = E , expand=1)

    
    

    

button_Nopt=Button(filter_frame, text='Optimal horizon=',command=window_Nopt,state='disabled')
button_Nopt.grid(column=0, columnspan=1, row=4, rowspan=1,sticky=E)
#label_Nopt = Label(filter_frame, text='Optimal horizon=')
#label_Nopt.grid(column=0, columnspan=1, row=4, rowspan=1,sticky=E)


def checkKal():
    if not chVarKal.get():
#        entry.configure(state = 'disabled')
        entry_Qfilter['state']='disabled'
        entry_Rfilter['state']='disabled'
        entry_x0filter['state']='disabled'
        entry_P0filter['state']='disabled'
    else:
#        entry.configure(state = 'normal')
        entry_Qfilter['state']='normal'
        entry_Rfilter['state']='normal'
        entry_x0filter['state']='normal'
        entry_P0filter['state']='normal'

def checkUF():
    if not chVarUF.get():
        entry_Nopt['state']='disabled'
        button_Nopt['state']='disabled'
    else:
        entry_Nopt['state']='normal'
        button_Nopt['state']='normal'

str_Qfilter = StringVar()
entry_Qfilter = Entry(filter_frame, textvariable = str_Qfilter,state='disabled')
entry_Qfilter.grid(column=1, columnspan=2, row=0, rowspan=1)
str_Rfilter = StringVar()
entry_Rfilter = Entry(filter_frame, textvariable = str_Rfilter,state='disabled')
entry_Rfilter.grid(column=1, columnspan=2, row=1, rowspan=1)
str_x0filter = StringVar()
entry_x0filter = Entry(filter_frame, textvariable = str_x0filter,state='disabled')
entry_x0filter.grid(column=1, columnspan=2, row=2, rowspan=1)
str_P0filter = StringVar()
entry_P0filter = Entry(filter_frame, textvariable = str_P0filter,state='disabled')
entry_P0filter.grid(column=1, columnspan=2, row=3, rowspan=1)

str_Nopt = StringVar()
entry_Nopt = Entry(filter_frame, textvariable = str_Nopt,state='disabled')
entry_Nopt.grid(column=1, columnspan=2, row=4, rowspan=1)

#uncertain condition
def checkunF():
    if chVarunF.get()==1 or chVarnoise.get()==1:
        entry_start['state']='normal'
        entry_end['state']='normal'
    if not chVarunF.get():
        entry_unF['state']='disabled'
        entry_start['state']='disabled'
        entry_end['state']='disabled'
    else:
        entry_unF['state']='normal'
    if chVarnoise.get()==1:
        if chVarunF.get()==1:
            messagebox.showwarning("Error", "Select one uncertain case only")
            checkunF.deselect()
            entry_unF['state']='disabled'

def checknoise():
    if chVarunF.get()==1 or chVarnoise.get()==1:
        entry_start['state']='normal'
        entry_end['state']='normal'
    if not chVarnoise.get():
        entry_unQ['state']='disabled'
        entry_start['state']='disabled'
        entry_end['state']='disabled'
    else:
        entry_unQ['state']='normal'
    if chVarunF.get()==1:
        if chVarnoise.get()==1:
            messagebox.showwarning("Error", "Select one uncertain case only")
            checknoise.deselect()
            entry_unQ['state']='disabled'

label_uncer=Label(filter_frame,text='Uncertainty Cases',fg='blue',
                  font=('Times'))
label_uncer.grid(column=0,columnspan=3,row=5)

chVarunF=IntVar()
checkunF=Checkbutton(filter_frame,text='Model mismatch',
                     variable=chVarunF,command=checkunF)
checkunF.deselect()
checkunF.grid(column=0, columnspan=2, row=6, rowspan=1,sticky=W,padx=20)

chVarnoise=IntVar()
checknoise=Checkbutton(filter_frame,text='Uncorrect noise statistics',
                       variable=chVarnoise,command=checknoise)
checknoise.deselect()
checknoise.grid(column=0, columnspan=2, row=7, rowspan=1,sticky=W,padx=20)

label_unF = Label(filter_frame, text='Mismatch F=')
label_unF.grid(column=0, columnspan=1, row=8, rowspan=1,sticky=E)
label_unQ = Label(filter_frame, text='Incorrect Noise\nVariance Qfilter=')
label_unQ.grid(column=0, columnspan=1, row=9, rowspan=1,sticky=E)
label_start = Label(filter_frame, text='Start time=')
label_start.grid(column=0, columnspan=1, row=10, rowspan=1,sticky=E)
label_end = Label(filter_frame, text='End time=')
label_end.grid(column=0, columnspan=1, row=11, rowspan=1,sticky=E)


str_unF = StringVar()
entry_unF = Entry(filter_frame, textvariable = str_unF,state='disabled')
entry_unF.grid(column=1, columnspan=2, row=8, rowspan=1)
str_unQ = StringVar()
entry_unQ = Entry(filter_frame, textvariable = str_unQ,state='disabled')
entry_unQ.grid(column=1, columnspan=2, row=9, rowspan=1)
str_start = StringVar()
entry_start = Entry(filter_frame, textvariable = str_start,state='disabled')
entry_start.grid(column=1, columnspan=2, row=10, rowspan=1)
str_end = StringVar()
entry_end = Entry(filter_frame, textvariable = str_end,state='disabled')
entry_end.grid(column=1, columnspan=2, row=11, rowspan=1)



############################################################
#------------------------滤波方法、其他------------------------#
############################################################
#choice_frame=Frame(master)
choice_frame=LabelFrame(master,text='Method Configuration \n& Others',fg='red',padx=0,pady=0)
choice_frame.grid(column=2,row=0,sticky=N+S)

#list = Listbox(master)
#list.grid(column=3, columnspan=3, row=0, rowspan = 3, \
#          padx = 10, pady = 10)
#list.insert(0, 'Kalman')
#list.insert(1, 'UFIR')


#label1=Label(choice_frame,text='Method Configuration',font=('Times'))
#label1.grid(column=0, columnspan=1, row=0, rowspan=1)


chVarKal=IntVar()
check1=Checkbutton(choice_frame,text='Kalman Filter',
                   variable=chVarKal,command=checkKal)#,onvalue='normal',
                   #offvalue='disabled')
check1.deselect()
check1.grid(column=0,row=0,sticky=W,padx = 5)

chVarUF=IntVar()
check2=Checkbutton(choice_frame,text='UFIR Filter',
                   variable=chVarUF,command=checkUF)
check2.deselect()
check2.grid(column=0,row=1,sticky=W,padx = 5)

button_run = Button(choice_frame, text='Run', command =main)
button_run.config(width=20)
button_run.grid(column=0, row=2, rowspan =1, \
                sticky=E+W,padx = 5,pady=5)

##下拉栏单选
#def show_msg(*args):
#    value=combobox1.get()
#    if value=='Estimation error-->':
#        print(1)
#    elif value=='Root mean square error-->':
#        print(2)
#
#comboVar = StringVar()
#combobox1 = ttk.Combobox(choice_frame,textvariable=comboVar, state='readonly')
##combobox1.config(width = 25)
#combobox1['value'] = ('Estimation error-->', 'Root mean square error-->')
#combobox1.current(0)
#combobox1.bind("<<ComboboxSelected>>", show_msg)
#combobox1.grid(column=0,row=4,rowspan=1,padx=10,pady=10)


#进度条组件
p1 = ttk.Progressbar(choice_frame,  mode="determinate", orient=HORIZONTAL)
p1.grid(row=3,column=0,sticky=E+W,padx=5)
p1["maximum"] = 100
p1["value"] = 0


label_fig=Label(choice_frame,text='Different Description',fg='blue',
                  font=('Times'))
label_fig.grid(column=0,row=4,sticky=E+W)

v=IntVar()
radiobutton_error=Radiobutton(choice_frame,text='Estimation error',
                              variable=v,value=1,indicatoron=False,command=lambda:figerror())
radiobutton_error.grid(column=0, row=5, rowspan =1, \
                sticky=E+W,padx=5,pady=0)
radiobutton_error.select()
#radiobutton_error.pack(side=LEFT)

radiobutton_rmse=Radiobutton(choice_frame,text='Root mean square error',
                              variable=v,value=2,indicatoron=False,command=lambda:figrmse())
radiobutton_rmse.deselect()
radiobutton_rmse.grid(column=0, row=6, rowspan =1, \
                sticky=E+W,padx=5)
#radiobutton_rmse.pack(side=LEFT)
############################################################
#------------------------结果展示------------------------#
############################################################
#fig_frame=Frame(master)
fig_frame=LabelFrame(master,text='Simulation Results',fg='red',padx=0,pady=0)
fig_frame.grid(column=0,columnspan=3,row=1,sticky=N+S+W+E)

frame1=Frame(fig_frame)
frame2=Frame(fig_frame)
frame1.pack()

def figerror():
    frame2.pack_forget()
    frame1.pack()

def figrmse():
    frame1.pack_forget()
    frame2.pack()


f = Figure(figsize=(7,4), dpi=100)
f_dataPlot = FigureCanvasTkAgg(f, frame1)
#dataPlot.get_tk_widget().grid(column=0,columnspan=2,row=0)
f_dataPlot.get_tk_widget().pack()

g = Figure(figsize=(7,4), dpi=100)
g_dataPlot = FigureCanvasTkAgg(g, frame2)
#dataPlot.get_tk_widget().grid(column=0,columnspan=2,row=0)
g_dataPlot.get_tk_widget().pack()


master.mainloop()




