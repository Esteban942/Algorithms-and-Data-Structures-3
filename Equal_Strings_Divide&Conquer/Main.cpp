#include <iostream>

using namespace std;

bool sonEquivalente (string a, string b) {
    if (a == b) return true; //comparo string si son iguales devuelvo true
    if (a.length() % 2 != 0){  //si llegue al final de las divisiones o es impar y no dio true, retorno false
        return false;
    }
    return (sonEquivalente(a.substr(0,a.length()/2),b.substr(b.length()/2,b.length())) &&
             sonEquivalente(a.substr(a.length()/2,a.length()),b.substr(0,b.length()/2))) ||
            (sonEquivalente(a.substr(0,a.length()/2),b.substr(0,b.length()/2)) &&
            sonEquivalente(a.substr(a.length()/2,a.length()),b.substr(b.length()/2,b.length())));
} //divido el problema en subproblemas dividiendo los strings y comparando

int main() {
    string a;
    string b;

    cin>>a;
    cin>>b;

    bool res = sonEquivalente(a,b);

    if(res){
        cout<<"YES";
    } else cout<<"NO";

    return 0;
};