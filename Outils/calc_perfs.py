# https://colab.research.google.com/drive/1GTDBP2MmMi87wtkQUu7YCjUbGFapTd_A?authuser=0#scrollTo=VnSML33jDuvk

import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

textures = np.array([100, 1000, 10000, 20000, 30000, 40000, 50000, 75000, 100000])
init_times = np.array([0.300000, 0.303000, 0.439000, 0.848000, 1.511000, 2.582000, 4.182000, 9.641000, 19.554001])
render_times = np.array([0.002000, 0.002000, 0.012000, 0.018000, 0.025000, 0.044000, 0.056000, 0.075000, 0.094000])

# Création de la figure et de l'axe
fig, ax = plt.subplots()

ax.plot(init_times, textures, label="Temps d'initialisation", color="blue", marker='o')
ax.plot(render_times, textures, label="Temps de rendu", color="green", marker='o')

# Configuration des axes
ax.set_xscale('log')
ax.set_yscale('log')
ax.set_xlabel('Temps (secondes)')
ax.set_ylabel('Nombre de textures')
ax.legend()
ax.grid(True, which="both", ls="--")

plt.show()
