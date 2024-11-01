import tkinter as tk
from tkinter import messagebox
import serial
import time
import threading 

arduino_port = "COM8"
baud_rate = 9600
arduino = None

def conectar():
    global arduino
    try: 
        arduino = serial.Serial(arduino_port, baud_rate)
        time.sleep(2)
        lbConection.config(text = "Estado: Conectado", fg = "green")
        messagebox.showinfo("Conexion", "Conexion establecida.")
        start_reading()
    except serial.SerialException:
        messagebox.showerror("Error", "No se puede conectar al Arduino, Verifique el puerto")
        

def desconectar():
    global arduino
    if arduino and arduino.is_open:
        arduino.close()
        lbConection.config(text = "Estado: Desconectado", fg = "red")
        messagebox.showinfo("Conexion", "Conexion terminada.")
    else: 
        messagebox.showwarning("Advertencia", "No hay conexion activa.")
 
def enviar_limite():
    global arduino
    if arduino and arduino.is_open:
        try: 
            limite = tbLimTemp.get()
            if limite.isdigit():
                arduino.write(f"{limite}\n".encode())
                messagebox.showinfo("Enviado", f"limite de temperatura ({limite}°C) enviado.")
            else:
                messagebox.showerror("Error", "Ingrese un valor numérico para el límite.")
        except Exception as e: 
            messagebox.showerror("Error", f"No se pudo enviar el limite: {e}")
    else:
        messagebox.showwarning("Advertencia", "Conéctese al Arduino antes de enviar el limite.")
 
def read_from_arduino():
    global arduino
    while arduino and arduino.is_open:
        try: 
            data = arduino.readline().decode().strip()
            if "Temperatura" in data: 
                temp_value = data.split(";")[1].strip().split(" ")[0]
                lbTemp.config(text = f"{temp_value}°C")
            time.sleep(1)
        except Exception as e:
            print (f"Error Leyendo datos: {e}")
            break
        
def start_reading():
    thread = threading.Thread(target = read_from_arduino)
    thread.daemon = True
    thread.start()
    

root = tk.Tk()
root.title("Interfaz de Monitoreo de Temperatura")
root.geometry("300x350")

lbTitleTemp = tk.Label(root, text = "Temperatura Actual", font = ("Arial", 12))
lbTitleTemp.pack(pady=10)

lbTemp = tk.Label(root, text="-- °C", font =("Arial", 24 ))
lbTemp.pack()

lbConection = tk.Label(root, text = "Estado: Desconectado", fg = "red", font = ("Arial", 10))
lbConection.pack(pady=5)

lblimitTemp = tk.Label(root, text ="Limite de Temperatura: " )
lblimitTemp.pack(pady = 5)
tbLimTemp = tk.Entry(root, width=10)
tbLimTemp.pack(pady=5)

btnEnviar = tk.Button(root, text= "Enviar Limite", command=enviar_limite, font = ("Arial", 10))
btnEnviar.pack(pady=5)   

btnConectar = tk.Button(root, text = "Conectar", command = conectar, font =("Arial", 10))
btnConectar.pack(pady=5)   

btnDesconectar = tk.Button(root, text = "Desconectar", command = desconectar, font =("Arial", 10))
btnDesconectar.pack(pady=5)   

root.mainloop()