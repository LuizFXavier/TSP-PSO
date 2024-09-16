#include "Velocity.hpp"

Velocity::Velocity()
{
    this->value = {};
}

Velocity Velocity::operator+(Velocity v)
{
    Velocity v_temp;
    v_temp.value = this->value;

    for (int i = 0; i < v.value.size(); i++)
        v_temp.value.push_back(v.value[i]);

    return v_temp;
}

Velocity Velocity::operator+(std::vector<std::pair<int, int>> values)
{
    Velocity v_temp;
    v_temp.value = this->value;

    for (int i = 0; i < values.size(); i++)
        v_temp.value.push_back(values[i]);

    return v_temp;
}

Velocity Velocity::operator*(double c)
{
    Velocity v;

    if(c == 0){
        return v;
    }

    int t = c;
    double k = c - t;

    for(int i = 0; i < t; i++){
        v = v + this->value;
    }

    Velocity v_temp;

    for(int i = 0; i < k * this->value.size(); i++){
        v_temp.value.push_back(this->value[i]);
    }

    v = v + v_temp;
    
    return v;
}