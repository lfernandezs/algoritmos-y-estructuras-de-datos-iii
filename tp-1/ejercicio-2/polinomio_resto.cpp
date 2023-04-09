#include "polinomio_resto.h"

/* ************************
 *  FUNCIONES AUXILIARES  *
 * ************************/

size_t n, r, m;

int mod(int x, int m) {
    return ((x % m) + m) % m;
}

bool combinacion_con_resto(int i, int k, int* v, tuple<bool, bool>** M) {
    if (i == n) return r == k;

    if (get<0>(M[i][k])) return get<1>(M[i][k]);

    M[i][k] = make_tuple(true,
                         combinacion_con_resto(i+1, mod(k+v[i], m), v, M) ||
                         combinacion_con_resto(i+1, mod(k*v[i], m), v, M) ||
                         combinacion_con_resto(i+1, mod(pow(k, v[i]), m), v, M) ||
                         combinacion_con_resto(i+1, mod(k-v[i], m), v, M)
    );

    return get<1>(M[i][k]);
}

bool combinacion_con_resto_bottom_up(int* v) {
    bool *fila_anterior = new bool[m];
    bool *fila_actual;
    fila_anterior[r] = true;

    for (int i = n-1; i >= 0; i--) {
        fila_actual = new bool[m];
        for (int j = 0; j < m; j++) {
            fila_actual[j] = fila_anterior[mod(j + v[i], m)] ||
                             fila_anterior[mod(j * v[i], m)] ||
                             fila_anterior[mod(pow(j, v[i]), m)] ||
                             fila_anterior[mod(j - v[i], m)];
        }
        fila_anterior = fila_actual;
    }

    return fila_actual[0];
}

/* *********************
 *  FUNCION PRINCIPAL  *
 * *********************/

int main() {
    int c;
    cin >> c;

    for (int k = 0; k < c; k++) {
        cin >> n >> r >> m;
        int v[n];
        bool resultado;

        // ESTRATEGIA TOP DOWN
        // Inicializo la matriz en <false, false>.
        tuple<bool, bool> **M = new tuple<bool, bool>*[n];
        for (int i = 0; i < n; i++) {
            M[i] = new tuple<bool, bool>[m];
            for (int j = 0; j < m; j++) {
                M[i][j] = make_tuple(false, false);
            }
        }

        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }

        resultado = combinacion_con_resto(0, 0, v, M);
        cout << "TOP DOWN: " << (resultado ? "Si" : "No") << endl;

        // ESTRATEGIA BOTTOM UP
        resultado = combinacion_con_resto_bottom_up(v);
        cout << "BOTTOM UP: " << (resultado ? "Si" : "No") << endl;
    }

    return 0;
}
