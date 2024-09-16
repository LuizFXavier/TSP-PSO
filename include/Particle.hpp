#pragma once
#include <vector>
#include <utility>
#include <unordered_map>
#include "Velocity.hpp"

using namespace std;
class Particle
{
private:
    std::vector<int> p_best;
    
    double best_dist;
public:
    std::vector<int> solucao_atual;
    Velocity velocity;

    Velocity operator-(Particle &p1);
    
};