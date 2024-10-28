import serial
import time
import requests


arduino_port = 'COM5'  # Pode ser diferente, cheque o gerenciador de dispositivos
baud_rate = 9600

ser = serial.Serial(arduino_port, baud_rate, timeout=1)
time.sleep(2)  # Aguarde a conexão estabilizar

def read_data():
    try:
        data = ser.readline().decode('utf-8').strip()
        if data:
            print(data)
            parts = data.split(",")
            distancia = float(parts[0].split(":")[1].strip())
            temperatura = float(parts[1].split(":")[1].strip())
            pureza = float(parts[2].split(":")[1].strip())

            payload = {'temperatura': temperatura, 'nivel': distancia, 'pureza': pureza}
            response = requests.post('http://localhost/sensor_data/insert_data.php', json=payload)
            print(response.text)
    except Exception as e:
        print(f"Erro ao ler ou enviar dados: {e}")

def close_connection():
    ser.close()
    print("Conexão serial fechada")

try:
    while True:
        read_data()
        time.sleep(2)
except KeyboardInterrupt:
    close_connection()
