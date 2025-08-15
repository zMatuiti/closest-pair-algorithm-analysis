import pandas as pd
import matplotlib.pyplot as plt

# Abre el archivo CSV
df = pd.read_csv('./uhr/results.csv')

# Crea el gráfico
plt.plot(df['n'], df['brute_force'], label='Brute Force', marker='o')
plt.plot(df['n'], df['divide_conquer'], label='Divide and Conquer', marker='s')

# Etiquetas para los ejes
plt.xlabel('n (Cantidad de puntos)')
plt.ylabel('Tiempo de ejecución (nanosegundos)')

# Usar escala logarítmica en el eje y
plt.yscale('log')

# Mostrar leyenda
plt.legend()

# Guardar el gráfico en un archivo
plt.savefig('plot.png')
