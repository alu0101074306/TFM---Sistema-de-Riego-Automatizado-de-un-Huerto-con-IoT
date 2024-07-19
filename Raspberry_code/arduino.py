import serial
import time
import logging
from data import arduino_data, historical_data, parse_data

# Configurar la conexión serial con el Arduino
try:
    ser = serial.Serial('/dev/ttyAMA1', 9600, timeout=1)
except serial.SerialException as e:
    logging.error(f"No se pudo abrir el puerto: {e}")
    exit(1)

def send_time():
    while True:
        current_time = time.strftime("%H:%M")
        try:
            ser.write(f"SET_TIME:{current_time}\n".encode('utf-8'))
        except Exception as e:
            logging.error(f"Error sending time: {e}")
        time.sleep(60)

def request_data():
    while True:
        try:
            ser.write("REQUEST_DATA\n".encode('utf-8'))
            data = ser.readline().decode('utf-8').strip()
            if data:
                parse_data(data)
        except Exception as e:
            logging.error(f"Error requesting data: {e}")
        time.sleep(5)

def toggle_actuator(actuator):
    try:
        current_state = arduino_data[actuator]
        new_state = "OFF" if current_state == "ON" else "ON"
        ser.write(f"SET_{actuator.upper()}:{new_state}\n".encode('utf-8'))
        arduino_data[actuator] = new_state
    except Exception as e:
        logging.error(f"Error toggling actuator {actuator}: {e}")
