//
// Created by kiryuhin_ve on 18.07.2023.
//

#include "getRandomNumber.h"

unsigned int getRandomNumber(unsigned int max){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist{0, max}; // distribution that maps to the ints 1..100
    return dist(rng);      // make a generator
}