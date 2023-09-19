import serial
from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.font_manager import FontProperties
import numpy as np
import csv

arduino = serial.Serial('COM5', 9600)

max_points = 50
horizontal_line_ys = [-4,-2, 0, 2,4]
x_data = np.arange(max_points)
y_data = np.zeros((3, max_points))
csv_file = open('acceleration_data.csv', mode='w', newline='')
csv_writer = csv.writer(csv_file)
csv_writer.writerow(['X', 'Y', 'Z']) 

fig, ax = plt.subplots()
lines = [ax.plot([], [], label=label)[0] for label in ['Acceleration sensor','','']]

lines[0].set_color('black')  
lines[1].set_color('black') 
lines[2].set_color('black')
ax.set_xlim(0, max_points - 1)
ax.set_ylim(-6, 6)
ax.set_xlabel('Time')
ax.set_ylabel('Acceleration (m/s^2)')
for y_val in horizontal_line_ys:
    ax.axhline(y=y_val, color='black', linestyle='-',  linewidth=0.3)
ax.set_title('Accelerometer Data')
legend_font = FontProperties(weight='bold') 
ax.legend(frameon=False, prop=legend_font) 
def init():
    for line in lines:
        line.set_data([], [])
    return lines

def animate(i):
    global x_data, y_data
    accel_data = arduino.readline().decode().strip().split('\t')    
    if len(accel_data) == 3:
        accel_values = [float(val) for val in accel_data]
        y_data = np.roll(y_data, shift=-1, axis=1)
        y_data[:, -1] = accel_values

        csv_writer.writerow(accel_values)
        for i, line in enumerate(lines):
            line.set_data(x_data, y_data[i])

    return lines

ani = FuncAnimation(fig, animate, init_func=init, interval=100, blit=True)

plt.show()

arduino.close()
csv_file.close()