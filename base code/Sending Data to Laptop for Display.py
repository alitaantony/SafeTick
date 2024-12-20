import serial

# Open serial connection
ser = serial.Serial('/dev/ttyUSB0', 115200)

while True:
    if ser.in_waiting:
        data = ser.readline().decode('utf-8').strip()
        print(f"Emotion Prediction: {data}")
