#pragma once
#include <vector>
#include <utility>
class Velocity
{
private:
public:
    std::vector<std::pair<int, int>> value;
    Velocity();
    Velocity operator+(Velocity v);
    Velocity operator+(std::vector<std::pair<int, int>> values);
    Velocity operator*(double c);
};