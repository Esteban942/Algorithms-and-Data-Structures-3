#include <iostream>

#include<vector>

using namespace std;

int edificiosMurciaCreciente(vector<int> altura,vector<int> ancho){
    vector<int> memoria(altura.size()+1);
    bool encontre;
    memoria[0]= ancho[0];
    memoria[altura.size()] = memoria[0];
    int i = 1;
    while (i < altura.size()){
        for (int j = i; j > 0; j--) {
            if (altura[i] > altura[j]){
                memoria[i] = ancho[i] + memoria[j];
                memoria[altura.size()] = max(memoria[i],memoria[altura.size()]);
                encontre = true;
                break;
            }
            encontre = false;
        }
        if (!encontre) {
            memoria[i] = ancho[i];
            memoria[altura.size()] = max(memoria[i],memoria[altura.size()]);
            encontre=false;
        }
        i++;
    }
    return memoria[altura.size()];
}

int edificiosMurciaDecreciente(vector<int> altura,vector<int> ancho){
    vector<int> memoria(altura.size()+1);
    bool encontre;
    memoria[0]= ancho[0];
    memoria[altura.size()] = memoria[0];
    int i = 1;
    while (i < altura.size()){
        for (int j = i; j > 0; j--) {
            if (altura[i] < altura[j]){
                memoria[i] = ancho[i] + memoria[j];
                memoria[altura.size()] = max(memoria[i],memoria[altura.size()]);
                encontre = true;
                break;
            }
            encontre = false;
        }
        if (!encontre) {
            memoria[i] = ancho[i];
            memoria[altura.size()] = max(memoria[i],memoria[altura.size()]);
            encontre=false;
        }
        i++;
    }
    return memoria[altura.size()];
}

int main(){
    int casos;
    int edificios;
    int valor;
    cin>>casos;
    for(int i = 1; i <= casos; i++){
        cin>>edificios;

        vector<int> altura (edificios);
        vector<int> ancho (edificios);

        for (int j = 0; j < edificios; j++){
            cin>> valor;
            altura[j]=valor;
        }
        for (int k = 0; k < edificios; k++){
            cin>>valor;
            ancho[k]=valor;
        }

        int c = edificiosMurciaCreciente(altura,ancho);
        int d = edificiosMurciaDecreciente(altura,ancho);
        if (c >= d){
            cout<<"Case "<<i<<"."<<"Increasing ("<<c<<")"<<"."<<"Decreasing ("<<d<<")"<<"."<<endl;
        } else {
            cout<<"Case "<<i<<"."<<"Decreasing ("<<d<<")"<<"."<<"Increasing ("<<c<<")"<<"."<<endl;
        }
    }
    return 0;
};