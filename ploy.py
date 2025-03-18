import pandas as pd
import matplotlib.pyplot as plt

file_path = 'data.csv'
data = pd.read_csv(file_path, header=None)

x_coords = data[1]
y_coords = data[2]

plt.figure()
plt.plot(x_coords, y_coords, marker='o', linestyle='-')

plt.xlabel('X')
plt.ylabel('Y')
plt.title('Plot of Data.csv')

# plt.grid(True)
plt.show()