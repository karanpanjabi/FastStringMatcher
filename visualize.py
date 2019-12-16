import matplotlib.pyplot as plt

low_3 = 1
high_3 = 255

low_2 = 1 << 8
high_2 = 255 << 8 | 255

low_1 = 1 << 16
high_1 = 255 << 16 | 255 << 8 | 255

# x = [0, low_3, high_3, low_2, high_2, low_1, high_1]
# y = [4, 3, 3, 2, 2, 1, 1]

x = [1, 1 << 8, 1 << 16]
y = [3, 2, 1]

import math

xn = [math.log(i, 256) for i in x]

# plt.plot(x, y, 'bo')
plt.plot(xn, y, 'ro')
plt.show()