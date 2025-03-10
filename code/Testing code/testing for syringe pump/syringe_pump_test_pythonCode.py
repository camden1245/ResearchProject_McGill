import serial

# Configure the serial connection
ser = serial.Serial(
    port='COM3',       # Replace with your COM port
    baudrate=9600,     # Default baud rate for NE1000
    bytesize=8,        # 8 data bits
    parity='N',        # No parity
    stopbits=1,        # 1 stop bit
    timeout=1          # Timeout for reading
)

# Function to send commands to the pump
def send_command(command):
    ser.write((command + '\r\n').encode())  # Send command with carriage return and newline
    response = ser.readline().decode().strip()  # Read the pump's response (if any)
    return response

# Read commands from a file
with open("commands.txt", "r") as file:
    for line in file:
        command = line.strip()  # Remove leading/trailing whitespace
        if command:  # Skip empty lines
            print("Sending command:", command)
            response = send_command(command)
            print("Response:", response)

# Close the serial connection
ser.close()
