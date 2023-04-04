#include "cuadrado_magico.h"

// TODO: Se puede tener una variable global? Se puede hacer algo parecido pero usando
//  un parámetro?
int r = 0;

int k_esimo_cuadrado_magico(int k, int n, vector<vector<int>> &solucion_parcial, int i, int j, set<int> valores_usados) {
    if (i == n) {
        if (es_cuadrado_magico(solucion_parcial, n)) {
            r++;
            if (r == k) imprimir_matriz(solucion_parcial, n);
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
                if (r == k) return 0;
            }
        }
    }

    if (i == 0 && j == 0 && r < k) cout << -1 ;
}

int main() {
    int k, n;
    cin >> k >> n;
    vector<vector<int>> cuadrado_magico(n, vector<int>(n));
    set<int> valores_usados;
    k_esimo_cuadrado_magico(k, n, cuadrado_magico, 0, 0, valores_usados);
    return 0;
}