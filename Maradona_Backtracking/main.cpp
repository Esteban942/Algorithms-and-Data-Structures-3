#include <iostream>

#include <vector>

using namespace std;

struct jugador{         //represento al jugador como un struct
    string nombre;
    int ataque;
    int defensa;
};

int ataqueMax;
int defensaMax;
vector<vector<jugador>> equipo_final (2, vector<jugador>(5));
vector<jugador> convocados(10);

bool prioridad_alfabeto(vector<vector<jugador>> equipo){   //determina que equipo tiene prioridad por alfabeto
    for (int i = 0; i < 5 ; i++){
            if (equipo_final[0][i].nombre < equipo[0][i].nombre){
                return true;
            }
    }
    return false;
}


void equipo_Maradona(vector<vector<jugador>> &equipo, int n, vector<int> &jugadores_disponibles, int ataque_equipo, int defensa_equipo) {

    if (n > 1 && n < 6){   //poda alfabetica para los atacantes
        if (equipo[0][n-2].nombre > equipo[0][n-1].nombre){
            return;
        }
    }

    if (n > 6){            //poda alfabetica para los defensores
        if (equipo[1][n-7].nombre > equipo[1][n - 6].nombre){
            return;
        }
    }

    if (n == 10) { //caso base determino si este equipo es mejor que el que tenia guardado
        if (ataqueMax < ataque_equipo) {    //determino quien tiene mas ataque
            ataqueMax = ataque_equipo;
            defensaMax = defensa_equipo;
            equipo_final = equipo;
            return;
        } else if (ataqueMax == ataque_equipo) {  //si el ataque es igual determino por otras cosas
            if (defensaMax < defensa_equipo) {      //me fijo la defensa de los equipos
                defensaMax = defensa_equipo;
                equipo_final = equipo;
                return;
            } else if (defensaMax == defensa_equipo){
                if (!prioridad_alfabeto(equipo)) {
                    equipo_final = equipo;
                    return;
                } else return;
            } else {
                return;
            }
        } else {
            return;
        }
    }

    for (int k = 0; k < 10; k++) {  //itero los convocados para saber quien entra en el equipo
        if (jugadores_disponibles[k] == 0) { //jugadores disponibles es para saber quienes ya estan en el equipo y quien no
            if (n < 5){             //armando atacantes
                equipo[0][n] = convocados[k]; //pongo el jugador en el equipo
                jugadores_disponibles[k] = 1; //marco que no esta disponible
                ataque_equipo += convocados[k].ataque; //sumo el ataque del jugador al equipo
                equipo_Maradona(equipo,n + 1, jugadores_disponibles, ataque_equipo, defensa_equipo); //recursion
                jugadores_disponibles[k] = 0; //el jugador esta disponible
                ataque_equipo -= convocados[k].ataque; //como lo saque del equipo saco su ataque
            } else {                //armando defensores idem anterior de los atacantes
                equipo[1][n - 5] = convocados[k];
                jugadores_disponibles[k] = 1;
                defensa_equipo += convocados[k].defensa;
                equipo_Maradona(equipo,n + 1, jugadores_disponibles, ataque_equipo, defensa_equipo);
                jugadores_disponibles[k] = 0;
                defensa_equipo -= convocados[k].defensa;
            }
        }
    }
}

int main() {
    int casos;
    cin>> casos;
    int n;
    vector<vector<jugador>> equipo (2, vector<jugador>(5));
    vector<int> jugadores_disponibles(10);
    int ataque_equipo;
    int defensa_equipo;

    for(int i = 1; i <= casos ;i++){
        for(int j = 0; j < 10 ;j++){
            cin>> convocados[j].nombre;
            cin>> convocados[j].ataque;
            cin>> convocados[j].defensa;
        }
        ataqueMax = 0;
        defensaMax = 0;
        ataque_equipo = 0;
        defensa_equipo = 0;
        n=0;

        equipo_Maradona(equipo,n,jugadores_disponibles,ataque_equipo,defensa_equipo);

        cout<< "Case " << i << ":" << endl;

        //atacantes
        cout<<"("<<equipo_final[0][0].nombre<<", ";
        cout<<equipo_final[0][1].nombre<<", ";
        cout<<equipo_final[0][2].nombre<<", ";
        cout<<equipo_final[0][3].nombre<<", ";
        cout<<equipo_final[0][4].nombre<<")"<<endl;

        //defensores
        cout<<"("<<equipo_final[1][0].nombre<<", ";
        cout<<equipo_final[1][1].nombre<<", ";
        cout<<equipo_final[1][2].nombre<<", ";
        cout<<equipo_final[1][3].nombre<<", ";
        cout<<equipo_final[1][4].nombre<<")"<<endl;
    }

    return 0;
}