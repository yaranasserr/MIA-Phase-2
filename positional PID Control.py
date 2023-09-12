import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt
import numpy as np
import math 
import time as t

#initialize robot robot_radius, theta and omega 
robot_radius = 2.0
theta = 0
w = .1

#this section for Create positional PID Control that takes the target position and executes an instruction to got to this position
#take from user target position
x_position = float(input("Enter x_position = ")) 
y_position = float(input("Enter y_position = ")) 
#initialize lists to store data
draw_x = []
draw_y = []
draw_theta = []
#initialize robot initial position
robot_position = [0,0]
#calculate length between robot and the target position
l =  math.sqrt(x_position**2+y_position**2)
#initialize past err
past_err = (abs(x_position-robot_position[0])+abs(y_position-robot_position[1]))/2

#phi is the angle of the target position
#ensure that if the positon_x ==0 dont make an error and make angle start from positive x axis
if (x_position==0 and y_position>=0):
    phi= np.pi/2
elif((x_position==0) and (y_position<0)):
    phi= 3*np.pi/2
elif(x_position<0):
    phi = np.arctan(y_position/x_position) + np.pi
else:
    phi = np.arctan(y_position/x_position) 

#first move robot to the target position
while(1):
    #calculate length between robot and the target position 
    l_from_robot_position = math.sqrt(robot_position[0]**2+robot_position[1]**2)
    #calculate the error
    err = (abs(x_position-robot_position[0])+abs(y_position-robot_position[1]))/2
    #print(err)
    #calculating velocity and using positional PID Control 
    x_velo = x_position * (l-l_from_robot_position)*.5+ ((err-past_err)/.01)*.001
    y_velo = y_position * (l-l_from_robot_position)*.5+ ((err-past_err)/.01)*.001
    #update robot position
    robot_position[0] += ((x_velo * np.cos(theta)) - (y_velo * np.sin(theta))) * 0.01 
    robot_position[1] += ((x_velo * np.sin(theta)) + (y_velo * np.cos(theta))) * 0.01
    #store the robot position on each iteration
    draw_x.append(robot_position[0])
    draw_y.append(robot_position[1])
    #break the loop if the err is less than certain value (.05)
    if (err<.05) :
        break
    past_err = err
    #make a delay
    t.sleep(.01)

while(1):
    #print(theta)
    #update theta and break when the err is less than certain value (.01)
    if (abs((phi-np.pi/2)-theta)<.01):
        draw_theta.append(theta)
        break
    else:
        theta += w*((phi-np.pi/2)-theta)
        draw_theta.append(theta) 

#ensute that the draw_x , draw_y and draw_theta are the same size
size_diff = len(draw_x) - len(draw_theta)
if size_diff > 0:
    # Append the last element of array2 multiple times to make it the same size as array1
    fill_value = draw_theta[-1]  # Get the last element of array2
    draw_theta = np.append(draw_theta, [fill_value] * size_diff)
elif size_diff < 0:
    # Append the last element of array1 multiple times to make it the same size as array2
    fill_value = draw_x[-1]  # Get the last element of array1
    draw_x = np.append(draw_x, [fill_value] * abs(size_diff))
    fill_value = draw_y[-1]  # Get the last element of array1
    draw_y = np.append(draw_y, [fill_value] * abs(size_diff))





#this function is to locate where is the wheels of robot are
def calculate_wheel_positions(x, y, theta):
    wheel_positions = []
    for angle in [np.pi / 6, np.pi / 6 + 2 * np.pi / 3, np.pi / 6 + 4 * np.pi / 3]:
        wheel_x = x + robot_radius * np.cos(theta + angle)
        wheel_y = y + robot_radius * np.sin(theta + angle)
        wheel_positions.append((wheel_x, wheel_y))
    return wheel_positions
#updating the plot view using update fun
def update(frame):
    x, y, theta = draw_x[frame], draw_y[frame], draw_theta[frame]

    #clear plot to plot the new values
    ax.clear()
    
    # Plot robot body and orientation lines
    ax.plot(x, y, 'bo')  # Robot body
    ax.plot([x, x + robot_radius * np.cos(theta + np.pi/2)],
            [y, y + robot_radius * np.sin(theta + np.pi/2)], 'r-')  # Robot orientation line (y-axis)
    ax.plot([x, x + robot_radius * np.cos(theta)],
            [y, y + robot_radius * np.sin(theta)], 'b-')  # Robot orientation line (x-axis)

    # Calculate and plot wheel positions
    wheel_positions = calculate_wheel_positions(x, y, theta)
    for wheel_x, wheel_y in wheel_positions:
        ax.plot(wheel_x, wheel_y, 'go')  # Wheel points
    #draw a X symbol at the target position
    ax.text(x_position, y_position, 'X', color='red', fontsize=12, ha='center', va='center')
    # Adjust the limits
    ax.set_xlim(-10, 10)  
    ax.set_ylim(-10, 10)
    
    # Add grid
    ax.grid(True, linestyle='--', alpha=0.5)
#plot
fig, ax = plt.subplots()
ani = FuncAnimation(fig, update, frames=range(len(draw_x)), interval=100)
plt.show()






    












      











