#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
using namespace std;

//https://cp-algorithms.com/graph/bridge-searching.html
// el codigo esta mal, la idea esta cerca, con varios casos de test en papel prece funcionar
// usar array globales


void dfs(int v,vector<set<int>> &vecinos,vector<bool> &visitado,int n,int &aristas_en_ciclo,int p,set<pair<int,int>> &back_edges,vector<int> &previo){
    
    visitado[v] = true;
    for(int u: vecinos[v]){
        if(!visitado[u]){
            previo[u] = v;
            //cout << "previo: " << u << "-" << v << endl;
            dfs(u,vecinos,visitado,n,aristas_en_ciclo,v,back_edges,previo);
        }else if(u != p){
            //if (previo[u] == -1) {previo[u]=v;}
            back_edges.insert(make_pair(u,v));
        }
    }

}



double probabilidad_de_perder(vector<set<int>> &vecinos,int n){
    
    vector<bool> visitados(n+1,false);
    int aristas_en_ciclo = 0; // cuento las aristas que pertenecen a un ciclo talque aunque el adversario que juega perfecto las elimine sea jugada ganadora
    
    set<pair<int,int>> back_edges;
    vector<int> previo(n+1,-1);
    for(int i=1;i <= n;i++){
        if(!visitados[i]){
          //  cout << "Componente Conexa" << endl;
            

            dfs(i,vecinos,visitados,n,aristas_en_ciclo,-1,back_edges,previo);

                }
            }
            
            vector<vector<bool>> aristas_procesadas;
            aristas_procesadas.assign(n+1, vector<bool>(n+1,false));
            for(auto x: back_edges){
                if( !(aristas_procesadas[x.first][x.second] ||  aristas_procesadas[x.second][x.first]) ) {
                  aristas_procesadas[x.first][x.second] = true;
                  aristas_procesadas[x.second][x.first] = true;
                  aristas_en_ciclo++;
                }
                
                
                //cout << x.first << "-" << x.second << endl;
                int u = x.first;
                int v = x.second;

                while(v != u){
                    if( previo[v]==-1 || aristas_procesadas[v][previo[v]] || aristas_procesadas[previo[v]][v] ) break;
                    //cout << v << endl;
                    aristas_en_ciclo++;
                    aristas_procesadas[v][previo[v]] = true;
                    aristas_procesadas[previo[v]][v] = true;
                    v = previo[v];
        }
    }

    long long formas_de_jugar = (n * (n-1))/2;

    double res = 1 - ( (double)aristas_en_ciclo / (double)formas_de_jugar);
    return res;
}


int main(){

    int n; cin >> n;
    int m; cin >> m;
    // uso lista de adyacencia
    vector<set<int>> vecinos(n+1);

    while(m--){
        int v; cin >> v;
        int w; cin >> w;
        vecinos[v].insert(w);
        vecinos[w].insert(v);
    }

    double res = probabilidad_de_perder(vecinos,n);
    cout << fixed << setprecision(5) << res << endl;

    return 0;

}




