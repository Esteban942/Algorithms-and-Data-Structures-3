#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;


int swap_letters(string s, string t,list<pair<int,int>>& p){
    int a = 0;
    int b = 0;
    for(int i = 0; i< s.size(); i++){ //me fijo que haya la misma cantidad de a y b para ambos strings
        if (s[i] == 'a'){
            a++;
        } else b++;
        if (t[i] == 'a'){
            a++;
        } else b++;
    }

    if (a % 2 != 0 && b % 2 != 0) return -1; //si no ya devuelvo

    //si sigue aca es porque se puede resolver

    int i = 0;
    char swap;
    int res=0;
    bool no_encontre = false; //flag por si no encuentra el mismo patron para swap y hay que swapear en el que estan
    int cant_pares = 0;

    while (i < s.size()){
        if (s[i] != t[i]){
            for (int j=i + 1; j< s.size() ; j++){
                if (s[j] != t[j] && s[i] != t[j]){ //busco el mismo patron para swapear
                    swap = t[j];
                    t[j] = s[i];
                    s[i] = swap;
                    res++;
                    p.push_back({i+1,j+1}); //agrego a la lista el par
                    cant_pares ++;
                    no_encontre= false;
                    break;
                }
                no_encontre=true;
            }
            if (no_encontre) { //si no encontre el mismo patron, swapeo en el lugar y busco este nuevo patron
                swap = t[i];
                t[i] = s[i];
                s[i] = swap;
                p.push_back({i+1,i+1}); //agrego a la lista el par
                cant_pares ++;
                res++;
                for (int j = i + 1; j < s.size(); j++) { //idem que arriba
                    if (s[j] != t[j] && s[i] != t[j]) {
                        swap = t[j];
                        t[j] = s[i];
                        s[i] = swap;
                        res++;
                        p.push_back({i+1,j+1}); //agrego a la lista el par
                        cant_pares ++;
                        break;
                    }
                }
            }
        }
        i++;
        no_encontre=false;
    }
    return res;
}

int main() {

    string s;
    string t;
    int tam;

    cin>> tam;
    cin>> s;
    cin>> t;

    list<pair<int,int>> pares_imprimir;

    int res = swap_letters(s,t,pares_imprimir);

    cout<<res<<endl;

    for (auto& p : pares_imprimir) {
        cout<<p.first<<" "<< p.second<<endl;
    }

    return 0;
}
