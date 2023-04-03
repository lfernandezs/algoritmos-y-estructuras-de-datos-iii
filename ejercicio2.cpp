#include <vector>
#include <math.h>

enum operacion { SUMA, MULTIPLICACION, POTENCIA, INDEFINIDO };
using namespace std;

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

            default:
                return -1;
                break;
        }
    }
    return resultado;
}

vector<operacion> operaciones_que_resuelven(int i, double w, int valores[]) {
    if ( i == 0) {
        if (valores[i] == w) return vector<operacion>(0);
        else return vector<operacion>(1, INDEFINIDO);
    }
    vector<operacion> suma = operaciones_que_resuelven(i - 1, w - valores[i], valores);
    suma.push_back(SUMA);

    if (resolver(suma, valores) == w) return suma;

    vector<operacion> multiplicacion = operaciones_que_resuelven(i - 1, w / valores[i], valores);
    multiplicacion.push_back(MULTIPLICACION);

    if (resolver(multiplicacion, valores) == w) return multiplicacion;

    vector<operacion> potencia = operaciones_que_resuelven(i - 1, pow(w, (double)(1 / (double)(valores[i]))), valores);
    potencia.push_back(POTENCIA);

    if (resolver(potencia, valores) == w) return potencia;

    return vector<operacion>(1, INDEFINIDO);

}

int main() {
    int V[5] = { 3, 1, 5, 2, 1 };
    vector<operacion> resultado = operaciones_que_resuelven(4, 400, V);
    return 0;
}