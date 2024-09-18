#pragma once
#include <vector>
#include <string>
#include "Cidade.hpp"
#include "Particle.hpp"
#define INFINITO 0xfffffff

using namespace std;
class PSO
{
private:
    double calcula_caminho(vector<int> caminho); //Fitness function
    double calcula_distancia(Cidade &a, Cidade &b);
    void main_loop();
    vector<Cidade> cidades;

    int c1 = 1;
    int c2 = 1;
    int nRep = 10;

    Particle* g_best;
    double best_dist = INFINITO;

    vector<std::vector<double>> distancias;

public:
    int nCidades;
    int nParticulas;
    vector<Particle> particulas;
    PSO(string cities_file);
    void executar(string routes_file);

    Particle get_best();
};