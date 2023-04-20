cmake_minimum_required(VERSION 3.25)
project(tp_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(ejercicio_1 ejercicio-1/cuadrado_magico.cpp ejercicio-1/cuadrado_magico.h ejercicio-3/actividades.cpp experimentación/time_algorithm.cpp)
add_executable(ejercicio_2 ejercicio-2/polinomio_resto.cpp ejercicio-2/polinomio_resto.h)
add_executable(ejercicio_3 ejercicio-3/actividades.cpp)