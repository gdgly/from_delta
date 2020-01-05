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
import ast
from PIL import Image, ImageTk
matplotlib.use("TkAgg")

#---------------------------------------------
#initial,only for input=2,output=1
#----------------------------------------------

global f
global dataPlot
global str_a, str_b, str_c, str_d, str_q, str_r
global str_F, str_H, str_Q, str_R, str_x0, str_N
global str_Qfilter, str_Rfilter,str_x0filter, str_P0filter, str_Nopt
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
    
def Kalman(systemModel):
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
        Covariance = R * FExpMinusP * G * FExpMinusP.T;
        PElements[0, i-p-1] = Covariance[0, 0];
        PElements[1, i-p-1] = Covariance[1, 1];
        MeasResidual[:, i-p-1] = yArr[:, i-p-1] - HArr[i-p-1, :] * xhat;
    return xArr,yArr,xhatArr,xhatError, PElements, NArr, MeasResidual


def horizon():
    pass
    return Nopt

def rmse():
    pass

def Initial():
    global str_a, str_b, str_c, str_d, str_q, str_r
    QFactorArr = 1
    Nopt = 12
    F = np.mat([[1, 0.1], [0, 1]])
    H = np.mat([1, 0]);
    QReal = np.mat([[0, 0], [0, 1**2]])
    QFilter = QFactorArr*QReal;
    R = 1**2#0.833**2
    x = np.mat([[1], [1]])
    N = 300
    print(type(N))
    
#    F=np.mat(ast.literal_eval(str_a.get()))
#    F=np.mat(ast.literal_eval(str_a.get()))
#    F=np.mat(ast.literal_eval(str_a.get()))
#    F=np.mat(ast.literal_eval(str_a.get()))
#    F=np.mat(ast.literal_eval(str_a.get()))
#    F=np.mat(ast.literal_eval(str_a.get()))

#    nx = max(F.shape)
#    ny = min(H.shape)
#    xArr=np.mat(np.zeros((nx, N)))
#    yArr=np.mat(np.zeros((ny, N)))
#    for k in range(0,N):
#        x = F * x + np.sqrt(QReal) * np.random.randn(nx, 1)
#        y = H * x + np.sqrt(R) * np.random.randn()
#        xArr[:, k] = x
#        yArr[:, k] = y
    systemModel = SystemModel(F, H, QReal, QFilter, R, x, N)
    return systemModel,Nopt



def draw():#画图
    global f
    global dataPlot
    (systemModel,Nopt)=Initial()
    N=systemModel.N
    resultF=UFIR(systemModel, False, Nopt)
    resultK=Kalman(systemModel)
    x=np.array(resultF[0])
    y=np.array(resultF[1])
    xhat=np.array(resultF[2])
    xhaterror=np.array(resultF[3])
    xhatKerror=np.array(resultK[3])
    
    f.clf()
    a = f.add_subplot(1,1,1)
    #a.plot(xhat[0,:],label='filter',color='black',linewidth=2)
    #a.plot(y[0,:],label='measurement')
    #a.plot(x[0,:],label='true')
    #a.plot(y[0,:]-x[0,:],label='measurement')
    a.plot(xhaterror[0,:],label='Ffilter')
    a.plot(xhatKerror[0,:],label='Kfilter')
    a.legend(loc = 'upper right')
    a.grid()
    a.set_xlim(0,N-1)
    a.set_title('Kalman & Measurement')
    dataPlot.show()


def main():
    draw()


def resize(w, h, w_box, h_box, pil_image):#对一个pil_image对象进行缩放，让它在一个矩形框内，还能保持比例 
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
model_frame=Frame(master)
model_frame.pack()


