cmake_minimum_required(VERSION 3.22)

project(tsp_pso)
add_subdirectory(matplotplusplus)

add_executable(tsp_pso
    src/Particle.cpp
    src/Velocity.cpp
    src/Cidade.cpp
    src/PSO.cpp
    src/Grafico.cpp
    src/main.cpp
)
target_link_libraries(tsp_pso PUBLIC matplot)
target_include_directories(tsp_pso PRIVATE include)