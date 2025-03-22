#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>

using namespace std;

struct Arista { //descripcion de las aristas
    int nodo;
    int flujo;
    int cap;
};

int convertirTalle(string talle){ //funcion para convertir el talle a su pos en el vector
    if(talle=="XXL") return 1;
    if(talle=="XL") return 2;
    if(talle=="L") return 3;
    if(talle=="M") return 4;
    if(talle=="S") return 5;
    if (talle=="XS") return 6;
}

vector<vector<int>> hacerRedResidual(vector<list<Arista>>& red){ //hago la red residual para calcular camino de aumento
    vector<vector<int>> m(red.size(),vector<int> (red.size()));
    for (int i = 0; i < red.size(); i++) { //recorro aristas y hago la funcion de la teorica
        for (Arista e:red[i]) {
            if (e.flujo>0){
                m[e.nodo][i]=1;
            }
            if (e.flujo<e.cap){
                m[i][e.nodo]=1;
            }
        }
    }
    return m;
}

bool bfs(vector<vector<int>>& residual,vector<int>& camino){ //uso bfs para encontrar el camino de aumento
    vector<bool> visitados(residual.size());                //recorriendo la red residual y guardando el camino
    queue<int> cola;
    cola.push(0);
    visitados[0]=true;
    camino[0]=-1;

    while(!cola.empty()){
        int nodo = cola.front();
        cola.pop();
        for (int i = 0; i < residual.size(); i++) {
            if( !visitados[i] && residual[nodo][i] == 1){
                if (i == (residual.size()-1)){
                    camino[i]=nodo;
                    return true; //corto cuando encuentro el nodo T (sumidero)
                }
                cola.push(i);
                camino[i]=nodo;
                visitados[i]= true;
            }
        }
    }
    return false;
}


int fordFulkerson(vector<list<Arista>>& red){
    vector<vector<int>> residual=hacerRedResidual(red); //creo la red residual
    vector<int> camino(residual.size());
    int flujo=0;
    while(bfs(residual,camino)){ //cada iteracion: si hay camino hago FF con el camino de aumento
        int delta=INT_MAX;              // y modifico la red inicial
        int actual= residual.size()-1;
        while(camino[actual] != -1){    //recorro el camino y calculo el delta
            for (Arista e:red[camino[actual]]) {
                if(e.nodo == actual){
                    delta = min(delta,e.cap-e.flujo);
                }
            }
            for (Arista e:red[actual]) {
                if(e.nodo == camino[actual]){
                    delta = min(delta,e.flujo);
                }
            }
            actual=camino[actual];
        }
        actual = camino.size()-1;
        while(camino[actual] != -1){ //actualizo la red original, con la funcion de la teorica
            for (Arista& e:red[camino[actual]]) { //y el delta calculado
                if(e.nodo == actual){
                    e.flujo += delta;
                }
            }
            for (Arista& e:red[actual]) {
                if(e.nodo == camino[actual]){
                    e.flujo -= delta;
                }
            }
            actual=camino[actual];
        }
        flujo += delta; //voy sumando el flujo maximo
        residual=hacerRedResidual(red); //vuelvo a hacer la red residual con los valores actualizados
    }
    return flujo;
}

int main() {
    int casos;
    cin>>casos;
    int remeras;
    int personas;
    int c;
    string t1;
    int talle1;
    int size;
    int flujo;

    for (int i = 0; i < casos; i++) {
        cin>>remeras;
        cin>>personas;
        c=remeras/6; //calculo capacidad de las aristas a talles
        size=8 + personas;

        vector<list<Arista>> v(size);
        for (int j = 0; j < personas; j++) { //armo el grafo
            cin>>t1;
            talle1= convertirTalle(t1);
            v[talle1].emplace_back(Arista{j+7,0,1}); //pongo el primer talle
            cin>>t1;
            talle1= convertirTalle(t1);
            v[talle1].emplace_back(Arista{j+7,0,1}); //pongo el segundo talle
            v[j+7].emplace_back(Arista{size - 1,0,1});
        }
        for (int j = 1; j < 7 ; j++) {
            v[0].emplace_back(Arista{j,0,c});//conecto S con todos los talles
        }
        flujo = fordFulkerson(v);
        if (flujo == personas){ //si el flujo maximo es igual a las personas hay solucion
            cout<<"YES"<<endl;
        } else cout<<"NO"<<endl;
    }
    return 0;
}
