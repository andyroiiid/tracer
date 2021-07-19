//
// Created by andyroiiid on 7/16/2021.
//

#include "random.h"

#include <random>

double randomDouble() {
    // use fixed seed for deterministic result
    static std::mt19937 engine(0); // NOLINT(cert-msc51-cpp)
    static std::uniform_real_distribution<double> distribution;
    return distribution(engine);
}
