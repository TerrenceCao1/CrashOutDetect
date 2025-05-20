import serial
import os
import time

ser = serial.Serial('COM3', 9600, timeout=1)

while True:
    line = ser.readline().decode('utf-8').strip()
    if line == "RESTART":
        print("Restarting computer...")
        os.system("shutdown /r /t 1")  # For Windows
        break
    time.sleep(0.1)
