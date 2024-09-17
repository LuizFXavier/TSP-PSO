#include <fstream>
#include <cmath>
#include "Cidade.hpp"
#include "PSO.hpp"

PSO::PSO(string cities_file)
{
    ifstream c_file(cities_file);

    c_file >> nCidades;

    { //Leitura das cidades
        double x, y;
        for(int i = 0; i < nCidades; i++){
            c_file >> x;
            c_file >> y;

            this->cidades.push_back(Cidade(x,y));
        }
    }

    distancias.resize(nCidades);
    
    for (int i = 0; i < nCidades; i++){ //Cálculo das distâncias entre as cidades

        vector <double> c;
        c.resize(nCidades);
        for (int j = 0; j < nCidades; j++){
            if (j > i)
                c[j] = calcula_distancia(cidades[i], cidades[j]);
            else if (j < i)
                c[j] = distancias[j][i];
            else
                c[j] = 0;
            
        }
        distancias.push_back(c);
    }

}

void PSO::executar(string routes_file)
{
    ifstream r_file(routes_file);
    r_file >> nParticulas;

    for(int i = 0; i < nParticulas; i++){
        vector<int> rota(nCidades +1);
        int c;
        for(int j = 0; j <= nCidades; j++){
            r_file >> rota[j];
        }
        this->particulas.push_back(Particle(rota));
    }

    first_iter();

}

void PSO::first_iter()
{
    
    for(Particle& p : particulas){
        p.best_dist = calcula_caminho(p.solucao_atual);

        if(p.best_dist < this->best_dist)
            this->best_dist = p.best_dist;
    }
    
}

void PSO::main_loop()
{   
    double f_value; //Resultado da função fitness

    for(int i = 1; i < nRep; i++){
        best_dist = INFINITO;

        for(Particle& p: particulas){
            f_value = calcula_caminho(p.solucao_atual);
            
            if(f_value < p.best_dist){
                p.best_dist = f_value;    
                p.p_best = p.solucao_atual;
            }
            if(f_value < best_dist){
                best_dist = f_value;
                g_best = &p;
            }

        }
        for(Particle& p: particulas){
            
            Particle p_best(p.p_best);
            
            Velocity v = (p_best - p) * c1 + (*g_best - p) * c2;

            p.aplicar_velocidade(v);
        }
    }


}

double PSO::calcula_caminho(std::vector<int> caminho) //Fitness function
{
    double distancia = 0;
    
    for(int i = 0; i < caminho.size() - 1; i++){
        distancia += distancias[caminho[i]][caminho[i+1]];
    }

    return distancia;
}

double PSO::calcula_distancia(Cidade &a, Cidade &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}