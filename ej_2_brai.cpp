#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <map>
#include <stack>
#include <utility>
#include <list>


using namespace std;

int n, m;
vector<vector<int>> D;
vector<vector<int>> D_T;
// nuevo digrafo D_2 con los CFC's colapsados en un solo nodo que representa cada uno.
vector<vector<int>> D_2;
stack<int> stackDeRecorrido;
set<int> cfc;

// dfs que crea un stack de recorrido y guarda el arbol dfs asociado al grafo.
void dfs_1(vector<vector<int>>& vecinos, int v,vector<bool> &visitado, vector<int>& previo){
    
    visitado[v] = true;
    for(int u: vecinos[v]){  
        if(!visitado[u]){
            previo[u] = v;
            dfs_1(vecinos,u,visitado,previo);
        }
    }

    stackDeRecorrido.push(v);
}

// dfs que guarda el recorrido en un conjunto que será una componente fuertemente conexa y guarda al representante del grupo.
void dfs_2(int v, vector<bool>& visitado, set<int>& cfc , int& min){
    visitado[v] = true;
    for(int u: D_T[v]){  // para cada u perteneciente al vecindario de salida de v
        if(!visitado[u]){
            dfs_2(u,visitado,cfc,min);
        }
    }
    cfc.insert(v);
    if(v < min){
        min = v;
    }
}


void kosaraju( list< pair<set<int>, int> >& componentes){
    
    
    // obtenemos el stack que va a definir el orden necesario de ejecuciones de BFS's, hacemos DFS sobre cualquier nodo
    
    vector<int> previo(n+1,-1);
    vector<bool> visitado(n,false);
    for(int i = 1 ; i <= n ; i++){
       dfs_1(D,i,visitado,previo);
    }
    
    //una vez obtenido el stack de recorrido hago dfs sobre cada nodo del stack, desde el tope hasta el final 
    //y guardo cada componente conexa. El dfs recorrerá D_T (digrafo invertido)
    
    // componentes será una lista donde cada elemento será una componente fuertemente conexa de D y su representante. (el mas chico)
    while( stackDeRecorrido.size() > 0) {
        int v = stackDeRecorrido.top();
        int min = v;
        set<int> cfc;
        dfs_2(v,visitado,cfc,min);
        componentes.push_back(make_pair(cfc,min));
        stackDeRecorrido.pop();
        }

}




void conjuntOptimo(){
    
    
    list< pair<set<int>, int>> componentes;
    
    // vamos a usar kosaraju para encontrar todas las componentes fuertemente conexas.
    kosaraju(componentes);
    
     // ahora hay que construir el nuevo digrafo D_2 pero en lugar de las cfcs en su lugar habrá un nodo que lo representa.
     
     vector<bool> nodosEliminados(n+1,false);
     
     for(auto cfc : componentes){
         int representante = cfc.second;
         for( int v : cfc.first ){  
             for( int u : D[v] ){  // para cada u en el vecindario de salida de v en D
                D_2[v].push_back(u);
             }
             if( v != representante ){
                nodosEliminados[v] = true;
             }
        }
     }
     
     
     // ahora D_2 es un digrafo sin circuitos, entonces solo resta hacer dfs sobre cada nodo y contar la cantidad de raices 
     // de todos los arboles dfs encontrados, es decir la cantidad de nodos que tienen padre -1 .
     
     
     vector<int> previo(n+1, -1);
     vector<bool> visitado(n+1,false);
     for(int i = 1; i <= n ; i++){
         if( !nodosEliminados[i] ){ // i no es un nodo eliminado
             dfs_1(D_2, i , visitado, previo);
         }
     }
     
     
     list<int> conjOptimo;
     
     for(int i = 1; i <= n ; i++){
         if(!nodosEliminados[i] &&  ( previo[i] == -1)  ){
             conjOptimo.push_back(i);
         }
     }
     
     cout << conjOptimo.size() << endl; 
     for(int i : conjOptimo){
         cout << i << "";  
     }
     
     return;
    
}





int main()
{
    
     cin >> n;
     cin >> m;

    D.assign(n+1, vector<int>(0));
    D_T.assign(n+1, vector<int>(0));
    D_2.assign(n+1, vector<int>(0));
    
    while(m--){
        int v; cin >> v;
        int w; cin >> w;
        D[v].push_back(w);
        D_T[w].push_back(v);
    }

    conjuntOptimo();
    return 0;
}
