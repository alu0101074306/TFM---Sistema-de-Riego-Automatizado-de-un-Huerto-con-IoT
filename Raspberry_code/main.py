import dash
from dash import dcc, html
import dash_bootstrap_components as dbc
import threading
import logging
from arduino import send_time, request_data
from layout import layout
from callbacks import register_callbacks

# Configurar el logger
logging.basicConfig(level=logging.INFO)

# Iniciar hilos para enviar hora y solicitar datos
threading.Thread(target=send_time, daemon=True).start()
threading.Thread(target=request_data, daemon=True).start()

# Configuración de la aplicación Dash
app = dash.Dash(__name__, external_stylesheets=[dbc.themes.BOOTSTRAP])
app.layout = layout
register_callbacks(app)

if __name__ == '__main__':
    app.run_server(debug=True, host='0.0.0.0')
