#include "cuadrado_magico.h"

int k_esimo_cuadrado_magico(int k, int n, vector<vector<int>> &solucion_parcial, int i, int j, set<int> valores_usados) {
    if (i == n) {
        if (es_cuadrado_magico(solucion_parcial, n)) {
            imprimir_matriz(solucion_parcial, n);
            cout << endl;
        }
        return 0;
    }

    // TODO: Hay alguna forma más eficiente de guardar los valores que no fueron usados?
    for (int v = 1; v <= n*n; v++) {
        if (!valores_usados.count(v)) {
            solucion_parcial[i][j] = v;
            if ( !suma_se_pasa(n, solucion_parcial, i, j) && !suma_no_alcanza(n, solucion_parcial, i, j) ) {
                set<int> valores_usados_copy(valores_usados);
                valores_usados_copy.insert(v);
                k_esimo_cuadrado_magico(k, n, solucion_parcial, i + (int) (j + 1 == n), (j + 1) % n,valores_usados_copy);
            }
        }
    }

    return 0;
}

int main() {
    int k = 0, n = 4;
    // cin >> k >> n;
    vector<vector<int>> cuadrado_magico(n, vector<int>(n));
    set<int> valores_usados;
    k_esimo_cuadrado_magico(k, n, cuadrado_magico, 0, 0, valores_usados);
    return 0;
}