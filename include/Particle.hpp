#pragma once
#include <vector>
#include <utility>
#include <unordered_map>
#include "Velocity.hpp"
#define INFINITO 0xfffffff

using namespace std;
class Particle
{
public:
    std::vector<int> p_best;
    double best_dist = INFINITO;
    std::vector<int> solucao_atual;
    Velocity velocity;

    Particle(vector<int> solution);
    Velocity operator-(Particle &p1);
    void aplicar_velocidade(Velocity &v);

};