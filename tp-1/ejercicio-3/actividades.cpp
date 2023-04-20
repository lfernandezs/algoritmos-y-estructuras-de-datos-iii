        #include <iostream>
        #include <stdio.h>
        #include <vector>
        #include <tuple>
        #include <iostream>
        #include <fstream>

        using namespace std;
         
        int actividades_maximales(ifstream &input)
        {
            int n, s, t;
            vector<tuple<int, int, int> > S;
         
            input >> n;
            int maximo = -1, minimo = 2*n;
            vector<vector<tuple<int, int, int>>> orden((2*n)+1);
            for(int i = 0; i < n; i++)
            {
                input >> s >> t;
                orden[t].push_back({i+1, s, t});
            }
            
            for(int i = 1; i <= 2*n; i++)
            {
                if(orden[i].size() > 0)
                {
                    if(S.size() == 0)
                    {
                        S.push_back(orden[i][0]);
                    }
                    else
                    {
                        int minimo = (2*n)+1, minPos = -1;
                        for(int j = 0; j < orden[i].size(); j++)
                        {
                            if(get<1>(orden[i][j]) >= get<2>(S[S.size() - 1]))
                            {
                                minimo = get<1>(orden[i][j]);
                                minPos = j;
                            }
                        }
                        if(minPos != -1) S.push_back(orden[i][minPos]);
                    }
                }
            }
            
            // cout << S.size() << endl;
            // for(auto i : S) cout << get<0>(i) << " ";
            // cout << "\n";
            
            return 0;
        }  
