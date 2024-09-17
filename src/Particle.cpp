#include <utility>
#include <iostream>
#include <unordered_map>
#include "Particle.hpp"

Velocity Particle::operator-(Particle &p1)
{
    Velocity v;

    unordered_map<int, int> positions(p1.solucao_atual.size());

    vector<int> caminho_aux = p1.solucao_atual;

    cout << "Posições:\n";
    for(int i = 0; i < p1.solucao_atual.size(); i++){
        
        positions[this->solucao_atual[i]] = i;
        cout << this->solucao_atual[i] << " : " << i<< endl;
    }
    for(int l = 0; l < p1.solucao_atual.size(); l++)
                cout << caminho_aux[l] << ", ";
    cout<< endl;
    for(int i = 0; i < p1.solucao_atual.size(); i++){
        int t = this->solucao_atual[i];

        while(t != caminho_aux[i]){
            int k = positions[caminho_aux[i]];

            v.value.push_back(pair(i, k));
            int temp = caminho_aux[i];
            caminho_aux[i] = caminho_aux[k];
            caminho_aux[k] = temp;
            
            for(int l = 0; l < p1.solucao_atual.size(); l++)
                cout << caminho_aux[l] << ", ";
            cout<< endl;
        }
    }

    
    return v;
}