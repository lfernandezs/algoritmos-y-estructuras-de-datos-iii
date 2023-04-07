#include <vector>
#include <math.h>
#include <iostream>

enum operacion { SUMA, MULTIPLICACION, POTENCIA, RESTA };
using namespace std;

int mod(int x, int m) {
    return ((x % m) + m) % m;
}

int resto = 10;
int v[4] = {7, 10, 10, 50};
int n = 4, m = 100, r = 10;

int M[3][100][4];

bool combinacion_con_resto(int resto_acumulado, int i, operacion op) {
    if (i == n) return resto_acumulado == resto;

    if (M[i][resto_acumulado][op] != -1) {
        return (bool)M[i][resto_acumulado][op];
    }

    switch (op) {
        case SUMA:
            M[i][resto_acumulado][op] = (int)(combinacion_con_resto(mod(resto_acumulado + v[i], m), i+1, SUMA) ||
                    combinacion_con_resto(mod(resto_acumulado + v[i], m), i+1, RESTA) ||
                    combinacion_con_resto(mod(resto_acumulado + v[i], m), i+1, MULTIPLICACION) ||
                    combinacion_con_resto(mod(resto_acumulado + v[i], m), i+1, POTENCIA));

        case RESTA:
            M[i][resto_acumulado][op] = (int)(combinacion_con_resto(mod(resto_acumulado - v[i], m), i+1, SUMA) ||
                   combinacion_con_resto(mod(resto_acumulado - v[i], m), i+1, RESTA) ||
                   combinacion_con_resto(mod(resto_acumulado - v[i], m), i+1, MULTIPLICACION) ||
                   combinacion_con_resto(mod(resto_acumulado - v[i], m), i+1, POTENCIA));

        case MULTIPLICACION:
            M[i][resto_acumulado][op] = (int)(combinacion_con_resto(mod(resto_acumulado * v[i], m), i+1, SUMA) ||
                   combinacion_con_resto(mod(resto_acumulado * v[i], m), i+1, RESTA) ||
                   combinacion_con_resto(mod(resto_acumulado * v[i], m), i+1, MULTIPLICACION) ||
                   combinacion_con_resto(mod(resto_acumulado * v[i], m), i+1, POTENCIA));

        case POTENCIA:
            M[i][resto_acumulado][op] = (int)(combinacion_con_resto(mod(pow(resto_acumulado, v[i]), m), i+1, SUMA) ||
                   combinacion_con_resto(mod(pow(resto_acumulado, v[i]), m), i+1, RESTA) ||
                   combinacion_con_resto(mod(pow(resto_acumulado, v[i]), m), i+1, MULTIPLICACION) ||
                   combinacion_con_resto(mod(pow(resto_acumulado, v[i]), m), i+1, POTENCIA));
    }

    return M[i][resto_acumulado][op];
}

int main() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for ( int k = 0; k < 4; k++) {
                M[i][j][k] = -1;
            }
        }
    }
    bool resultado = combinacion_con_resto(mod(v[0], m), 1, SUMA) ||
            combinacion_con_resto(mod(v[0], m), 1, RESTA) ||
            combinacion_con_resto(mod(v[0], m), 1, MULTIPLICACION) ||
            combinacion_con_resto(mod(v[0], m), 1, POTENCIA);
    cout << resultado << endl;
    return 0;
}