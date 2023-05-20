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
            cout << "previo: " << u << "-" << v << endl;
            dfs(u,vecinos,visitado,n,aristas_en_ciclo,v,back_edges,previo);
        }else if(u != p){
            if (previo[u] == -1) {previo[u]=v;}
            back_edges.insert(make_pair(max(v,u),min(v,u)));
        }
    }

}



double probabilidad_de_perder(vector<set<int>> &vecinos,int n){
    
    vector<bool> visitados(n+1,false);
    int aristas_en_ciclo = 0; // cuento las aristas que pertenecen a un ciclo talque aunque el adversario que juega perfecto las elimine sea jugada ganadora
    
    for(int i=1;i <= n;i++){
        if(!visitados[i]){
            cout << "Componente Conexa" << endl;
            
            set<pair<int,int>> back_edges;
            vector<int> previo(n+1,-1);
            
            dfs(i,vecinos,visitados,n,aristas_en_ciclo,-1,back_edges,previo);
            
            for(auto x: back_edges){
                aristas_en_ciclo++;
                cout << x.first << "-" << x.second << endl;
                int v = previo[x.first];
                while(v != x.first){
                    cout << v << endl;
                    aristas_en_ciclo++;
                    v = previo[v];
                }
            }
        }
    }

    int formas_de_jugar = (n * (n-1))/2;

    double res = 1 - ((double)aristas_en_ciclo / (double)formas_de_jugar);
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

