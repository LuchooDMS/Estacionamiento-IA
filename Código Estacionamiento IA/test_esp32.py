import serial
import time
import random

# ⚠️ CAMBIAR ESTO
esp32 = serial.Serial('COM3', 115200)

time.sleep(2)  # esperar conexión

while True:

    datos = [str(random.randint(0,1)) for _ in range(8)]
    mensaje = ",".join(datos) + "\n"

    print("Enviado:", mensaje)

    esp32.write(mensaje.encode())

    time.sleep(5)