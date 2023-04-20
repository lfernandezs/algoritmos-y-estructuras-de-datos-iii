#include "polinomio_resto.h"

#define ll long long

/* ************************
 *  FUNCIONES AUXILIARES  *
 * ************************/

using namespace std;


ll mod(ll x, ll m) {
    return ((x % m) + m) % m;
}

ll mod_bin_exp(ll x, ll y, ll n) {
    if ( y == 0 ) return 1;
    ll result = mod( (ll)pow( mod_bin_exp( x, y / 2, n ), 2 ), n );
    return (mod( y, 2 ) == 0 ? result : mod( result * x, n ) );
}

ll mod_bin_mul(ll x, ll y, ll n) {
    return mod(mod(x, n) * mod(y, n), n);
}

// i: posición en el vector v
// k: resto actual
bool combinacion_con_resto(ll i, ll k, ll* v, ll** M, ll n, ll m, ll r) {
    if (i == n) return r == k;

    if (M[i][k] != -1) return (bool)M[i][k];

    M[i][k] = (ll)(
            combinacion_con_resto(i+1, mod(k+v[i], m), v, M, n, m, r) ||
            combinacion_con_resto(i+1, mod_bin_mul(k, v[i], m), v, M, n, m, r) ||
            combinacion_con_resto(i+1, mod_bin_exp(k, v[i], m), v, M, n, m, r) ||
            combinacion_con_resto(i+1, mod(k-v[i], m), v, M, n, m, r));

    return (bool)M[i][k];
}

//bool combinacion_con_resto_bottom_up(long long* v) {
//    bool *fila_anterior = new bool[m];
//    bool *fila_actual;
//    fila_anterior[r] = true;
//
//    for (long long i = n-1; i >= 0; i--) {
//        fila_actual = new bool[m];
//        for (long long j = 0; j < m; j++) {
//            fila_actual[j] = fila_anterior[mod(j + v[i], m)] ||
//                             fila_anterior[mod(j * v[i], m)] ||
//                             fila_anterior[mod_bin_exp(j, v[i], m)] ||
//                             fila_anterior[mod(j - v[i], m)];
//        }
//        fila_anterior = fila_actual;
//    }
//
//    return fila_actual[0];
//}

/* *********************
 *  FUNCION PRINCIPAL  *
 * *********************/

int main() {
    ll c, n, r, m;
    cin >> c;

    for (ll k = 0; k < c; k++) {
        cin >> n >> r >> m;
        ll v[n];
        bool resultado;

        // ESTRATEGIA TOP DOWN
        // Inicializo la matriz en <false, false>.
        ll **M;
        M = new ll *[n];
        for (ll i = 0; i < n; i++) {
            M[i] = new ll[m];
            for (ll j = 0; j < m; j++) {
                M[i][j] = -1;
            }
        }

        for (ll i = 0; i < n; i++) {
            cin >> v[i];
        }

        resultado = combinacion_con_resto(0, 0, v, M, n, m, r);
        cout << (resultado ? "Si" : "No") << endl;

        // ESTRATEGIA BOTTOM UP
//        resultado = combinacion_con_resto_bottom_up(v);
//        cout << "BOTTOM UP: " << (resultado ? "Si" : "No") << endl;
    }

    return 0;
}
