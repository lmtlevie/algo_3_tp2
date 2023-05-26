#include <iostream>


vector<pair<double,bool,int,int>> generar_aristas_pesadas(vector<tuple<,int,int,int>> nodos){
    vector<pair<double,bool,int,int>> A;
    for(tuple<int,int,int> nodo:nodos){
        for(tuple<int,int,int> nodo2:nodos){
            double distancia = dist(nodo,nodo2);
            bool utp = false;
            if(distancia == 0){continue;} // mismo nodo
            if(distancia >= r){
                utp = true;
            }
            A.push_back(make_tuple(distancia,utp,get<2>(nodo),get<2>(nodo2)));
        }
    }
}

pair<double,double> costo(vector<pair<double,bool,int,int>> A){
    double res_utp = 0;
    double res_f_o = 0;
    for(auto arista_pesada: A){
        if(conjunto.find(get<2>(arista_pesada)) != conjunto.find(get<3>(arista_pesada))){
            conjunto.union(get<2>(arista_pesada),get<2>(arista_pesada));
            if(get<1>(arista_pesada)){
                res_utp += get<0>(arista_pesada);
            }else{
                res_f_o += get<0>(arista_pesada);
            }
        }
    }
    return make_pair(res_utp,res_f_o);

}



int main(){
 
    int c; cin >> c;
    while(c--){
        int n; cin >> n;
        int r; cin >> r;
        int w; cin >> w;
        int u; cin >> u;
        int v; cin >> v;
        // x, y, id
        vector<tuple<int,int,int>> nodos;
        int i = 0;
        while(n--){
            int x; cin >> x;
            int y; cin >> y;
            nodos.push_back(make_pair(x,y,i));
            i++;
        }
        
        // Aristas con Peso y si son UTP y cordeenadas
        vector<tuple<double,bool,int,int>> A = generar_aristas_pesadas(nodos);
        // por ahi no usar sort
        sort(A.begin(),A.end());
        pair<double,double> res = costos(plano_pabellon,A);
        cout << "Caso #" << c << ": " << get<0>(res) << " " << get<1>(res) << endl;
    }

    return 0;
}
