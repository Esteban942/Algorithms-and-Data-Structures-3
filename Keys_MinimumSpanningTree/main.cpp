#include <iostream>
#include <vector>
#include <cmath>
#include <climits>


using namespace std;

int calculoDistancia(string s1,string s2){ //funcion para calcular la distancia entre combinaciones

    int res=0;
    int d1;
    int d2;

    for (int i = 0; i < 4; ++i) {
        d1= s1[i] - '0';
        d2= s2[i] - '0';
        res += min(abs(d1-d2),10-abs(d1-d2)); //distancia entre vuelta por izquierda o derecha
    }

    return res;
}

void hacerGrafo(vector<string>& v,vector<vector<int>>& m){ //hago el grafo uniendo todas las aristas con todas
    for (int i = 0; i < m.size(); i++){                     //con su correspondiente distancia entre ellas
        for (int j = 0; j < v.size(); j++) {
            m[i][j] = calculoDistancia(v[i],v[j]);
        }
    }
}

int caso0000(vector<string>& v){
    int res = calculoDistancia(v[0],"0000");
    for (int i = 1; i < v.size(); i++){
        res = min(res, calculoDistancia(v[i],"0000"));
    }
    return res;
}

int primBarato(vector<vector<int>>& m){ //algoritmo de prim visto en teorica y practica
    int res=0;
    vector<bool> visitados(m.size());
    vector<int> k(m.size());
    for (int i = 0; i < visitados.size(); i++) {
        k[i]=INT_MAX;
        visitados[i]=false;
    }
    k[0]=0;
    for (int i = 0; i < m.size(); i++) {
        int min = INT_MAX;
        int v;
        for (int j = 0; j < visitados.size(); j++) {
            if (!(visitados[j]) && k[j] < min){ //me fijo si no esta visitado y si es menor a lo que habia
                min = k[j]; //actualizo el min
                v = j; //agarro el indice
            }
        }
        visitados[v]=true;
        res += k[v]; //sumo el costo ya que es el minimo
        for (int j = 0; j < m.size(); j++) {
            if(!(visitados[j]) && m[v][j] < k[j]){
                k[j]=m[v][j];
            }
        }
    }
    return res;
}

int combinacionesMin(vector<string>& v){
    vector<vector<int>> m(v.size(),vector<int>(v.size()));
    int res;
    hacerGrafo(v,m); //primero armo el grafo,uniendo las combinaciones entre si
    res = caso0000(v); //calculo el caso del 0000(no incluido en el grafo)
    res += primBarato(m); //corro prim para el AGM
    return res;
}

int main() {
    int casos;
    cin>>casos;
    int n;
    string valor;
    int res;

    for(int i=0; i<casos;i++){
        cin>>n;
        vector<string> v(n);
        for (int j=0; j < n; j++){
            cin>>valor;
            v[j] = valor;
        }
        res = combinacionesMin(v);
        cout<<res<<endl;
    }

    return 0;
}
