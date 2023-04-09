//
// Created by luli on 09/04/23.
//

#ifndef TP_1_CUADRADO_MAGICO_H
#define TP_1_CUADRADO_MAGICO_H

#include <iostream>
#include <vector>
#include <math.h>
#include <set>
using namespace std;

bool suma_numero_magico(vector<int> seccion, int n, int numero_magico);
void imprimir_matriz(vector<vector<int>> matriz, int n);
bool es_cuadrado_magico(vector<vector<int>> matriz, int n);
bool suma_se_pasa(int n, vector<vector<int>> &solucion_parcial, int i, int j);
bool suma_no_alcanza(int n, vector<vector<int>> &solucion_parcial, int i, int j);
int suma_fila(vector<vector<int>> &solucion_parcial, int i, int j);
int suma_columna(vector<vector<int>> &solucion_parcial, int i, int j);
void k_esimo_cuadrado_magico(int k, int n, vector<vector<int>> &solucion_parcial, int i, int j, set<int> valores_usados);

#endif //TP_1_CUADRADO_MAGICO_H
