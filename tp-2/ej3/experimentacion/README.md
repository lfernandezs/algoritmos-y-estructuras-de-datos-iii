**Cómo obtener los gráficos:**
1. `generate_random_instances.py` tiene dos funciones, que generan un archivo `inputs/input.csv` con instancias aleatorias, ordenadas o desordenadas. Llamar a ese script para generarlas.

2. `time_algorithm` toma ese archivo generado y ejecuta el ejercicio 3 para cada instancia. En `output_*.csv` escribe los tiempos para cada tamaño de instancia.

3. `experimentacion.ipynb` grafica los resultados de `output_*.csv`.
