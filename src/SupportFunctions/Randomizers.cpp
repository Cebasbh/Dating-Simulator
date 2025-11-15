#include "Randomizers.h"

float NumberRandomizer(bool flag, float RI, float RS){
    std::random_device rd; //Cosas de semillas
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribucion(RI, RS); //Crea la distribución uniforme
    //Switch entre distribución Discreta o Continua
    float randomizer = 0.f;
    if (flag == true){
        randomizer = distribucion(gen); 
    }
    else{
        randomizer = std::round(distribucion(gen));
    }
    return randomizer;
}

std::vector<float> FractionRandomizer(int count){
    std::vector<float> fractions;
    float sum = 0;
    for (int i = 0; i < count; i++) {
        float val = NumberRandomizer(true, 0.01, 1);
        fractions.push_back(val);
        sum = sum + val;
    }
    for (int i = 0; i < count; i++) {
        fractions[i] = fractions[i] / sum;
    }
    return fractions;
}