#include <iostream>
#include <vector>
#include <climits>

using namespace std;

long long dantzigBarato(vector<vector<int>>& m){ //algoritmo sacado del cormen y teorica
    long long res=0;
    for (int k = 0; k < m.size() - 1 ; k++) {   //recorro la matriz y voy calculando el camino minimo
        for (int i = 0; i <= k; i++) {      //y luego voy agregando mas torres (invariante de Dantzig)
            int l1=INT_MAX;
            int l2=INT_MAX;
            for (int j = 0; j <= k; j++) {  //funcion vista en teorica de Dantzig
                l1=min(m[i][j] + m[j][k+1],l1);
                l2= min(m[k+1][j] + m[j][i],l2);
            }
            m[i][k+1]=l1;
            m[k+1][i]=l2;
            res+= l1+l2; //actualizo res con los valores calculados con k nodos
        }
        for (int i = 0; i <= k; i++) {//funcion vista en teorica para los caminos minimos
            for (int j = 0; j <= k; j++) {
                m[i][j]= min(m[i][j],m[i][k+1] + m[k+1][j]);
                res += m[i][j]; //actualizo res con los resultados finales
            }
        }
    }
    return res;
}

void cambiarGrafo(vector<vector<int>>& m,vector<int>& v){
    vector<vector<int>> copia(m.size(),vector<int>(m.size()));
    int v1;
    int v2;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size(); j++) {
            v1=v[i];
            v2=v[j];
            copia[i][j]=m[v1][v2];
        }
    }
    m=copia;
}

long long energiaNecesaria(vector<vector<int>>& m,vector<int>& v){
    long long res;
    cambiarGrafo(m,v); //cambio el grafo para usar el nuevo orden y calcular usando el invariante de dantzig
    res = dantzigBarato(m);
    return res;
}

int main() {
    int casos;
    int torres;
    cin>>casos;
    int valor;
    int pos;
    long long res;

    for (int i = 0; i < casos; i++){
        cin>>torres;
        vector<vector<int>> m(torres,vector<int>(torres));
        vector<int> orden(torres);
        for (int j = 0; j < torres; j++) {  //armo el grafo
            for (int k = 0; k < torres; k++) {
                cin>>valor;
                m[j][k]=valor;
            }
        }
        for (int j = torres - 1; j >= 0; j--) { //pongo las posiciones para cumplir el invariante de
            cin>>pos;                            //dantzig y no cambiarlo despues
            orden[j]=pos;
        }
        res = energiaNecesaria(m,orden);
        cout<<res<<endl;
    }

    
    return 0;
}
