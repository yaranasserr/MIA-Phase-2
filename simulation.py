import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

#important how to use the robot
#arrows keys to move up, down, left and right ONLY one press and the robot will move automaticly
# r button to rotate CCW
# t button to rotate CW
# y button to stop moving or rotating

class OmniWheelRobot:
    def __init__(self, Vx=1.0, Vy=0.0, omega=0.0, theta=0.0):
        self.wheel_radius = 0.5
        self.robot_radius = 2.0
        self.x = 0.0
        self.y = 0.0
        self.theta = theta
        self.Vx = Vx
        self.Vy = Vy
        self.omega = omega
        
    def calculate_wheel_positions(self):
        wheel_positions = []
        for angle in [np.pi / 6, np.pi / 6 + 2 * np.pi / 3, np.pi / 6 + 4 * np.pi / 3]:
            wheel_x = self.x + self.robot_radius * np.cos(self.theta + angle)
            wheel_y = self.y + self.robot_radius * np.sin(self.theta + angle)
            wheel_positions.append((wheel_x, wheel_y))
        return wheel_positions

    def update(self, frame):
        # Update the robot's pose
        self.theta += self.omega * 0.1
        self.x += ((self.Vx * np.cos(self.theta)) - (self.Vy * np.sin(self.theta))) * 0.1 
        self.y += ((self.Vx * np.sin(self.theta)) + (self.Vy * np.cos(self.theta))) * 0.1

        # Plot the robot
        ax.clear()
        
        # Plot robot body and orientation line
        ax.plot(self.x, self.y, 'bo')  # Robot body
        ax.plot([self.x, self.x + self.robot_radius * np.cos(self.theta+np.pi/2)],
                [self.y, self.y + self.robot_radius * np.sin(self.theta+np.pi/2)], 'r-') # Robot orientation line
        ax.plot([self.x, self.x + self.robot_radius * np.cos(self.theta)],
                [self.y, self.y + self.robot_radius * np.sin(self.theta)], 'b-') # Robot orientation line

        # Calculate and plot wheel positions
        wheel_positions = self.calculate_wheel_positions()
        for wheel_x, wheel_y in wheel_positions:
            ax.plot(wheel_x, wheel_y, 'go')  # Wheel points

        ax.set_xlim(-10, 10)  # Adjust the limits as needed
        ax.set_ylim(-10, 10)
        
        # Add grid
        ax.grid(True, linestyle='--', alpha=0.5)

    def set_velocities(self, Vx, Vy, omega):
        self.Vx = Vx
        self.Vy = Vy
        self.omega = omega

# Create an instance of the OmniWheelRobot class with initial values
robot = OmniWheelRobot(Vx=0.0, Vy=0.0, omega=0.0, theta=0.0)

fig, ax = plt.subplots()
ani = FuncAnimation(fig, robot.update, frames=range(100), interval=100)

# Function to handle keyboard input for velocity control
def on_key(event):
    if event.key == 'up':
        robot.set_velocities(Vx=0.0, Vy=1.0, omega=0.0)  # Move forward
    elif event.key == 'down':
        robot.set_velocities(Vx=0.0, Vy=-1.0, omega=0.0)  # Move backward
    elif event.key == 'left':
        robot.set_velocities(Vx=-1.0, Vy=0.0, omega=0.0)  # Move left
    elif event.key == 'right':
        robot.set_velocities(Vx=1.0, Vy=0.0, omega=0.0)  # Move right
    elif event.key == 'y':
        robot.set_velocities(Vx=0.0, Vy=0.0, omega=0.0)  # Stop
    elif event.key == 'r':
        robot.set_velocities(Vx=0.0, Vy=0.0, omega=0.2)  # Rotate right
    elif event.key == 't':
        robot.set_velocities(Vx=0.0, Vy=0.0, omega=-0.2)  # Rotate left
    fig.canvas.draw()

# Connect the keyboard input function
fig.canvas.mpl_connect('key_press_event', on_key)

plt.show()

