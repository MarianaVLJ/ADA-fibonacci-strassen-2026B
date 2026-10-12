import matplotlib.pyplot as plt
import csv
import os

def leer_datos(archivo):
    n_vals, t1_vals, t2_vals = [], [], []
    if os.path.exists(archivo):
        with open(archivo, 'r') as f:
            reader = csv.reader(f)
            next(reader) # Saltar la cabecera
            for row in reader:
                n_vals.append(int(row[0]))
                t1_vals.append(int(row[1]))
                t2_vals.append(int(row[2]))
    return n_vals, t1_vals, t2_vals

# --- 1. Gráfico para Fibonacci ---
n_fibo, tiempo_On, tiempo_Ologn = leer_datos('resultados_fibonacci.txt')

if n_fibo:
    plt.figure(figsize=(10, 5))
    plt.plot(n_fibo, tiempo_On, marker='o', label='Iterativo - O(n)')
    plt.plot(n_fibo, tiempo_Ologn, marker='s', label='Matrices - O(log n)')
    plt.title('Análisis Empírico: Secuencia de Fibonacci')
    plt.xlabel('Tamaño de entrada (N)')
    plt.ylabel('Tiempo de ejecución (Microsegundos)')
    plt.legend()
    plt.grid(True)
    plt.savefig('grafico_fibonacci.png')
    plt.clf()

# --- 2. Gráfico para Multiplicación de Matrices ---
n_matrices, tiempo_On3, tiempo_Strassen = leer_datos('resultados_matrices.txt')

if n_matrices:
    plt.figure(figsize=(10, 5))
    plt.plot(n_matrices, tiempo_On3, marker='o', label='Clásico - O(n³)')
    plt.plot(n_matrices, tiempo_Strassen, marker='s', label='Strassen - O(n².81)')
    plt.title('Análisis Empírico: Multiplicación de Matrices')
    plt.xlabel('Tamaño de la matriz (NxN)')
    plt.ylabel('Tiempo de ejecución (Milisegundos)')
    plt.legend()
    plt.grid(True)
    plt.savefig('grafico_matrices.png')

print("Gráficos generados con éxito basándose en los archivos .txt")