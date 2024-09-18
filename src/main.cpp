#include <iostream>
#include "PSO.hpp"
using namespace std;

int main(int argc, char * argv[]){

    if(argc < 2){
        return EXIT_FAILURE;
    }
    
    PSO pso(argv[1]);

    pso.executar(argv[2]);

    for(int i = 0; i <= pso.nCidades; i++)
        cout << pso.get_best().solucao_atual[i] << " ";
    cout << endl;
    cout << pso.get_best().best_dist;
    cout << endl;

    return EXIT_SUCCESS;
}