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
import ast

import matplotlib, sys
from numpy import arange, sin, pi
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
from tkinter import *
matplotlib.use('TkAgg')
####initial,only for input=2,output=1

A=np.array([[1,0.1],[0,1]])
#A=np.array(ast.literal_eval(input('A=')))

B=np.array([1,0.1])
C=np.array([1,0])
D=1
#D=eval(input('D='))
nx=2
ny=1
Q=1**2
R=5**2
N=150

w=random.normal(0,math.sqrt(Q),N)
v=random.normal(0,math.sqrt(R),N)

x=np.zeros([nx, N+1])
x[:,0]=np.array([1,0.1])
y=np.zeros(N+1)
y[0]=np.dot(C,x[:,0])+D*v[0]
for i in range(0, N):
    x[:,i+1]=np.dot(A,x[:,i])+B*w[i]
    y[i+1]=np.dot(C,x[:,i])+D*v[i]

xhat = np.zeros([nx,N+1])
xhatminus = np.zeros([nx,N+1])
P=np.array([[0, 0], [0, 0]])
Pminus = np.zeros([nx,N+1])
for i in range(1,N):
    xhatminus[:,i]=np.dot(A,xhat[:,i-1])
    Pminus=np.dot(np.dot(A,P),A.T)+B*Q*B.T
    K=np.dot(np.dot(Pminus,C.T),1./(np.dot(np.dot(C,Pminus),C.T)+R))
    xhat[:,i]=xhatminus[:,i]+np.dot(K,y[i]-np.dot(C,xhatminus[:,i]))
    P=np.dot(np.eye(nx)-np.dot(K,C),Pminus)

#plt.Figure()
#plt.plot(xhat[0,0:N]-x[0,0:N],label='Kalman',color='black',linewidth=2)
#plt.plot(y[0:N]-x[0,0:N],label='measurement')
#plt.legend(loc = 'upper right')
#plt.xlim(0,N)
#plt.grid()
#plt.show()


#from tkinter import *  
#import matplotlib  
#from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg  
#from matplotlib.figure import Figure  
#def drawPic():  
#    try:sampleCount=int(inputEntry.get())  
#    except:  
#        sampleCount=50
#        print('请输入整数')
#        inputEntry.delete(0,END)  
#        inputEntry.insert(0,'50')  
#         
#    #清空图像，以使得前后两次绘制的图像不会重叠  
#    drawPic.f.clf()  
#    drawPic.a=drawPic.f.add_subplot(111)  
#         
#    #在[0,100]范围内随机生成sampleCount个数据点  
#    x=np.random.randint(0,100,size=sampleCount)  
#    y=np.random.randint(0,100,size=sampleCount)  
#    color=['black']  
#         
#    #绘制这些随机点的散点图，颜色随机选取  
#    drawPic.a.scatter(x,y,s=3,color=color[np.random.randint(len(color))])  
#    drawPic.a.set_title('Demo: Draw N Random Dot')  
#    drawPic.canvas.show()
#  
#if __name__ == '__main__':
##    matplotlib.use('TkAgg')
#    root = Tk()
#    #在Tk的GUI上放置一个画布，并用.grid()来调整布局  
#    drawPic.f = Figure(figsize=(5,4), dpi=100)
#    drawPic.canvas = FigureCanvasTkAgg(drawPic.f, master=root)
#    drawPic.canvas.show()
#    drawPic.canvas.get_tk_widget().grid(row=0, columnspan=3)
#    #放置标签、文本框和按钮等部件，并设置文本框的默认值和按钮的事件函数  
#    Label(root,text='请输入样本数量：').grid(row=1,column=0)  
#    inputEntry=Entry(root)  
#    inputEntry.grid(row=1,column=1)  
#    inputEntry.insert(0,'50')  
#    Button(root,text='画图',command=drawPic).grid(row=1,column=2,columnspan=3)
#    #启动事件循环  
#    root.mainloop()  


master = Tk()
master.title('Kalman Filter')
#-------------------------------------------------------------------------------

f = Figure(figsize=(7,4), dpi=100)
a = f.add_subplot(1,1,1)
#a.plot(xhat[0,0:N]-x[0,0:N],label='Kalman',color='black',linewidth=2)
#a.plot(y[0:N]-x[0,0:N],label='measurement')
a.plot(xhat[0,0:N],label='Kalman',color='black',linewidth=2)
a.plot(y[0:N],label='measurement')
a.plot(x[0,0:N],label='true')
a.legend(loc = 'upper right')
a.grid()
a.set_xlim(0,N)

dataPlot = FigureCanvasTkAgg(f, master=master)
dataPlot.show()
dataPlot.get_tk_widget().pack(side=TOP, fill=BOTH, expand=1)
#-------------------------------------------------------------------------------
master.mainloop()