# -*- coding: utf-8 -*-
"""
Created on Tue Nov 14 19:41:30 2017

@author: fanxu
"""
#import matplotlib.pyplot as plt
#
#fig = plt.figure()
#fig.suptitle('bold figure suptitle', fontsize=14, fontweight='bold')
#ax = fig.add_subplot(111)
#fig.subplots_adjust(top=0.85)
#ax.set_title('axes title')
#ax.set_xlabel('xlabel')
#ax.set_ylabel('ylabel')
#ax.text(3, 8, 'boxed italics text in data coords', style='italic',
#bbox={'facecolor':'red', 'alpha':0.5, 'pad':10})
#ax.text(2, 6, r'an equation: $E=mc^2$', fontsize=15)
#ax.text(3, 2, u'unicode: Institut f\374r Festk\366rperphysik')
#ax.text(0.95, 0.01, 'colored text in axes coords',
#verticalalignment='bottom', horizontalalignment='right',
#transform=ax.transAxes,
#color='green', fontsize=15)
#ax.plot([2], [1], 'o')
#ax.annotate('annotate', xy=(2, 1), xytext=(3, 4),
#arrowprops=dict(facecolor='black', shrink=0.05))
#ax.axis([0, 10, 0, 10])
#plt.show()





#from tkinter import *
#
#root = Tk()
#
#textLabel = Label(root,text="有些心疼", justify=LEFT, padx=10) #Label 标签控件；可以显示文本和位图
#
#textLabel.pack(side=LEFT)
#
#photo = PhotoImage(format="png",file=r"C:\Users\fanxu\Desktop\Python\Filter GUI\fig1.emf")#PhotoImagecan be used for GIF and PPM/PGM color bitmaps
#
#imgLabel = Label(root, image=photo)
#imgLabel.pack(side=RIGHT)
#
#mainloop()

#!/usr/bin/env python
# -*- coding: utf-8 -*-

#from tkinter import *
#root = Tk()
##将一字符串与Checkbutton的值绑定，每次点击Checkbutton，将打印出当前的值
#v = StringVar()
#def callCheckbutton():
#    print(v.get())
#Checkbutton(root,variable = v,text = 'checkbutton value',
#            onvalue = 'python',        #设置On的值
#            offvalue = 'tkinter',    #设置Off的值
#            command = callCheckbutton).pack()
#root.mainloop()


#from tkinter import *  
#from tkinter import ttk  
#
#def sonwindow():
#    root2=Tk()
#root = Tk()  
#button_run = Button(root, text='Run', command = sonwindow)
#button_run.grid()
#root.mainloop()





#from tkinter import *  
#from tkinter import ttk  
#import time  
#  
#def manu_increment(*args):  
#    for i in range(100):  
#        p1["value"] = i+1  
#        root.update()  
##        time.sleep(0.1)  
#  
#def auto_increment(*args):  
#    global flag,value  
#    flag = not flag  
#  
#    if flag:  
#        btn2["text"] = "暂停动画"  
#        p2.start(10)  
#    else:  
#        btn2["text"] = "开始动画"  
#        value = p2["value"]  
#        p2.stop()  
#        p2["value"] = value  
#  
#root = Tk()  
#root.title("Progressbar组件")  
## 定量进度条  
#p1 = ttk.Progressbar(root, length=200, mode="determinate", orient=HORIZONTAL)  
#p1.grid(row=1,column=1)  
#p1["maximum"] = 100  
#p1["value"] = 0  
#  
## 通过指定变量，改变进度条位置  
## n = IntVar()  
## p1["variable"] = n  
#  
## 通过指定步长，改变进度条位置  
## p1.step(2)  
#  
#btn = ttk.Button(root,text="开始动画",command=manu_increment)  
#btn.grid(row=1,column=0)  
#  
## 非定量进度条  
#flag = False   # 标志位  
#value = 0      # 进度条位置  
#  
#p2 = ttk.Progressbar(root, length=200, mode="indeterminate", orient=HORIZONTAL)  
#p2.grid(row=2,column=1)  
#  
#btn2 = ttk.Button(root,text="自动动画",command=auto_increment)  
#btn2.grid(row=2,column=0)  
#  
#root.mainloop()  




#from tkinter import *  
#from tkinter import ttk  
#
#def show_msg(*args):
#    value=players.get()
#    if value=='成龙':
#        print(1)
#    elif value=='刘德华':
#        print(2)
#    elif value=='周星驰':
#        print(3)
#
#
#root = Tk()
#name = StringVar()
#players = ttk.Combobox(root, textvariable=name)
#players["values"] = ("成龙", "刘德华", "周星驰")
#players["state"] = "readonly"
#players.current(0)
## players.set("演员表")
## print(players.get())
#players.bind("<<ComboboxSelected>>", show_msg)
#players.pack()
#root.mainloop()



#from tkinter import *
#root = Tk()
#group=LabelFrame(root,text='asdg',padx=5,pady=0)
#group.pack(padx=10,pady=10)
#langs=[('p',1),('a',2)]
#
#v=StringVar()
#print(v)
#v.set(2)
#for langs,num in langs:
#    b=Radiobutton(group,text=langs,variable=v,value=num,indicatoron = False)
#    b.pack()
#mainloop()





