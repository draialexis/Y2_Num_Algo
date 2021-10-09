import numpy as np
import matplotlib.pyplot as plt

x_t = [
    0,
    2,
    4,
    6,
    8,
    10,
    12,
    14,
    16,
    18,
    20,
    22,
    24,
    26,
    28,
    30,
    32,
    34,
    36,
    38
]
y_d = [
    0.99987,
    0.99997,
    1.00000,
    0.99997,
    0.99988,
    0.99973,
    0.99953,
    0.99927,
    0.99897,
    0.99846,
    0.99805,
    0.99751,  # 0.999751,#error
    0.99705,
    0.99650,
    0.99664,  # 0.99664,#error?
    0.99533,
    0.99472,
    0.99472,  # 0.99472,#error?
    0.99333,
    0.99326
]

curve = np.polyfit(x_t, y_d, 2)
poly = np.poly1d(curve)

new_x_t = []
new_y_d = []
# for i in range(0, 20):
for i in range(0, 50):
    new_x_t.append(i * 2)
    new_y_d.append(poly(i * 2))

plt.plot(new_x_t, new_y_d, "red")
plt.scatter(x_t, y_d, 100)
plt.show()
