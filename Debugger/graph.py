import matplotlib.pyplot as plt
import numpy as np
import sys
# Initialize the x and y data lists
x_data = []
y_data = []

# Create a function to update the plot
def update_plot():
    plt.clf()
    plt.plot(x_data, y_data)
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Real-time Plot')
    plt.pause(0.01)  # Pause for a short time to update the plot

# Create an initial plot
plt.ion()  # Turn on interactive mode for real-time plotting
update_plot()

while True:
    user_input = input()
    if user_input.lower() == 'exit':
        break
    try:
        value = float(user_input)
        x_data.append(len(x_data))
        y_data.append(value)
        update_plot()
    except ValueError:
        print("Invalid input. Please enter a numeric value or 'exit' to quit.")

# Clean up and close the plot
plt.ioff()  # Turn off interactive mode
plt.show()
