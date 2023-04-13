import serial
import tkinter as tk

class MainMenu(tk.Frame):
    def __init__(self, master, serial_interface):
        super().__init__(master)
        self.serial = serial_interface
        self.create_widgets()

    def create_widgets(self):
        tk.Label(self, text="        MENU PRINCIPAL        ").grid(row=0, column=0, columnspan=2)
        tk.Button(self, text=" Modificar Posicion de  Servos ", command=self.open_submenu1).grid(row=1, column=0, padx=10, pady=5)
        tk.Button(self, text="Modificar Posicion de Stepper", command=self.open_submenu2).grid(row=2, column=0, padx=10, pady=5)
        tk.Button(self, text=" Modificar  Tiempo  de  Titileo ", command=self.open_submenu3).grid(row=3, column=0, padx=10, pady=5)
        tk.Button(self, text="             Obtener Estatus            ", command=self.open_submenu4).grid(row=4, column=0, padx=10, pady=5)
        tk.Button(self, text="             Modificar Todo            ", command=self.open_submenu5).grid(row=5, column=0, padx=10, pady=5)

    def open_submenu1(self):
        SubMenu1(self.serial)
        data = f"1 "
        self.serial.write(data.encode())

    def open_submenu2(self):
        SubMenu2(self.serial)
        data = f"2 "
        self.serial.write(data.encode())

    def open_submenu3(self):
        SubMenu3(self.serial)
        data = f"3 "
        self.serial.write(data.encode())

    def open_submenu4(self):
        SubMenu4(self.serial)
        data = f"4 "
        self.serial.write(data.encode())

    def open_submenu5(self):
        SubMenu5(self.serial)
        data = f"5 "
        self.serial.write(data.encode())

class SubMenu1(tk.Toplevel):
    def __init__(self, serial_interface):
        super().__init__()
        self.serial = serial_interface
        self.create_widgets()

    def create_widgets(self):
        tk.Label(self, text=" INGRESE LOS NUEVOS VALORES PARA LOS ").pack()
        tk.Label(self, text="  SERVOS COMO NUMERO ENTRE 1 Y 180  ").pack()
        tk.Label(self, text="Servo 1:").pack()
        self.entry1 = tk.Entry(self)
        self.entry1.pack()
        tk.Label(self, text="Servo 2:").pack()
        self.entry2 = tk.Entry(self)
        self.entry2.pack()
        tk.Button(self, text="ENVIAR", command=self.send).pack()

    def send(self):
        data = f"{self.entry1.get()},{self.entry2.get()}, "
        self.serial.write(data.encode())
        self.destroy()

class SubMenu2(tk.Toplevel):
    def __init__(self, serial_interface):
        super().__init__()
        self.serial = serial_interface
        self.create_widgets()

    def create_widgets(self):
        tk.Label(self, text="         INGRESE LA CANTIDAD DE PASOS A DAR Y LA DIRECCION         ").pack()
        tk.Label(self, text="(Seleccionar la caja para derecha, deseleccionar para la izquierda)").pack()
        tk.Label(self, text="Numero de Pasos:").pack()
        self.entry1 = tk.Entry(self)
        self.entry1.pack()
        self.var = tk.IntVar(value=0)
        tk.Checkbutton(self, text="Direccion", variable=self.var, onvalue=1, offvalue=0).pack()
        tk.Button(self, text="Enviar", command=self.send).pack()

    def send(self):
        data = f"{self.entry1.get()},{self.var.get()}, "
        self.serial.write(data.encode())
        self.destroy()

class SubMenu3(tk.Toplevel):
    def __init__(self, serial_interface):
        super().__init__()
        self.serial = serial_interface
        self.create_widgets()

    def create_widgets(self):
        tk.Label(self, text="INGRESE EL TIEMPO EN MS DESEADO PARA EL PARPADEO").pack()
        self.entry1 = tk.Entry(self)
        self.entry1.pack()
        tk.Button(self, text="Enviar", command=self.send).pack()

    def send(self):
        data = f"{self.entry1.get()}, "
        self.serial.write(data.encode())
        self.destroy()

class SubMenu4(tk.Toplevel):
    def __init__(self, serial_interface):
        super().__init__()
        self.serial = serial_interface
        self.received_data = []
        self.create_widgets()

    def create_widgets(self):
        data = f"4 "
        self.serial.write(data.encode())
        
        self.text = tk.Text(self)
        self.text.pack()
        tk.Button(self, text="Cerrar", command=self.close).pack()

        # read from serial port and display received data
        while True:
            if self.serial.in_waiting > 0:
                data = self.serial.read(self.serial.in_waiting)
                self.text.insert("end", data.decode("utf-8"))
                self.text.see("end")
            self.update()
            

    def close(self):
        self.serial.write(b",")
        self.destroy()


class SubMenu5(tk.Toplevel):
    def __init__(self, serial_interface):
        super().__init__()
        self.serial = serial_interface
        self.create_widgets()

    def create_widgets(self):
        tk.Label(self, text=" INGRESE LOS NUEVOS VALORES PARA TODOS LOS CAMPOS ").pack()
        tk.Label(self, text="Servo 1:").pack()
        self.entry1 = tk.Entry(self)
        self.entry1.pack()
        tk.Label(self, text="Servo 2:").pack()
        self.entry2 = tk.Entry(self)
        self.entry2.pack()
        tk.Label(self, text="Numero de Pasos:").pack()
        self.entry3 = tk.Entry(self)
        self.entry3.pack()
        tk.Label(self, text="(Seleccionar la caja para derecha, deseleccionar para la izquierda)").pack()
        self.var = tk.IntVar(value=0)
        tk.Checkbutton(self, text="Direccion", variable=self.var, onvalue=1, offvalue=0).pack()
        tk.Label(self, text="Tiempo de Titileo en ms:").pack()
        self.entry4 = tk.Entry(self)
        self.entry4.pack()
        tk.Button(self, text="Enviar", command=self.send).pack()

    def send(self):
        data = f"{self.entry1.get()},{self.entry2.get()},{self.entry3.get()},{self.var.get()},{self.entry4.get()}, "
        self.serial.write(data.encode())
        self.destroy()

if __name__ == '__main__':
    ser = serial.Serial('COM5', 115200) # Change to the appropriate serial port and baud rate
    root = tk.Tk()
    app = MainMenu(root, ser)
    app.pack()
    root.mainloop()
