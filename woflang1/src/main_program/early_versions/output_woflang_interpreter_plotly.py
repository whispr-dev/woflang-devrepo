import plotly.graph_objs as go
import plotly.io as pio

# Assuming you have the `variables_history` from your script
variables_history = [
{'i_1': 20.0},
{'i_1': 20.0, 'i_2': 10.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0, 'v_B': 45.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0, 'v_B': 45.0, 'theta_B': 50.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0, 'v_B': 45.0, 'theta_B': 50.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0, 'v_B': 45.0, 'theta_B': 50.0, 'a_B': 0.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0, 'v_B': 45.0, 'theta_B': 50.0, 'a_B': 0.0, 'i_1_C': 0.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0, 'v_B': 45.0, 'theta_B': 50.0, 'a_B': 0.0, 'i_1_C': 0.0, 'i_2_C': 0.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0, 'v_B': 45.0, 'theta_B': 50.0, 'a_B': 0.0, 'i_1_C': 0.0, 'i_2_C': 0.0, 'w_1_C': 1.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0, 'v_B': 45.0, 'theta_B': 50.0, 'a_B': 0.0, 'i_1_C': 0.0, 'i_2_C': 0.0, 'w_1_C': 1.0, 'w_2_C': -0.5},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0, 'v_B': 45.0, 'theta_B': 50.0, 'a_B': 0.0, 'i_1_C': 0.0, 'i_2_C': 0.0, 'w_1_C': 1.0, 'w_2_C': -0.5, 'v_C': 0.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0, 'v_B': 45.0, 'theta_B': 50.0, 'a_B': 0.0, 'i_1_C': 0.0, 'i_2_C': 0.0, 'w_1_C': 1.0, 'w_2_C': -0.5, 'v_C': 0.0, 'theta_C': -5.0},
 {'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0, 'v_B': 45.0, 'theta_B': 50.0, 'a_B': 0.0, 'i_1_C': 0.0, 'i_2_C': 0.0, 'w_1_C': 1.0, 'w_2_C': -0.5, 'v_C': 0.0, 'theta_C': -5.0},
{'i_1': 20.0, 'i_2': 10.0, 'w_1': 0.0, 'w_2': 1.0, 'v_A': 10.0, 'theta_A': 15.0, 'a_A': 0.0, 'i_1_B': -30.0, 'i_2_B': 40.0, 'w_1_B': -1.5, 'w_2_B': 0.0, 'v_B': 45.0, 'theta_B': 50.0, 'a_B': 0.0, 'i_1_C': 0.0, 'i_2_C': 0.0, 'w_1_C': 1.0, 'w_2_C': -0.5, 'v_C': 0.0, 'theta_C': -5.0, 'a_C': 0.0},
# ... Add the rest of your variables_history here
]

# Prepare data for Plotly
traces = []
variable_names = set()  # Set to track all variable names

# Collect all variable names
for step in variables_history:
    for key in step.keys():
        variable_names.add(key)

# Create traces for each variable
for var_name in variable_names:
    x = []
    y = []
    for step, vars_at_step in enumerate(variables_history):
        if var_name in vars_at_step:
            x.append(step)
            y.append(vars_at_step[var_name])
        else:
            # Fill with None if the variable was not defined at this step
            x.append(step)
            y.append(None)
    traces.append(go.Scatter(x=x, y=y, mode='lines+markers', name=var_name))

# Create layout
layout = go.Layout(
    title='Variable Changes Over Time',
    xaxis=dict(title='Command Index'),
    yaxis=dict(title='Variable Value'),
    hovermode='closest'
)

# Create figure and plot it
fig = go.Figure(data=traces, layout=layout)
pio.show(fig)  # This will open the plot in your default web browser
