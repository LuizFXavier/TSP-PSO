#include <fstream>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <random>
#include "Cidade.hpp"
#include "PSO.hpp"

PSO::PSO(string cities_file)
{
    srand(time(0)); //Seed para geração de números aleatórios posteriormente.
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

        vector <double> c(nCidades);
        
        for (int j = 0; j < nCidades; j++){

            if (j > i)
                c[j] = calcula_distancia(cidades[i], cidades[j]);
            else if (j < i)
                c[j] = distancias[j][i];
            else
                c[j] = 0;
            
        }
        distancias[i] = c;
    }
    this->best_particle.best_dist = INFINITO;
}

void PSO::executar(string routes_file)
{
    ifstream r_file(routes_file);
    r_file >> nParticulas;
    
    for(int i = 0; i < nParticulas; i++){
        vector<int> rota(nCidades +1);
        
        for(int j = 0; j <= nCidades; j++){
            r_file >> rota[j];
        }
        
        this->particulas.push_back(Particle(rota));

    }
    for(int i = 0; i < nParticulas; i++){
        for(int j = 0; j <= nCidades; j++){
            
            cout << particulas[i].solucao_atual[j] << " ";
        }
        cout << endl << endl;
    }

    main_loop();

}


void PSO::executar()
{
    gerar_particulas();
    main_loop();
}
int random_number (int i) { return rand()%i;}

void PSO::gerar_particulas()
{
    vector<int> rota(nCidades + 1);
    for(int i = 1; i <= nCidades; i++){
        rota[i-1] = i;
    }
    rota[nCidades] = rota[0];
    
    
    for(int i = 0; i < nParticulas; i++){
        random_shuffle(rota.begin(), rota.end() - 1, random_number);
        
        rota[nCidades] = rota[0];
        
        this->particulas.push_back(Particle(rota));
        shift_rota(this->particulas[i]);
    }
}

void PSO::shift_rota(Particle &p)
{
    while (p.solucao_atual[0] != 1)
    {
        for(int i = 0; i < nCidades; i++){
            p.solucao_atual[i] = p.solucao_atual[i+1];
        }
        p.solucao_atual[nCidades] = p.solucao_atual[0];
    }
    
}

Particle PSO::get_best()
{
    return this->best_particle;
}

void PSO::main_loop()
{   
    double f_value; //Resultado da função fitness
    double g_best_value; // Melhor resultado fitness da iteração
    Particle *g_best; // Melhor partícula da iteração

    for(int i = 0; i < nRep; i++){
        g_best_value = INFINITO;
        int t = 0;
        for(Particle& p: particulas){
            
            f_value = calcula_caminho(p.solucao_atual);
            
            // Atualiza o p_best da partícula i
            if(f_value < p.best_dist){
                p.best_dist = f_value;    
                p.p_best = p.solucao_atual;
            }
            // Atualiza o novo possível melhor global
            if(f_value < g_best_value){
                g_best_value = f_value;
                g_best = &p;
            }
        }
        // Atualiza o melhor resultado de todas as iterações
        if(g_best_value < this->best_particle.best_dist){
            this->best_particle = *g_best;
        }
        
        for(Particle& p: particulas){
            
            Particle p_best(p.p_best);
            
            double r1 = static_cast<double>(rand()) / RAND_MAX;
            double r2 = static_cast<double>(rand()) / RAND_MAX;
            
            double w = w_max - (w_max - w_min)/nRep * i;

            Velocity v = p.velocity * w + (p_best - p) * c1 * r1  + (*g_best - p) * c2 * r2;
            p.velocity = v;
            
            p.aplicar_velocidade(v);
            shift_rota(p);
        }
        
    }


}

double PSO::calcula_caminho(std::vector<int> caminho) //Fitness function
{
    double distancia = 0;
    
    for(int i = 0; i < nCidades; i++){
        distancia += distancias[caminho[i] -1][caminho[i+1] -1];
    }
    return distancia;
}

double PSO::calcula_distancia(Cidade &a, Cidade &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}