import tkinter as tk


class App:  # 定义类
    def __init__(self, master, data):
        frame = tk.Frame(master)  # 定义窗体框架
        frame.pack(side=tk.RIGHT, padx=100, pady=100)

        # 定义按钮
        self.hi_there = tk.Button(
            frame, text="打招呼", bg="red", fg='green', command=self.say_hi)
        self.hi_there.pack(padx=10, pady=10)  # 位置
        self.aaa = self.hex_to_float(data)
        print(self.aaa)

    def say_hi(self):
        print("Hi! 大家好,终于我跟大家见面了。")

    def hex_to_float(self, u16data):
        f_res = (u16data & 0x003F)/64 + (u16data & 0x7FC0) / 64
        return f_res


root = tk.Tk()
app = App(root, 0x06E0)
root.mainloop()
