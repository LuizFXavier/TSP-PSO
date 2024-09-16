#pragma once
#include <vector>
#include "Cidade.hpp"
class PSO
{
private:
    double calcula_caminho(std::vector<int> caminho);
    double calcula_distancia(Cidade &a, Cidade &b);

    int nCidades;

    std::vector<std::vector<double>> distancias;

public:
    PSO(int n, std::vector<Cidade> &cidades);
    
};