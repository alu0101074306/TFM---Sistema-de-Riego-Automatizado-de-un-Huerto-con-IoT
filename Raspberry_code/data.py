import time
import re
import logging

arduino_data = {
    "temperature": "0",
    "humidity": "0",
    "pressure": "0",
    "index_temp": "0",
    "wind_speed": "0",
    "wind_direction": "0",
    "uv_index": "0",
    "water_present": "No",
    "riego": "OFF",
    "purgado": "OFF",
    "llenado": "OFF",
    "foco": "OFF",
    "tank_level": "0",
    "caudal": "0",
    "humsustrato": "0",
    "hora": "00:00"
}

historical_data = {
    "temperature": [],
    "humidity": [],
    "pressure": [],
    "wind_speed": [],
    "wind_direction": [],
    "timestamps": []
}

def parse_data(data):
    global arduino_data, historical_data
    try:
        parts = data.split(',')
        for part in parts:
            if ':' in part:
                key, value = part.split(':', 1)
                key = key.strip().lower().replace(" ", "_")
                arduino_data[key] = value.strip()

        timestamp = time.strftime("%H:%M:%S")
        historical_data["timestamps"].append(timestamp)

        try:
            historical_data["temperature"].append(float(re.sub(r'[^\d.]+', '', arduino_data["temperature"])))
        except ValueError:
            historical_data["temperature"].append(0)

        try:
            historical_data["humidity"].append(float(re.sub(r'[^\d.]+', '', arduino_data["humidity"])))
        except ValueError:
            historical_data["humidity"].append(0)

        try:
            historical_data["pressure"].append(float(re.sub(r'[^\d.]+', '', arduino_data["pressure"])))
        except ValueError:
            historical_data["pressure"].append(0)

        try:
            historical_data["wind_speed"].append(float(re.sub(r'[^\d.]+', '', arduino_data["wind_speed"])))
        except ValueError:
            historical_data["wind_speed"].append(0)

        try:
            historical_data["wind_direction"].append(float(re.sub(r'[^\d.]+', '', arduino_data["wind_direction"])))
        except ValueError:
            historical_data["wind_direction"].append(0)

        if len(historical_data["timestamps"]) > 100:
            for key in historical_data:
                historical_data[key].pop(0)
    except Exception as e:
        logging.error(f"Error parsing data: {e}")
