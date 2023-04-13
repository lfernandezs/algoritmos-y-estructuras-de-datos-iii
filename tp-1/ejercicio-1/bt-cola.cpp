#include <iostream>
#include <vector>
#include <math.h>
#include <set>
#include <queue>

using namespace std;

int r = 0, numero_magico;

void imprimir_matriz(vector<vector<int>> &matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

bool es_cuadrado_magico(vector<vector<int>> &matriz, vector<vector<int>> &sumasFilas, vector<vector<int>> &sumasColumnas, int n) {
    bool filas = true, columnas = true;
    vector<int> suma_diagonales(2);

    for(int i = 0; i < n; i++)
    {
        if(sumasFilas[i][n] != numero_magico) filas = false; 
        if(sumasColumnas[n][i] != numero_magico) columnas = false;
        suma_diagonales[0] += matriz[i][i];
        suma_diagonales[1] += matriz[i][n-1-i];
    }
    return filas
           && columnas
           && (suma_diagonales[0] == numero_magico)
           && (suma_diagonales[1] == numero_magico);
}

bool suma_se_pasa(int n, vector<vector<int>> &sumasFilas, vector<vector<int>> &sumasColumnas, int i, int j) {
    return sumasFilas[i][j+1] > numero_magico || sumasColumnas[i+1][j] > numero_magico;
}

// TODO: ver el nombre.
bool suma_no_alcanza(int n, vector<vector<int>> &sumasFilas, vector<vector<int>> &sumasColumnas, int i, int j) {
    if (i == n-1) return sumasColumnas[i+1][j] < numero_magico;
    if (j == n-1) return sumasFilas[i][j+1] < numero_magico;
    return false;
}

/* *********************
 *  FUNCION PRINCIPAL  *
 * *********************/

void k_esimo_cuadrado_magico(int k, int n, vector<vector<int>> &solucion_parcial, int i, int j, vector<vector<int>> &sumasFilas, vector<vector<int>> &sumasColumnas, queue<int> &cola) {
    if(r == k)
        return;
    if (i == n) {
        if (es_cuadrado_magico(solucion_parcial, sumasFilas, sumasColumnas, n)) {
            r++;
            if (r == k) imprimir_matriz(solucion_parcial, n);
        }
        return;
    }
    int cont = cola.size();
    while(cont--)
    {
        int v = cola.front();
        cola.pop();
        solucion_parcial[i][j] = v;
        sumasFilas[i][j+1] = sumasFilas[i][j] + v;
        sumasColumnas[i+1][j] = sumasColumnas[i][j] + v;
        if ( !suma_se_pasa(n, sumasFilas, sumasColumnas, i, j) && !suma_no_alcanza(n, sumasFilas, sumasColumnas, i, j) ) { // O(1)
//          set<int> valores_usados_copy(valores_usados); // O(n*n)
//          valores_usados_copy.insert(v); // O(log(n*n))
            //valores_usados.insert(v); // O(log(n*n))
            k_esimo_cuadrado_magico(k, n, solucion_parcial, i + (int) (j + 1 == n), (j + 1) % n, sumasFilas, sumasColumnas, cola);
            //valores_usados.erase(v); // O(log(n*n))
            if (r == k) return;
        }
        cola.push(v);

    }
    
    /*
    VERSION TARDIA CON SET
    // TODO: Hay alguna forma más eficiente de guardar los valores que no fueron usados?
    for (int v = 1; v <= n*n; v++) {
        if (!valores_usados.count(v)) { // O(log(n*n))
            solucion_parcial[i][j] = v;
            sumasFilas[i][j+1] = sumasFilas[i][j] + v;
            sumasColumnas[i+1][j] = sumasColumnas[i][j] + v;
            if ( !suma_se_pasa(n, sumasFilas, sumasColumnas, i, j) && !suma_no_alcanza(n, sumasFilas, sumasColumnas, i, j) ) { // O(1)
//                set<int> valores_usados_copy(valores_usados); // O(n*n)
//                valores_usados_copy.insert(v); // O(log(n*n))
                valores_usados.insert(v); // O(log(n*n))
                k_esimo_cuadrado_magico(k, n, solucion_parcial, i + (int) (j + 1 == n), (j + 1) % n, valores_usados, sumasFilas, sumasColumnas);
                valores_usados.erase(v); // O(log(n*n))
                if (r == k) return;
            }
        }
    }
*/
    if (i == 0 && j == 0 && r < k) cout << -1 << endl;
}

int main() {
    int n, k;
    cin >> n >> k;
    numero_magico = ((int)pow(n, 3) + n) / 2;
    vector<vector<int>> cuadrado_magico(n, vector<int>(n));
    vector<vector<int>> sumasFilas (n, vector<int>(n+1, 0));
    vector<vector<int>> sumasColumnas (n+1, vector<int>(n, 0));
    //set<int> valores_usados;
    queue<int>cola;
    for(int i = 1; i <=n*n; i++)
        cola.push(i);
    k_esimo_cuadrado_magico(k, n, cuadrado_magico, 0, 0, sumasFilas, sumasColumnas, cola);
    return 0;
}
