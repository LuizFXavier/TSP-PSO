#include <iostream>
#include "PSO.hpp"
using namespace std;

int main(int argc, char * argv[]){

    if(argc < 1){
        return EXIT_FAILURE;
    }
    
    PSO pso(argv[1]);

    pso.executar();
    for(int i = 0; i < pso.nParticulas; i++){
        for(int j = 0; j <= pso.nCidades; j++){
            cout << pso.particulas[i].solucao_atual[j] <<" ";
        }
        cout << ": " << pso.calcula_caminho(pso.particulas[i].solucao_atual) << "\n";
    }
    cout<<"\n-------------------------------------\n";
    for(int i = 0; i <= pso.nCidades; i++)
        cout << pso.get_best().solucao_atual[i]<< " ";
    
    cout << endl;
    cout << pso.get_best().best_dist;
    cout << endl;

    return EXIT_SUCCESS;
}