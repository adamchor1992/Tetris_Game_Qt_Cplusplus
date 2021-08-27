#pragma once

#include <random>
#include <memory>

class RandomNumberGenerator
{
public:
    RandomNumberGenerator(unsigned min, unsigned max);
    unsigned GenerateRandomNumber();

private:
    static std::default_random_engine m_RandomEngine;
    std::unique_ptr<std::uniform_int_distribution<unsigned>> m_Distribution;
};
