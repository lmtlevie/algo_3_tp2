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

// dfs que crea un stack de recorrido
void dfs_1(int v,vector<bool> &visitado,int n,int p){
    
    visitado[v] = true;
    for(int u: D[v]){  // para cada u perteneciente al vecindario de salida de v
        if(!visitado[u]){
            dfs_1(u,visitado,n,v);
        }
    }

    stackDeRecorrido.push(v);
}

// dfs que guarda el recorrido en un conjunto que será una componente fuertemente conexa y guarda al representante del grupo.
void dfs_2(int v, vector<bool>& visitado, set<int>& cfc , int& min){
    visitado[v] = true;
    for(int u: D_T[v]){  // para cada u perteneciente al vecindario de salida de v
        if(!visitado[u]){
            //previo[u] = v;
            dfs_2(u,visitado,cfc);
        }
    }
    cfc.insert(v);
    if(v < min){
        min = v;
    }
}

// vamos a usar kosaraju para encontrar todas las componentes fuertemente conexas.
void kosaraju(vector<bool>& visitado, vector<int>& previo){
    
    
    // obtenemos el stack que va a definir el orden necesario de ejecuciones de BFS's, hacemos DFS sobre cualquier nodo
    
   // dfs_1(1,visitado,n,-1, previo);
    
    //una vez obtenido el stack de recorrido hago dfs sobre cada nodo del stack, desde el tope hasta el final 
    //y guardo cada componente conexa. El dfs recorrerá D_T (digrafo invertido)
    
    // componentes será una lista donde cada elemento será una componente fuertemente conexa de D y su representante. (el mas chico)
    list< pair<set<int>, int>> componentes = {};
    while( stackDeRecorrido.size() > 0) {
        int v = stackDeRecorrido.top();
        int min = v;
        set<int> cfc;
        dfs_2(v,visitado,cfc,min);
        componentes.insert(make_pair(cfc,min));
        stackDeRecorrido.pop();
        }

}

// ahora hay que construir el nuevo digrafo D_2 pero en lugar de las cfcs en su lugar habrá un nodo que lo representa.


// continuará...







int main()
{
    


    while (true) {
        cin >> n >> m;
        if (n + m == 0) break;

        map<string,int> name_to_index;
        
        string line; getline(cin, line);
        for (int i=0; i<n; i++) {
            getline(cin, line); name_to_index[line] = i;
            
        }
        
        D.assign(n, vector<int>(0)); D_T.assign(n, vector<int>(0));

        for (int j=0; j<m; j++) {
            string from, to;
            getline(cin, from);
            getline(cin, to);
            D[name_to_index[from]].push_back(name_to_index[to]);
            D_T[name_to_index[to]].push_back(name_to_index[from]);
        }

        // Completar
    }

    return 0;
}