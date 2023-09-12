r = .01 #meter wheel radius 
b = .02 #meter robot radius
import matplotlib.pyplot as plt
import numpy as np
"""
forward Kinematic 
w1 = 255 #  rad/s
w2 = 255 #  rad/s
w3 = 255 #  rad/s

v1 = w1 * r
v2 = w2 * r
v3 = w3 * r

alpha1 = 30 # degreer
alpha2 = 150 # degree
alpha3 = 270 # degree

v = np.array([[v1],
              [v2],
              [v3]])

k = np.array([[np.cos((alpha1+90) * (np.pi/180)),np.cos((alpha2+90) * (np.pi/180)),np.cos((alpha3+90) * (np.pi/180))],
             [np.sin((alpha1+90) * (np.pi/180)),np.sin((alpha2+90) * (np.pi/180)),np.sin((alpha3+90) * (np.pi/180))],
             [1/b,1/b,1/b]])

vl = k @ v 
print(f"vl: \n{np.round(vl,2)}")
"""

#inverse Kinematic

alpha1 = 30 # degree
alpha2 = 150 # degree
alpha3 = 270 # degree

vx = int(input("Enter Vx = ")) # m/s
vy = int(input("Enter Vy = ")) # m/s
w = int(input("Enter W = ")) # rad/s

vl = np.array([[vx],
              [vy],
              [w]])

k = np.array([[np.cos((alpha1+90) * (np.pi/180)),np.cos((alpha2+90) * (np.pi/180)),np.cos((alpha3+90) * (np.pi/180))],
             [np.sin((alpha1+90) * (np.pi/180)),np.sin((alpha2+90) * (np.pi/180)),np.sin((alpha3+90) * (np.pi/180))],
             [1/b,1/b,1/b]])


v = np.linalg.inv(k) @ vl # m/s
print(f"v: \n{np.round(v,2)}")

angular_velo = v/r
print(f"angular_velo: \n{np.round(angular_velo,2)}") # rad/s

rpm = (angular_velo*60)/(2*np.pi)
print(f"rpm of each motor: \n{np.round(rpm,2)}") # rpm

theta = 0
rot = np.array([[np.cos(theta * (np.pi/180)),-np.sin(theta * (np.pi/180)),0],
             [np.sin(theta * (np.pi/180)),np.cos(theta * (np.pi/180)),0],
             [0,0,1]])

vg = rot @ vl
print(f"vg: \n{np.round(vg,2)}")








