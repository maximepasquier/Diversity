import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

import random
from itertools import count
from matplotlib.animation import FuncAnimation

# Lecture des fichiers
contamine = pd.read_csv("/home/maxime/Documents/Automate_Cellulaire/Diversity/Simulations/Systeme_1/data_csv/Humain_contamine.csv")
# genomeAP = pd.read_csv(r'/home/kilian/Documents/Automate_Cellulaire/Diversity/data/genomeAP.csv')
# genomeH = pd.read_csv(r'/home/kilian/Documents/Automate_Cellulaire/Diversity/data/genomeH.csv')
# hx = pd.read_csv(r'/home/kilian/Documents/Automate_Cellulaire/Diversity/data/hx.csv')
# hy = pd.read_csv(r'/home/kilian/Documents/Automate_Cellulaire/Diversity/data/hy.csv')
# immune = pd.read_csv(r'/home/kilian/Documents/Automate_Cellulaire/Diversity/data/immune.csv')

# print(contamine[:3])
# print(contamine[:3]['Humain_0'])
# print(contamine.iloc[:3,:3]) # access i,j coords
# sum_contamine = contamine.sum(axis=1)
# sum_contamine.plot(figsize=(15,10))
# plt.show()

t = np.arange(0.0, 2.0, 0.01)
s = 1 + np.sin(2 * np.pi * t)

fig, ax = plt.subplots()
ax.plot(t, s)

ax.set(xlabel='time (s)', ylabel='voltage (mV)',
       title='About as simple as it gets, folks')
ax.grid()

fig.savefig("test.png")
plt.show()


'''
def animate(i):
    contamine = pd.read_csv("/home/maxime/Documents/Automate_Cellulaire/Diversity/Simulations/Systeme_1/data_csv/Humain_contamine.csv")
    sum_contamine = contamine.sum(axis=1)
    plt.cla()
    plt.title("Contaminations")
    sum_contamine.plot(figsize=(15, 8))
    plt.xlabel("Itérations")
    plt.ylabel("Nombre d'infectés")
    plt.tight_layout()


ani = FuncAnimation(plt.gcf(), animate, interval=100)

plt.tight_layout()
plt.show()


contamine_data = pd.DataFrame(contamine)
ax = plt.gca()
contamine_data.plot(kind='line',y = 'Humain_6',ax=ax,color='red')
ax.set_xlabel("Index values")
ax.set_ylabel("Latitude values")
plt.title('Demo graph for Line plots')
plt.show()

contamine['Humain_0'].plot()
contamine.plot(figsize=(15,10))
plt.show()
'''