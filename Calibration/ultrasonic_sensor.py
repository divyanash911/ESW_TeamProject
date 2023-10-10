import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import LinearRegression

data = [(1.0, 2.1), (2.0, 3.9), (3.0, 6.0), (4.0, 8.1), (5.0, 9.8)]
# Random Data

x_data = np.array([x for x, y in data]).reshape(-1, 1)
y_data = np.array([y for x, y in data])

model = LinearRegression()
model.fit(x_data, y_data)

y_pred = model.predict(x_data)

plt.scatter(x_data, y_data, label="Data Points")

plt.plot(x_data, y_pred, color='red', label="Linear Regression Line")

plt.xlabel("Actual Distance")
plt.ylabel("Actual Distance Measured by Sensor")
plt.legend()

plt.title("Linear Regression")
plt.show()

print(f"Linear Relation: y = {model.coef_[0]:.2f}x + {model.intercept_:.2f}")
