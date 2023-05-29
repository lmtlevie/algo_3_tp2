#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

//https://cp-algorithms.com/graph/bridge-searching.html
// usar array globales


void dfs(int v,vector<set<int>> &vecinos,vector<bool> &visitado,int n,int &aristas_en_ciclo,int p,vector<pair<int,int>> &back_edges,vector<int> &previo){
    
    visitado[v] = true;
    for(int u: vecinos[v]){
        if(!visitado[u]){
            previo[u] = v;
            dfs(u,vecinos,visitado,n,aristas_en_ciclo,v,back_edges,previo);
        }else if(u != p){
            back_edges.push_back(make_pair(u,v));
        }
    }

}


void dfs_2(vector<set<int>>& vecinos, vector<bool>& visitados, int v, int& cant){
    if( visitados[v]) return;
    cant++;
    visitados[v] = true;
    for(int u : vecinos[v]){
        dfs_2(vecinos,visitados,u,cant);
    }
}

void dfsBridges(int u, int parent, vector<bool>& visited, vector<int>& disc, vector<int>& low, const vector<set<int>>& graph, set<pair<int, int>>& bridges) {
    static int time = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;

    for (int v : graph[u]) {
        if (!visited[v]) {
            dfsBridges(v, u, visited, disc, low, graph, bridges);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u])
                bridges.insert({u, v});
        }
        else if (v != parent)
            low[u] = min(low[u], disc[v]);
    }
}

set<pair<int, int>> findBridges(const vector<set<int>>& graph) {
    int V = graph.size();
    vector<bool> visited(V, false);
    vector<int> disc(V, 0);
    vector<int> low(V, 0);
    set<pair<int, int>> bridges;

    for (int u = 0; u < V; ++u) {
        if (!visited[u])
            dfsBridges(u, -1, visited, disc, low, graph, bridges);
    }

    return bridges;
}





double probabilidad_de_perder(vector<set<int>> &vecinos_original, int n){
    
    
    vector<set<int>> vecinos(n+1);
    set<pair<int,int>> bridges = findBridges(vecinos_original);

    //quito puentes de grafo :
    for(int i = 1; i <= n; i++ ){
       for( auto u : vecinos_original[i]){
           if( !( bridges.count(make_pair(i,u)) || bridges.count(make_pair(u,i)) )){
               vecinos[i].insert(u);
               vecinos[u].insert(i);
           }
       }
    }
    
     // ahora vecinos es una version sin aristas puentes del grafo original. solo queda contar nodos por c.c
     double probabilidad_de_ganar = 0.0;
    vector<bool> visitados(n+1,false);
     long long formas_de_jugar = (n * (n-1))/2;          
    for(int v = 1; v <= n ; v++){
        int cant = 0;
        dfs_2(vecinos,visitados,v,cant);
        
        if(cant == 0) continue;
        probabilidad_de_ganar += ( ((double)cant*( (double) cant-1) ) / 2 ) / (double) formas_de_jugar;
        
        
    }


    double res = 1 - probabilidad_de_ganar;
  
    return res;

}


int main(){

    int n; cin >> n;
    int m; cin >> m;
    // uso lista de adyacencia
    vector<set<int>> vecinos_original(n+1);


    while(m--){
        int v; cin >> v;
        int w; cin >> w;
        vecinos_original[v].insert(w);
        vecinos_original[w].insert(v);
    }

    double res = probabilidad_de_perder(vecinos_original,n);
    cout << fixed << setprecision(5) << res << endl;

    return 0;

}















