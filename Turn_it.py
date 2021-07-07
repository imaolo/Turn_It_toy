import serial  
import time 
import tkinter as tk
import datetime
from PIL import ImageTk,Image

class Application(tk.Frame):
    def __init_elf, master=None):
        super().__init__(master)
        self.master = master
        self.createWidgets()
        self.state = "connect"
        self.data = ""
        self.score = 0
    def createWidgets(self):
        self.image = Image.open("logo.jpg").resize((100,100))
        self.logo  = ImageTk.PhotoImage(self.image)

        self.LOGO1 = tk.Label(image = self.logo,height = 100, width = 100)
        self.LOGO1.grid(row = 0, column = 0,padx = 20,pady = 20)

        self.LOGO2 = tk.Label(image = self.logo,height = 100, width = 100)
        self.LOGO2.grid(row = 0, column = 2,padx = 20,pady = 20)

        self.TITLE = tk.Label(text="Turn-It",fg = "gray",bg = "white",font = ("Arial", 40))
        self.TITLE.grid(row = 0,column = 1)

        self.LEFT = tk.Label(bg = "white",font = ("Arial",30),fg = "red")
        self.LEFT.grid(row = 1, column = 0)

        self.MIDDLE = tk.Label(text = "Connecting",fg = "green",bg = "white",font = ("Arial",30))
        self.MIDDLE.grid(row = 1, column = 1)

        self.RIGHT = tk.Label(bg = "white",font = ("Arial",30),fg="red")
        self.RIGHT.grid(row = 1, column = 2)        
    def readLine(self):
        print("------ping--------")
        self.data = self.bt.readline().decode()
        print("data: ",self.data)
        self.after(200,self.readLine)
        if (self.data != ''):
            self.update()
    def bluetoothConnect(self):
        self.MIDDLE.config(fg="red",text = "Connecting")
        print("connecting")
        self.bt = serial.Serial(
            port='COM4',\
            baudrate=38400,\
            parity=serial.PARITY_NONE,\
            stopbits=serial.STOPBITS_ONE,\
            bytesize=serial.EIGHTBITS,\
            timeout=1,\
            xonxoff = False)
        self.bt.reset_input_buffer()
        self.bt.reset_output_buffer()
        self.MIDDLE.config(fg="green",text = "Connected")
        self.state = "start"
        print("connected")
    def update(self):
        print("Begin Update")
        array = self.data.split()
        if(array[0] == "left"):
            self.LEFT.config(text=array[1],fg=array[2])
        elif(array[0] == "right"):
            display = array[1]
            self.RIGHT.config(text= display,fg=array[2])
        elif(array[0] == "middle"):
            display = "Score: "+array[1]
            self.MIDDLE.config(text=display,fg=array[2])

root = tk.Tk()
root.configure(bg="white")
root.geometry('500x250')

app = Application(master=root)
app.after(5,app.bluetoothConnect())
app.after(25,app.readLine())
app.mainloop()



