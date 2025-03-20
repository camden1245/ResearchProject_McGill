import serial
import time

# Replace 'COM3' with your serial port
ser = serial.Serial('COM3', 19200, timeout=1)

def send_command(command):
    ser.write(f'{command}\r'.encode())
    time.sleep(0.1)
    response = ser.read_all().decode()
    return response

# Example: Get pump firmware version
response = send_command('VER')
print(f'Pump Response: {response}')

ser.close()
