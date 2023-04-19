#include <iostream>
#include <vector>
#include <math.h>
#include <set>
#include <stdio.h>

using namespace std;

int c = 0, numero_magico;


void imprimir_matriz(vector<vector<int>> matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

bool es_cuadrado_magico(vector<vector<int>> &matriz, vector<int> &sumasFilas, vector<int> &sumasColumnas, int n) {
    bool filas = true, columnas = true;
    vector<int> suma_diagonales(2);

    for(int i = 0; i < n; i++)
    {
        if(sumasFilas[i] != numero_magico) filas = false;
        if(sumasColumnas[i] != numero_magico) columnas = false;
        suma_diagonales[0] += matriz[i][i];
        suma_diagonales[1] += matriz[i][n-1-i];
    }
    return filas
           && columnas
           && (suma_diagonales[0] == numero_magico)
           && (suma_diagonales[1] == numero_magico);
}

bool suma_se_pasa(int n, vector<int> &sumasFilas, vector<int> &sumasColumnas, int i, int j) {
    return sumasFilas[i] > numero_magico || sumasColumnas[j] > numero_magico;
}


bool suma_no_alcanza(int n, vector<int> &sumasFilas, vector<int> &sumasColumnas, int i, int j) {
    if (i == n-1) return sumasColumnas[j] < numero_magico;
    if (j == n-1) return sumasFilas[i] < numero_magico;
    return false;
}

/* *********************
 *  FUNCION PRINCIPAL  *
 * *********************/

// TODO: Se puede tener una variable global? Se puede hacer algo parecido pero usando
//  un parámetro?

void k_esimo_cuadrado_magico(int k, int n, vector<vector<int>> &solucion_parcial, int i, int j, vector<int> valores_usados, vector<int> &suma_filas, vector<int> &suma_columnas) {
    if (i == n) {
        if (es_cuadrado_magico(solucion_parcial, suma_filas, suma_columnas, n)) {
            c++;
            if (c == k) imprimir_matriz(solucion_parcial, n);
        }
        return;
    }

    // TODO: Hay alguna forma más eficiente de guardar los valores que no fueron usados?
    for (int v = 1; v <= n*n; v++) {
        if (!valores_usados[v-1]) { // O(log(n*n))
            solucion_parcial[i][j] = v;
            suma_filas[i] += v;
            suma_columnas[j] += v;
            if ( !suma_se_pasa(n, suma_filas, suma_columnas, i, j) && !suma_no_alcanza(n, suma_filas, suma_columnas, i, j) ) { // O(n)
                valores_usados[v-1] = 1; // O(log(n*n))
                k_esimo_cuadrado_magico(k, n, solucion_parcial, i + (int) (j + 1 == n), (j + 1) % n, valores_usados, suma_filas, suma_columnas);
                valores_usados[v-1] = 0; // O(log(n*n))
                if (c == k) return;
            }
            solucion_parcial[i][j] = 0;
            suma_filas[i] -= v;
            suma_columnas[j] -= v;
        }
    }

    if (i == 0 && j == 0 && c < k) printf("-1\n");
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    numero_magico = ((int)pow(n, 3) + n) / 2;
    vector<vector<int>> cuadrado_magico(n, vector<int>(n));
    vector<int> suma_filas(n, 0);
    vector<int> suma_columnas(n, 0);
    vector<int> valores_usados(n*n, 0);
    k_esimo_cuadrado_magico(k, n, cuadrado_magico, 0, 0, valores_usados, suma_filas, suma_columnas);
    return 0;
}