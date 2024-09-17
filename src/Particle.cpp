#include <utility>
#include <iostream>
#include <unordered_map>
#include "Particle.hpp"

Particle::Particle(vector<int> solution)
{
    this->solucao_atual = solution;
}

Velocity Particle::operator-(Particle &p1)
{
    Velocity v;

    unordered_map<int, int> positions(p1.solucao_atual.size());

    vector<int> caminho_aux = p1.solucao_atual;

    for(int i = 0; i < p1.solucao_atual.size(); i++){
        
        positions[this->solucao_atual[i]] = i;
    }
    
    for(int i = 0; i < p1.solucao_atual.size(); i++){
        int t = this->solucao_atual[i];

        while(t != caminho_aux[i]){
            int k = positions[caminho_aux[i]];
            v.value.push_back(pair(i, k));
            int temp = caminho_aux[i];
            caminho_aux[i] = caminho_aux[k];
            caminho_aux[k] = temp;

            if(i == 0)
                caminho_aux[caminho_aux.size() -1] = caminho_aux[0]; 
        }
    }

    return v;
}

void Particle::aplicar_velocidade(Velocity &v)
{
    int aux;
    for(int i = 0; i < v.value.size(); i++){
        
        aux = this->solucao_atual[v.value[i].first];
        this->solucao_atual[v.value[i].first] = this->solucao_atual[v.value[i].second];
        this->solucao_atual[v.value[i].second] = aux;
    }
}
