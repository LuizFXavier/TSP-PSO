#include "PSO.hpp"

PSO::PSO(int n, std::vector<Cidade> &cidades)
{
    this->distancias.resize(n);
    
    for (int i = 0; i < this->nCidades; i++){

        std::vector <double> c;
        c.resize(nCidades);
        for (int j = 0; j < this->nCidades; j++){
            if (j > i)
                c[j] = calcula_distancia(cidades[i], cidades[j]);
            else if (j < i)
                c[j] = this->distancias[j][i];
            else
                c[j] = 0;
            
        }
        this->distancias.push_back(c);
    }
}

double PSO::calcula_caminho(std::vector<int> caminho)
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