        #include <vector>
        #include <iostream>
        #include <tuple>
        #include <string>
         
        #define ll long long
        using namespace std;
         
        /* ************************
         *  FUNCIONES AUXILIARES  *
         * ************************/
         
        ll n, r, m;
         
        ll mod(ll x, ll m) {
            return ((x % m) + m) % m;
        }
        
        ll mod_bin_exp(ll base, ll exp, ll m) {
             if(!exp)
                return 1;
         
            ll pot = mod_bin_exp(base, (exp / 2), m);
         
            if(!(exp % 2))
                return ((pot * pot) % m);
         
            return ((((pot * pot) % m) * base) % m);
        }
        
        bool combinacion_con_resto(ll i, ll k, ll* v, vector<vector<int> > &dp) {
            if (i == n) return r == k;
         
            if (dp[i][k] != -1) return (bool) dp[i][k];
         
            dp[i][k] = (int) (
                                combinacion_con_resto(i+1, mod(k+v[i], m), v, dp) ||
                                combinacion_con_resto(i+1, mod(k*v[i], m), v, dp) ||
                                combinacion_con_resto(i+1, mod_bin_exp(k, v[i], m), v, dp) ||
                                combinacion_con_resto(i+1, mod(k-v[i], m), v, dp)
                            );
         
            return (bool) dp[i][k];
        }
        
        /* *********************
         *  FUNCION PRINCIPAL  *
         * *********************/
         
        int main() {
            vector<string>respuestas;
            ll c;
            cin >> c;
         
            for (ll k = 0; k < c; k++) {
                cin >> n >> r >> m;
                vector<vector<int> > dp(n, vector<int> (m, -1));
                ll v[n];
                bool resultado;
                for (ll i = 0; i < n; i++) {
                    cin >> v[i];
                }
                resultado = combinacion_con_resto(1, v[0], v, dp);
                if(resultado)
                    respuestas.push_back("Si");
                else respuestas.push_back("No");
            }
            for(auto j:respuestas)
                cout << j << endl;
         
            return 0;
        }  
