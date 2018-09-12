import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

plt.subplot(1, 2, 1)
plt.subplot(1, 2, 2)
plt.savefig('history.png')
