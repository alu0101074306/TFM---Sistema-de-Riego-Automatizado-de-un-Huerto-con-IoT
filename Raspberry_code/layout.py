from dash import dcc, html
import dash_bootstrap_components as dbc

layout = html.Div([
    dcc.Tabs([
        dcc.Tab(label='Status', children=[
            dcc.Interval(id='interval-component', interval=1*1000, n_intervals=0),
            dbc.Container([
                dbc.Row([dbc.Col(html.H1("Estado Huerto IoT", className="text-center mb-4"))]),
                dbc.Row([
                    dbc.Col(html.Div([html.H4("Temperatura:"), html.P(id='temperature')])),
                    dbc.Col(html.Div([html.H4("Humedad:"), html.P(id='humidity')])),
                    dbc.Col(html.Div([html.H4("Presión:"), html.P(id='pressure')])),
                    dbc.Col(html.Div([html.H4("Índice de calor:"), html.P(id='index_temp')]))
                ]),
                dbc.Row([
                    dbc.Col(html.Div([html.H4("Velocidad del viento:"), html.P(id='wind_speed')])),
                    dbc.Col(html.Div([html.H4("Dirección del viento:"), html.P(id='wind_direction')])),
                    dbc.Col(html.Div([html.H4("Índice UV:"), html.P(id='uv_index')])),
                    dbc.Col(html.Div([html.H4("Agua presente:"), html.P(id='water_present')]))
                ]),
                dbc.Row([
                    dbc.Col(html.Div([html.H4("Riego:"), html.P(id='riego')])),
                    dbc.Col(html.Div([html.H4("Purgado:"), html.P(id='purgado')])),
                    dbc.Col(html.Div([html.H4("Llenado:"), html.P(id='llenado')])),
                    dbc.Col(html.Div([html.H4("Foco:"), html.P(id='foco')]))
                ]),
                dbc.Row([
                    dbc.Col(html.Div([html.H4("Nivel del tanque:"), html.P(id='tank_level')])),
                    dbc.Col(html.Div([html.H4("Caudal:"), html.P(id='caudal')])),
                    dbc.Col(html.Div([html.H4("Humedad del sustrato:"), html.P(id='humsustrato')])),
                    dbc.Col(html.Div([html.H4("Hora:"), html.P(id='hora')]))
                ])
            ])
        ]),
        dcc.Tab(label='Monitor', children=[
            dcc.Interval(id='interval-graph', interval=1*1000, n_intervals=0),
            dbc.Container([
                dbc.Row([dbc.Col(dcc.Graph(id='temperature-graph'))]),
                dbc.Row([dbc.Col(dcc.Graph(id='humidity-graph'))]),
                dbc.Row([dbc.Col(dcc.Graph(id='pressure-graph'))]),
                dbc.Row([dbc.Col(dcc.Graph(id='wind_speed-graph'))]),
                dbc.Row([dbc.Col(dcc.Graph(id='wind_direction-graph'))]),
            ])
        ]),
        dcc.Tab(label='Actuadores', children=[
            dbc.Container([
                dbc.Row([dbc.Col(html.H1("Control de Actuadores", className="text-center mb-4"))]),
                dbc.Row([
                    dbc.Col(html.Div([html.H4("Riego:"), html.P(id='riego_status'), dbc.Button("REGAR", id='REGAR', color="primary")])),
                    dbc.Col(html.Div([html.H4("Purgado:"), html.P(id='purgado_status'), dbc.Button("PURGAR", id='PURGAR', color="primary")])),
                    dbc.Col(html.Div([html.H4("Llenado:"), html.P(id='llenado_status'), dbc.Button("LLENAR", id='LLENAR', color="primary")])),
                    dbc.Col(html.Div([html.H4("Foco:"), html.P(id='foco_status'), dbc.Button("FOCO", id='FOCO', color="primary")]))
                ])
            ])
        ])
    ])
])
