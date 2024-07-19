from dash import callback_context
from dash.dependencies import Input, Output
from arduino import toggle_actuator
from data import arduino_data, historical_data
import plotly.graph_objs as go

def register_callbacks(app):

    # Callbacks para la pestaña de Status
    @app.callback(
        [Output('temperature', 'children'),
         Output('humidity', 'children'),
         Output('pressure', 'children'),
         Output('index_temp', 'children'),
         Output('wind_speed', 'children'),
         Output('wind_direction', 'children'),
         Output('uv_index', 'children'),
         Output('water_present', 'children'),
         Output('riego', 'children'),
         Output('purgado', 'children'),
         Output('llenado', 'children'),
         Output('foco', 'children'),
         Output('tank_level', 'children'),
         Output('caudal', 'children'),
         Output('humsustrato', 'children'),
         Output('hora', 'children')],
        [Input('interval-component', 'n_intervals')]
    )
    def update_status(n):
        return (f"{arduino_data['temperature']}",
                f"{arduino_data['humidity']}",
                f"{arduino_data['pressure']}",
                f"{arduino_data['index_temp']}",
                f"{arduino_data['wind_speed']}",
                f"{arduino_data['wind_direction']}°",
                f"UV: {arduino_data['uv_index']}",
                f"Agua: {arduino_data['water_present']}",
                f"Riego: {arduino_data['riego']}",
                f"Purgado: {arduino_data['purgado']}",
                f"Llenado: {arduino_data['llenado']}",
                f"Foco: {arduino_data['foco']}",
                f"Nivel: {arduino_data['tank_level']}",
                f"Caudal: {arduino_data['caudal']}",
                f"H. Sustrato: {arduino_data['humsustrato']}",
                arduino_data["hora"])

    # Callbacks para la pestaña de Monitor
    @app.callback(
        [Output('temperature-graph', 'figure'),
         Output('humidity-graph', 'figure'),
         Output('pressure-graph', 'figure'),
         Output('wind_speed-graph', 'figure'),
         Output('wind_direction-graph', 'figure')],
        [Input('interval-graph', 'n_intervals')]
    )
    def update_graphs(n):
        temperature_trace = go.Scatter(
            x=historical_data["timestamps"],
            y=historical_data["temperature"],
            mode='lines+markers',
            name='Temperatura'
        )

        humidity_trace = go.Scatter(
            x=historical_data["timestamps"],
            y=historical_data["humidity"],
            mode='lines+markers',
            name='Humedad'
        )

        pressure_trace = go.Scatter(
            x=historical_data["timestamps"],
            y=historical_data["pressure"],
            mode='lines+markers',
            name='Presión'
        )

        wind_speed_trace = go.Scatter(
            x=historical_data["timestamps"],
            y=historical_data["wind_speed"],
            mode='lines+markers',
            name='Velocidad del viento'
        )

        wind_direction_trace = go.Scatter(
            x=historical_data["timestamps"],
            y=historical_data["wind_direction"],
            mode='lines+markers',
            name='Dirección del viento'
        )

        temperature_layout = go.Layout(title='Temperatura', xaxis=dict(title='Tiempo'), yaxis=dict(title='Celsius'))
        humidity_layout = go.Layout(title='Humedad', xaxis=dict(title='Tiempo'), yaxis=dict(title='%'))
        pressure_layout = go.Layout(title='Presión', xaxis=dict(title='Tiempo'), yaxis=dict(title='hPa'))
        wind_speed_layout = go.Layout(title='Velocidad del viento', xaxis=dict(title='Tiempo'), yaxis=dict(title='km/h'))
        wind_direction_layout = go.Layout(title='Dirección del viento', xaxis=dict(title='Tiempo'), yaxis=dict(title='Grados'))

        temperature_fig = go.Figure(data=[temperature_trace], layout=temperature_layout)
        humidity_fig = go.Figure(data=[humidity_trace], layout=humidity_layout)
        pressure_fig = go.Figure(data=[pressure_trace], layout=pressure_layout)
        wind_speed_fig = go.Figure(data=[wind_speed_trace], layout=wind_speed_layout)
        wind_direction_fig = go.Figure(data=[wind_direction_trace], layout=wind_direction_layout)

        return temperature_fig, humidity_fig, pressure_fig, wind_speed_fig, wind_direction_fig

    # Callbacks para la pestaña de Actuadores
    @app.callback(
        [Output('riego_status', 'children'),
         Output('purgado_status', 'children'),
         Output('llenado_status', 'children'),
         Output('foco_status', 'children')],
        [Input('REGAR', 'n_clicks'),
         Input('PURGAR', 'n_clicks'),
         Input('LLENAR', 'n_clicks'),
         Input('FOCO', 'n_clicks')]
    )
    def update_actuators(riego_clicks, purgado_clicks, llenado_clicks, foco_clicks):
        ctx = callback_context

        if not ctx.triggered:
            button_id = 'No clicks yet'
        else:
            button_id = ctx.triggered[0]['prop_id'].split('.')[0]

        if button_id == 'REGAR':
            toggle_actuator('riego')
        elif button_id == 'PURGAR':
            toggle_actuator('purgado')
        elif button_id == 'LLENAR':
            toggle_actuator('llenado')
        elif button_id == 'FOCO':
            toggle_actuator('foco')

        return (f"Riego: {arduino_data['riego']}",
                f"Purgado: {arduino_data['purgado']}",
                f"Llenado: {arduino_data['llenado']}",
                f"Foco: {arduino_data['foco']}")
