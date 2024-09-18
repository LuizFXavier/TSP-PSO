#include <fstream>
#include <cmath>
#include <iostream>
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

Particle PSO::get_best()
{
    return *g_best;
}

void PSO::main_loop()
{   
    double f_value; //Resultado da função fitness

    for(int i = 0; i < nRep; i++){
        cout << "Rep " << i <<": \n";
        this->best_dist = INFINITO;
        int t = 0;
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
            

            cout<<"Particula "<< t << ":\natual: ";
            for(int i = 0; i <= nCidades; i++)
                cout<< p.solucao_atual[i] << " ";
            
            cout<< ", " <<f_value <<"\np_best: ";
            for(int i = 0; i <= nCidades; i++)
                cout<< p.p_best[i] << " ";
            cout<< ", " << p.best_dist << endl;
            t++;
        }
        cout<<"G_best: ";
        for(int i = 0; i < g_best->solucao_atual.size(); i++)
            cout<<g_best->solucao_atual[i] << " ";
        cout<<", " << g_best->best_dist << endl << endl;
        t = 0;
        for(Particle& p: particulas){
            cout<<"Particula "<< t << ":\n";
            Particle p_best(p.p_best);
            cout << "\nAntes de calcular a velocidade\n";
            
            Velocity pb = (p_best - p);
            cout << "pb = ";
            for(int w = 0; w < pb.value.size(); w++)
                cout << "(" << pb.value[w].first << ", " << pb.value[w].second << ") ";

            Velocity gb = (*g_best - p);
            cout << "\ngb = ";
            for(int w = 0; w < gb.value.size(); w++)
                cout << "(" << gb.value[w].first << ", " << gb.value[w].second << ") ";
            
            Velocity v = (p_best - p) * 0.5 + (*g_best - p) * 0.5;
            cout << "\nv = ";
            for(int w = 0; w < v.value.size(); w++)
                cout << "(" << v.value[w].first << ", " << v.value[w].second << ") ";
            
            cout << "\nAntes de aplicar a velocidade\n";
            p.aplicar_velocidade(v);
            t++;
        }
        cout<<"\n---------------------------------\n";
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