#from tkinter import *
#global entry
#global entry_state
#def button_onClick():
#    global entry
#    global entry_state
#    if entry_state:
#        entry.configure(state = 'disabled')
#        entry_state = False
#    else:
#        entry.configure(state = 'normal')
#        entry_state = True
#
#
#tkwindow = Tk()
#entry_state = True
#text = StringVar()
#entry = Entry(tkwindow, textvariable = text)
#button = Checkbutton(tkwindow, text='Click', command = button_onClick)
#entry.pack()
#button.pack()
#tkwindow.mainloop()




from tkinter import *
def button_onClick():
    if not int(chvar.get()):
#        entry.configure(state = 'disabled')
        entry['state']='disabled'
    else:
#        entry.configure(state = 'normal')
        entry['state']='normal'


tkwindow = Tk()
chvar=StringVar()
text=StringVar()
entry = Entry(tkwindow, textvariable = text,state='disabled')
button = Checkbutton(tkwindow, text='Click', variable=chvar,command = button_onClick)
button.deselect()
entry.pack()
button.pack()
tkwindow.mainloop()