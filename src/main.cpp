#include <iostream>
#include "PSO.hpp"
#include "Grafico.hpp"
#include "Particle.hpp"
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
    
    Particle best = pso.get_best();
    cout<<"\n-------------------------------------\n";
    for(int i = 0; i <= pso.nCidades; i++)
        cout << best.solucao_atual[i]<< " ";
    
    cout << endl;
    cout << best.best_dist;
    cout << endl;

    Grafico::apresentar(pso.cidades, best);

    return EXIT_SUCCESS;
}