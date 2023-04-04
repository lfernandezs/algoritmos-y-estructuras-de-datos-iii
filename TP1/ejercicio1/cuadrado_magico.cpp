#include "cuadrado_magico.h"

bool suma_numero_magico(vector<int> seccion, int n, int numero_magico) {
    for (int i = 0; i < n; i++) {
        if (seccion[i] != numero_magico) return false;
    }

    return true;
}

void imprimir_matriz(vector<vector<int>> matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

bool es_cuadrado_magico(vector<vector<int>> matriz, int n) {
    int numero_magico = ((int)pow(n, 3) + n) / 2;
    vector<int> suma_filas(n);
    vector<int> suma_columnas(n);
    vector<int> suma_diagonales(2);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            suma_filas[i] += matriz[i][j];
            suma_columnas[j] += matriz[i][j];

            if (i == j) suma_diagonales[0] += matriz[i][j];
            if (i + j == n - 1) suma_diagonales[1] += matriz[i][j];
        }
    }

    return suma_numero_magico(suma_filas, n, numero_magico)
           && suma_numero_magico(suma_columnas, n, numero_magico)
           && suma_numero_magico(suma_diagonales, 2, numero_magico);
}

bool suma_se_pasa(int n, vector<vector<int>> &solucion_parcial, int i, int j) {
    int numero_magico = ((int)pow(n, 3) + n) / 2;
    return suma_fila(solucion_parcial, i, j) > numero_magico
           || suma_columna(solucion_parcial, i, j) > numero_magico;
}

bool suma_no_alcanza(int n, vector<vector<int>> &solucion_parcial, int i, int j) {
    int numero_magico = ((int)pow(n, 3) + n) / 2;
    if (i == n-1) return suma_columna(solucion_parcial, i, j) < numero_magico;
    if (j == n-1) return suma_fila(solucion_parcial, i, j) < numero_magico;
    return false;
}

int suma_fila(vector<vector<int>> &solucion_parcial, int i, int j) {
    int suma = 0;
    for (int k = 0; k <= j; k++) suma += solucion_parcial[i][k];
    return suma;
}

int suma_columna(vector<vector<int>> &solucion_parcial, int i, int j) {
    int suma = 0;
    for (int k = 0; k <= i; k++) suma += solucion_parcial[k][j];
    return suma;
}