#import tkinter as tk
# 
#g_font = ("Monaco", 12)
# 
# 
#class ShowFrame(object):
#    '''
#    show frame
#    '''
# 
#    def __init__(self, master=None):
#        self.root = master
#        self.create_frame()
# 
#    def create_frame(self):
#        '''
#        create main frame
#        '''
#        self.frm = tk.Frame(self.root)
#        self.frm.pack(fill="both", expand=1)
# 
#        self.frm_choose = tk.LabelFrame(self.frm) 
#        self.frm_choose.pack(fill="both", expand=1, padx=2, side=tk.TOP)
# 
#        self.frm_show = tk.LabelFrame(self.frm) 
#        self.frm_show.pack(fill="both", expand=1, padx=2, side=tk.BOTTOM)
# 
#        self.create_frm_choose()
#        self.create_frm_show()
# 
#    def create_frm_choose(self):
#        '''
#        create frame choose
#        '''
#        self.choose_info_lst = ["Button0", "Button1", "Button2", "Button3"]
#        self.choose_btn_lst = list()
#        for index, value in enumerate(self.choose_info_lst):
#            temp_btn = tk.Button(self.frm_choose,
#                                 anchor="w",
#                                 text=value,
#                                 font=g_font)
#            temp_btn.bind('<Button-1>', self.btn_click)
#            temp_btn.pack(fill="both", expand=1, padx=2, pady=2, side=tk.LEFT)
#            self.choose_btn_lst.append(temp_btn)
# 
#    def create_frm_show(self):
#        '''
#        create frame show
#        '''
#        self.show_label_0 = tk.Label(self.frm_show, text="Button0", font=g_font)
#        self.show_label_0.pack(fill="both", expand=1, padx=2, pady=2)
# 
#        self.show_label_1 = tk.Label(self.frm_show, text="Button1", font=g_font)
#        self.show_label_1.pack_forget()
# 
#        self.show_label_2 = tk.Label(self.frm_show, text="Button2", font=g_font)
#        self.show_label_2.pack_forget()
# 
#        self.show_label_3 = tk.Label(self.frm_show, text="Button3", font=g_font)
#        self.show_label_3.pack_forget()
# 
#    def btn_click(self, event=None):
#        '''
#        choose frm
#        '''
#        btn_text = event.widget['text']
#        if btn_text == "Button0":
#            self.show_label_0.pack(fill="both", expand=1, padx=2, pady=2)
#            self.show_label_1.pack_forget()
#            self.show_label_2.pack_forget()
#            self.show_label_3.pack_forget()
#        elif btn_text == "Button1":
#            self.show_label_0.pack_forget()
#            self.show_label_1.pack(fill="both", expand=1, padx=2, pady=2)
#            self.show_label_2.pack_forget()
#            self.show_label_3.pack_forget()
#        elif btn_text == "Button2":
#            self.show_label_0.pack_forget()
#            self.show_label_1.pack_forget()
#            self.show_label_2.pack(fill="both", expand=1, padx=2, pady=2)
#            self.show_label_3.pack_forget()
#        elif btn_text == "Button3":
#            self.show_label_0.pack_forget()
#            self.show_label_1.pack_forget()
#            self.show_label_2.pack_forget()
#            self.show_label_3.pack(fill="both", expand=1, padx=2, pady=2)
# 
#if __name__ == "__main__":
#    '''
#    main loop
#    '''
#    root = tk.Tk()
#    root.columnconfigure(0, weight=1)
#    root.rowconfigure(0, weight=1)
#    root.geometry()
# 
#    app = ShowFrame(root)
#    app.frm.pack(fill="both", expand=1)
#    root.mainloop()


#from tkinter import *
#root = Tk()
#
#def r1():
#    print('call r1')
#def r2():
#    print('call r2')
#def r3():
#    print('call r3')
#def r4():
#    print('call r4')
#
#i = 0
#v = IntVar()
#v.set(0)
#for r in [r1,r2,r3,r4]:
#    Radiobutton(root,variable = v, text = 'radio button', value = i, command = r,
#                    indicatoron = 0).pack()
#    i += 1
#    
#root.mainloop()




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







from tkinter import *

root=Tk()
root.geometry("500x280")

frame1=Frame(root,width=500,height=280)
frame2=Frame(root,width=500,height=280)
frame1.pack()

def to_frame1():
	frame2.pack_forget()
	frame1.pack()
def to_frame2():
	frame1.pack_forget()
	frame2.pack()


Button(frame1,text="button1").pack()
Button(frame1,text="button2").pack()

Button(frame2,text="button3").pack()
Button(frame2,text="button4").pack()

# 菜单
menubar=Menu(root)
function_select_menu=Menu(menubar,tearoff=0)
function_select_menu.add_command(label="功能1",command=to_frame1)
function_select_menu.add_command(label="功能2",command=to_frame2)
menubar.add_cascade(label="功能",menu=function_select_menu)
root.config(menu=menubar)


root.mainloop()





