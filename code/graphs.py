import json
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.pyplot import figure
with open('history.json') as f:
    history = json.load(f)
x = [i for i in range(len(history['acc']))]
figure(figsize=(8, 3))
plt.subplot(1, 2, 1)
plt.grid(True)
plt.plot(x, history['acc'], color='#4ead78')
plt.xlabel('epoch')
plt.ylabel('accuracy')
plt.subplot(1, 2, 2)
plt.grid(True)
plt.plot(x, history['loss'], color='#d12727')
plt.xlabel('epoch')
plt.ylabel('loss')
plt.savefig('../images/history.png', bbox_inches='tight')
