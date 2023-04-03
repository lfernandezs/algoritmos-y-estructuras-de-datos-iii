#include <iostream>
#include <vector>
#include <math.h>
#include <set>
using namespace std;

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

int k_esimo_cuadrado_magico(int k, int n, vector<vector<int>> &solucion_parcial, int i, int j, set<int> valores_disponibles) {
    if (i == n) {
        if (es_cuadrado_magico(solucion_parcial, n)) {
            imprimir_matriz(solucion_parcial, n);
            cout << endl;
        }
        return 0;
    }

    for (auto v : valores_disponibles) {
        solucion_parcial[i][j] = v;
        set<int> valores_disponibles_copy = set(valores_disponibles);
        valores_disponibles_copy.erase(v);
        k_esimo_cuadrado_magico(k, n, solucion_parcial, i + (int)(j+1 == n), (j+1) % n, valores_disponibles_copy);
    }
    
    return 0;
}

int main() {
    int k = 0, n = 4;
    // cin >> k >> n;
    vector<vector<int>> cuadrado_magico(n, vector<int>(n));
    set<int> valores_disponibles;
    for (int i = 0; i < n*n; i++) valores_disponibles.insert(i+1);
    k_esimo_cuadrado_magico(k, n, cuadrado_magico, 0, 0, valores_disponibles);
    return 0;
}