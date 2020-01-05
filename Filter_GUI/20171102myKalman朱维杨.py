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
from numpy import arange, sin, pi
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import tkinter
matplotlib.use('TkAgg')
####initial,only for input=2,output=1

global f
global dataPlot
global str_a, str_b, str_c, str_d, str_w, str_v
global y

def draw(nx, Q, R, N, A, B, C, D, w, v):
	global f
	global dataPlot
	x=np.zeros([nx, N+1])
	x[:,0]=np.array([[1,0.1]])
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

	
	f.clf()
	a = f.add_subplot(1,1,1)
	a.plot(xhat[0,0:N]-x[0,0:N],label='Kalman',color='black',linewidth=2)
	a.plot(y[0:N]-x[0,0:N],label='measurement')
	a.legend(loc = 'upper right')
	a.grid()
	a.set_xlim(0,N)
	dataPlot.show()

def run():
	global str_a, str_b, str_c, str_d, str_w, str_v
	# Data Input
	#A=np.array([[1,0.1],[0,1]])
	A=np.array(eval(str_a.get()))
	#B=np.array([1,0.1])
	B=np.array(eval(str_b.get()))
	#C=np.array([1,0])
	C=np.array(eval(str_c.get()))
	#D=1
	D=np.array(eval(str_d.get()))
	nx=2
	#ny=1
	Q=1**2
	R=5**2
	#w=random.normal(0,math.sqrt(Q),N)
	w = eval(str_w.get())
	#v=random.normal(0,math.sqrt(R),N)
	v = eval(str_v.get())
	N = len(w)
	draw(nx, Q, R, N, A, B, C, D, w, v)

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
	
	
	
# Main window
master = Tk()
master.title('Kalman Filter')
label_a = Label(master, text='A=')
label_a.grid(column=0, columnspan=1, row=0, rowspan=1)
label_b = Label(master, text='B=')
label_b.grid(column=0, columnspan=1, row=1, rowspan=1)
label_c = Label(master, text='C=')
label_c.grid(column=0, columnspan=1, row=2, rowspan=1)
label_d = Label(master, text='D=')
label_d.grid(column=0, columnspan=1, row=3, rowspan=1)
label_w = Label(master, text='Q=')
label_w.grid(column=0, columnspan=1, row=4, rowspan=1)
label_v = Label(master, text='R=')
label_v.grid(column=0, columnspan=1, row=5, rowspan=1)
label_y = Label(master, text='y')
label_y.grid(column=0, columnspan=1, row=6, rowspan=1)
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
str_w = StringVar()
entry_w = Entry(master, textvariable = str_w)
entry_w.grid(column=1, columnspan=2, row=4, rowspan=1)
str_v = StringVar()
entry_v = Entry(master, textvariable = str_v)
entry_v.grid(column=1, columnspan=2, row=5, rowspan=1)
button_import = Button(master, text='Import', command = chooseExcelFile)
button_import.grid(column=1, columnspan=2, row=6, rowspan=1, sticky=E+W)
list = Listbox(master)
list.grid(column=3, columnspan=3, row=0, rowspan = 3, padx = 10, pady = 10)
list.insert(0, 'Kalman')
button_run = Button(master, text='Run', command = run)
button_run.grid(column=3, columnspan=3, row=3, rowspan=1, sticky=E+W, padx = 10, pady = 10)

f = Figure(figsize=(7,4), dpi=100)
dataPlot = FigureCanvasTkAgg(f, master=master)
dataPlot.get_tk_widget().grid(column=6, columnspan=7, row=0, rowspan=7, pady = 10)

# Loop
master.mainloop()