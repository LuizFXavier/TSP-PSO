#include <iostream>
#include "Velocity.hpp"
#include "Particle.hpp"
using namespace std;

int main(){
    
    Particle p1, p2;

    p1.solucao_atual = {0,2,1,3};
    p2.solucao_atual = {2,1,3,0};

    Velocity v = p1 - p2;
    for(int i = 0; i < v.value.size(); i++){
        cout << v.value[i].first << ", "<< v.value[i].second << endl;
    }
    return EXIT_SUCCESS;
}