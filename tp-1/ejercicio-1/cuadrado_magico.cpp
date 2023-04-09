#include "cuadrado_magico.h"

/* ************************
 *  FUNCIONES AUXILIARES  *
 * ************************/

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

// TODO: ver el nombre.
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

/* *********************
 *  FUNCION PRINCIPAL  *
 * *********************/

// TODO: Se puede tener una variable global? Se puede hacer algo parecido pero usando
//  un parámetro?
int r = 0;

void k_esimo_cuadrado_magico(int k, int n, vector<vector<int>> &solucion_parcial, int i, int j, set<int> valores_usados) {
    if (i == n) {
        if (es_cuadrado_magico(solucion_parcial, n)) {
            r++;
            if (r == k) imprimir_matriz(solucion_parcial, n);
        }
        return;
    }

    // TODO: Hay alguna forma más eficiente de guardar los valores que no fueron usados?
    for (int v = 1; v <= n*n; v++) {
        if (!valores_usados.count(v)) { // O(log(n*n))
            solucion_parcial[i][j] = v;
            if ( !suma_se_pasa(n, solucion_parcial, i, j) && !suma_no_alcanza(n, solucion_parcial, i, j) ) { // O(n)
//                set<int> valores_usados_copy(valores_usados); // O(n*n)
//                valores_usados_copy.insert(v); // O(log(n*n))
                valores_usados.insert(v); // O(log(n*n))
                k_esimo_cuadrado_magico(k, n, solucion_parcial, i + (int) (j + 1 == n), (j + 1) % n, valores_usados);
                valores_usados.erase(v); // O(log(n*n))
                if (r == k) return;
            }
        }
    }

    if (i == 0 && j == 0 && r < k) cout << -1;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> cuadrado_magico(n, vector<int>(n));
    set<int> valores_usados;
    k_esimo_cuadrado_magico(k, n, cuadrado_magico, 0, 0, valores_usados);
    return 0;
}

