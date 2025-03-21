import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

file_path = 'data.csv'
data = pd.read_csv(file_path, header=None)

x_coords = data[1]
y_coords = data[2]

plt.figure()
plt.plot(x_coords, y_coords, marker='o', linestyle='-')

plt.xlabel('X')
plt.ylabel('Y')
plt.title('Plot of Data.csv')

plt.savefig("data_plot.jpg")
plt.show()

angles = []
for i in range(1, len(x_coords) - 1):
    # Vectors between consecutive points
    vec1 = np.array([x_coords[i] - x_coords[i-1], y_coords[i] - y_coords[i-1]])
    vec2 = np.array([x_coords[i+1] - x_coords[i], y_coords[i+1] - y_coords[i]])
    
    # Calculate the angle between the vectors
    angle = np.arctan2(vec2[1], vec2[0]) - np.arctan2(vec1[1], vec1[0])
    angles.append(angle)

# Plot the histogram of angles
plt.figure()
plt.hist(angles, bins=30, edgecolor='black')
plt.xlabel('Angle')
plt.ylabel('Frequency')
plt.title('Histogram of Angles Between Consecutive Lines')
plt.savefig("angles_histogram.jpg")
plt.show()