#include <iostream>

#include<vector>

using namespace std;

int locosPorLasNueces (vector<vector<int>> b, vector<vector<int>> m, int c){
    int altura = b.size();
    int arboles = b[0].size();

    for (int i = 0; i < arboles; i++) {        //pongo en la altura mas alta cuantas nueces hay en cada arbol
            m[altura-1][i] = b[altura-1][i];
            m[altura - 1][arboles] = max(m[altura - 1][arboles],m[altura-1][i]);
    }
    
    int i = altura - 2;
    while (i > -1){       //recorro por alturas (bajando de los arboles)
        for (int j = 0; j < arboles; j++ ) { //me muevo en los arboles
            if (i + c > altura - 1){    //pregunto si jj pudo haber venido por un salto
                m[i][j] = m[i + 1][j] + b[i][j];  // si no vino de un salto, vino del mismo arbol
                m[i][arboles] = max(m[i][arboles],m[i][j]); //guardo el maximo de los arboles en esta altura
            } else {
                m[i][j] = max(m[i + 1][j] + b[i][j], b[i][j] + m[i + c][arboles]); //pido el maximo de haber saltado o de haber venido del mismo arbol
                m[i][arboles] = max(m[i][arboles],m[i][j]); //idem de antes
            }
        }
        i--;
    }

   return m[0][arboles];
}

int main() {

    int arboles;
    int altura;
    int caida;
    int casos;
    int cantNueces;
    int lugar;

    cin>>casos;
    for(int i = 1; i <= casos; i++){
        cin>>arboles;
        cin>>altura;
        cin>>caida;

        vector<vector<int>> bosque (altura,vector<int> (arboles));
        vector<vector<int>> memoria (altura,vector<int> (arboles + 1)); //memoria para guardar los maximos acumulados
        for (int j = 0; j < arboles; j++){
            cin>>cantNueces;
            for (int k = 0; k < cantNueces; k++){
                cin>>lugar;
                bosque[lugar-1][j] += 1;
            }
        }

        int res;
        res=locosPorLasNueces(bosque,memoria,caida);
        cout<<res<<endl;

    }

    return 0;
}
