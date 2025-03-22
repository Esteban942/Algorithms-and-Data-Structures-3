#include <iostream>
#include <vector>

using namespace std;

long long int compra_venta_vinos(vector<long long int> v){
    int i = 0;
    long long int res = 0;

    while( i < v.size() ){
        if (v[i] < 0){ //caso negativo
            for (int j = i + 1; j < v.size() ; j++) { //busco entre los vendedores y compradores
                if (v[j] > 0){  //como es caso negativo, busco uno positivo
                    v[i] += v[j];  //modifico el que estoy parado
                    if (v[i] > 0){  //si me pasé a positivo quiere decir que hubo exceso, devuelvo el resto a Vj
                        res += (v[j] - v[i]) * (j - i); //cuento unidad de trabajo
                        v[j]= v[i]; //Vj tiene vinos todavia
                        v[i]=0; //y pongo el Vi en 0
                        break;
                    } else if (v[i] < 0){ // si no llegué es que no alcanzó Vi queda con lo que tenia
                        res += v[j] * (j-i); //cuento unidad de trabajo
                        v[j]=0; //Vj se quedo sin vinos
                    } else { //si ambos numeros eran iguales pero opuestos
                        res += v[j] * (j-i); //cuento unidades de trabajo
                        v[j] = 0; // y ambos quedan en 0
                        break;
                    }
                }
            }
        }   else if (v[i] > 0){  //caso positivo
            for (int j = i + 1; j < v.size() ; j++) { //busco entre los vendedores y los compradores
                if (v[j] < 0){ //como es caso positivo, busco un negativo
                    v[i] += v[j]; //modifico el que estoy parado
                    if (v[i] > 0){ // si no me alcanzó
                        res += (-v[j]) * (j - i); //sumo unidades de trabajo
                        v[j]= 0; // Vj se quedo sin vinos
                    } else if (v[i] < 0){ //hubo exceso
                        res += ((-v[j]) + v[i]) * (j-i); //sumo unidades de trabajo
                        v[j]= v[i]; // pongo el exceso en Vj
                        v[i] =0; //pongo Vi en 0
                        break;
                    } else { //alcanzó justo
                        res += (-v[j]) * (j-i); //sumo unidades de trabajo
                        v[j] = 0; // pongo Vj 0 vinos
                        v[i] = 0;   // pongo Vi 0 vinos
                        break;
                    }
                }
            }
        }
        i++;
    }
    return res;
}

int main() {
    int casas;
    cin>>casas;
    long long int valor;
    vector<long long int> vinos(casas);

    for (int i=0;i < casas;i++){
        cin>>valor;
        vinos[i]=valor;
    }

    cout<<compra_venta_vinos(vinos);
    return 0;
}