label_a = Label(master, text='Transition matrix A=')
label_a.grid(column=0, columnspan=1, row=0, rowspan=1,sticky=E)
label_b = Label(master, text='Observation matrix H=')
label_b.grid(column=0, columnspan=1, row=1, rowspan=1,sticky=E)
label_c = Label(master, text='State noise variance Q=')
label_c.grid(column=0, columnspan=1, row=2, rowspan=1,sticky=E)
label_d = Label(master, text='Observation noise variance R=')
label_d.grid(column=0, columnspan=1, row=3, rowspan=1,sticky=E)
label_w = Label(master, text='Simulation interval N=')
label_w.grid(column=0, columnspan=1, row=4, rowspan=1,sticky=E)
label_v = Label(master, text='Initial state x0=')
label_v.grid(column=0, columnspan=1, row=5, rowspan=1,sticky=E)
label_y = Label(master, text='Observation y (cannot use now)=',fg='gray')
label_y.grid(column=0, columnspan=1, row=6, rowspan=1,sticky=E)


str_a = StringVar()
entry_a = Entry(master, textvariable = str_a)
entry_a.grid(column=1, columnspan=2, row=0, rowspan=1)
str_b = StringVar()
entry_b = Entry(master, textvariable = str_b)
entry_b.grid(column=1, columnspan=2, row=1, rowspan=1)
str_c = StringVar()
entry_c = Entry(master, textvariable = str_c)
entry_c.grid(column=1, columnspan=2, row=2, rowspan=1)
str_d = StringVar()
entry_d = Entry(master, textvariable = str_d)
entry_d.grid(column=1, columnspan=2, row=3, rowspan=1)
str_q = StringVar()
entry_q = Entry(master, textvariable = str_q)
entry_q.grid(column=1, columnspan=2, row=4, rowspan=1)
str_r = StringVar()
entry_r = Entry(master, textvariable = str_r)
entry_r.grid(column=1, columnspan=2, row=5, rowspan=1)

button_import = Button(master, text='Import',fg='gray', command = chooseExcelFile)
button_import.grid(column=1, columnspan=2, row=6, rowspan=1, sticky=E+W)


############################################################
#------------------------滤波参数设置------------------------#
############################################################
filter_frame=Frame(master)
filter_frame.pack()








############################################################
#------------------------滤波方法------------------------#
############################################################
choice_frame=Frame(master)
choice_frame.pack()

#list = Listbox(master)
#list.grid(column=3, columnspan=3, row=0, rowspan = 3, \
#          padx = 10, pady = 10)
#list.insert(0, 'Kalman')
#list.insert(1, 'UFIR')

chVarKal=IntVar()
check1=Checkbutton(master,text='Kalman Filter',variable=chVarKal)
#check1.select()
check1.grid(column=3,row=0,sticky=W,padx = 10)

chVarUF=IntVar()
check2=Checkbutton(master,text='UFIR Filter',variable=chVarUF)
#check2.select()
check2.grid(column=3,row=1,sticky=W,padx = 10)


button_run = Button(master, text='Run', command = main)
button_run.grid(column=3, row=2, rowspan =1, \
                sticky=E+W,padx = 10, pady = 10)


canvas=Canvas(master,width=200,height=200)
canvas.grid(column=3,row=3, rowspan =3, \
                sticky=E+W,padx = 10, pady = 10)
canvas.create_text(50,40,text='Remark:',fill='blue',\
                   font=('Times',16))
image_model=Image.open('fig1.emf')
w,h=image_model.size
image_model_resized=resize(w,h,100,100,image_model)
tk_image_model=ImageTk.PhotoImage(image_model_resized)

image_matirx=Image.open('fig2.emf')
w,h=image_matirx.size
image_matirx_resized=resize(w,h,120,100,image_matirx)
tk_image_matrix=ImageTk.PhotoImage(image_matirx_resized)

canvas.create_image(10,70,anchor=NW,image=tk_image_model)
canvas.create_image(10,120,anchor=NW,image=tk_image_matrix)
#canvas.create_rectangle(20,70,175,130)


############################################################
#------------------------结果展示------------------------#
############################################################
fig_frame=Frame(master)
fig_frame.pack()

f = Figure(figsize=(7,4), dpi=100)
dataPlot = FigureCanvasTkAgg(f, master=master)
dataPlot.get_tk_widget().grid(column=6, columnspan=7, row=0, rowspan=7, pady = 10)

master.mainloop()




