
#include <fstream>
#include <iostream>
#include <vector>
#include <iostream>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

int n,r,w,u,v;


struct Dsu {
    vector<int> parent, rank;

    Dsu(int size) {
        parent.resize(size);
        rank.resize(size);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int vertex) {
        if (parent[vertex] != vertex)
            parent[vertex] = find(parent[vertex]);
        return parent[vertex];
    }

    void Union(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);
        
        if(xRoot != yRoot){
            parent[yRoot] =xRoot;
        }
    }
};



double dist(tuple<int,int,int> a, tuple<int,int,int> b){
     int x = get<0>(a) - get<0>(b);
     int y = get<1>(a) - get<1>(b);
     
     double res = x*x + y*y;
     return sqrt(res);
}


vector<tuple<double,bool,int,int>> generar_aristas_pesadas(vector<tuple<int,int,int>>& nodos){
    vector<tuple<double,bool,int,int>> A;
    for(auto nodo : nodos){
        for(auto nodo2 : nodos){
            if(get<2>(nodo) > get<2>(nodo2)){continue;} // esta condicion es para no repetir aristas simetricas
            double distancia = dist(nodo,nodo2);
            bool utp = false;
            if(distancia == 0){continue;} // mismo nodo
            if(distancia <= r){
                utp = true;
            }
            A.push_back(make_tuple(distancia,utp,get<2>(nodo),get<2>(nodo2)));
        }
    }
    
    return A;
}




pair<double,double> costo(vector<tuple<double,bool,int,int>> A){


    // creo el DSU donde están  todas las cc's
    Dsu dsu(n);
    int componentes = n;
    double res_utp = 0;
    double res_f_o = 0;
    
    for( auto arista_pesada : A){
        if(dsu.find(get<2>(arista_pesada)) != dsu.find(get<3>(arista_pesada))){
            dsu.Union( get<2>(arista_pesada) ,get<3>(arista_pesada));
            if(get<1>(arista_pesada)){
                res_utp += get<0>(arista_pesada)*u;
            }else{
                res_f_o += get<0>(arista_pesada)*v;
            }
            
        componentes--;
        if( componentes == w ){break;}
            
        }
        

    }
    
    
    
    
    return make_pair(res_utp,res_f_o);

}
void expirmentacion(){
    ofstream archivo("resultados.csv");
    archivo << "n\ttiempo_prom\n";
    int n_max = 1000;
    vector<double> resultados(n_max);
    for(int i = 10; i < n_max; i +=10){
        vector<tuple<int,int,int>> nodos;
        int j = 0;
        while( j < i){
            int x = rand();
            int y = rand();
            nodos.push_back(make_tuple(x,y,j));
            j++;
        }
        n = i;
        r = rand() % 1000 + 1;
        w = rand() % n;
        v = rand() % 10 + 1;
        u = rand() % v + 1;
        double t0 = clock();
        vector<tuple<double,bool,int,int>> A = generar_aristas_pesadas(nodos);
        sort(A.begin(),A.end());
        pair<double,double> res = costo(A);

        double t1 = clock();
        double tiempo = (double(t1 - t0) / CLOCKS_PER_SEC);
        resultados[i] = tiempo;
        archivo << n << "\t" << resultados[i]  << endl;
    }
    archivo.close();
}


int main(){
    /*
    int c; cin >> c;
    int j = 1;
    while(c--){
        cin >> n; cin >> r;
        cin >> w; cin >> u; cin >> v;
        // x, y, id
        vector<tuple<int,int,int>> nodos;
        int i = 0;
        while( i < n){
            int x; cin >> x;
            int y; cin >> y;
            nodos.push_back(make_tuple(x,y,i));
            i++;
        }
        
        // Aristas con Peso y si son UTP y cordeenadas
        vector<tuple<double,bool,int,int>> A = generar_aristas_pesadas(nodos);
        // por ahi no usar sort
        sort(A.begin(),A.end());
        pair<double,double> res = costo(A);
        int caso = j;
        cout << "Caso #" << caso << ": " <<std::fixed << std::setprecision(3) << get<0>(res) << " " << get<1>(res) << 
        j++;
    }*/
    expirmentacion();

    return 0;
}

