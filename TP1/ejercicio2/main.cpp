#include <vector>
#include <math.h>

enum operacion { SUMA, MULTIPLICACION, POTENCIA, RESTA, INDEFINIDO };
using namespace std;

int mod(int x, int m) {
    return ((x % m) + m) % m;
}

int resolver(vector<operacion> operaciones, int valores[]) {
    int resultado = valores[0];
    for (int i = 0; i < operaciones.size(); i++) {
        switch(operaciones[i]) {
            case SUMA:
                resultado += valores[i+1];
                break;

            case MULTIPLICACION:
                resultado *= valores[i+1];
                break;

            case POTENCIA:
                resultado = pow(resultado, valores[i+1]);
                break;

            case RESTA:
                resultado -= valores[i+1];
                break;

            default:
                return -1;
                break;
        }
    }
    return resultado;
}

vector<operacion> operaciones_que_resuelven(int i, int r, int m, int valores[]) {
    if ( i == 0 ) {
        if (mod(valores[i], m) == r) return vector<operacion>(0);
        else return vector<operacion>(1, INDEFINIDO);
    }
    vector<operacion> suma = operaciones_que_resuelven(i - 1, mod((r - valores[i]), m), m, valores);
    suma.push_back(SUMA);

    if (mod(resolver(suma, valores), m) == r) return suma;

    vector<operacion> multiplicacion = operaciones_que_resuelven(i - 1, mod((r / valores[i]), m), m, valores);
    multiplicacion.push_back(MULTIPLICACION);

    if (mod(resolver(multiplicacion, valores), m) == r) return multiplicacion;

    // TODO: ver si la conversión de pow a int está bien
    // TODO: ver si la operación de raíz no es muy costosa.
    vector<operacion> potencia = operaciones_que_resuelven(i - 1, mod((int)pow(r, (double)(1 / (double)(valores[i]))), m), m, valores);
    potencia.push_back(POTENCIA);

    if (mod(resolver(potencia, valores), m) == r) return potencia;

    vector<operacion> resta = operaciones_que_resuelven(i - 1, mod(r + valores[i], m), m, valores);
    resta.push_back(RESTA);

    if (mod(resolver(resta, valores), m) == r) return resta;

    return vector<operacion>(1, INDEFINIDO);

}

int main() {
    int V[3] = { 1, 1, 1 };
    int n = 2, m = 100000, r = 10;
    vector<operacion> resultado = operaciones_que_resuelven(n, r, m, V);
    return 0;
}