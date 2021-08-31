#include "random_number_generator.h"

#include <ctime>

std::default_random_engine RandomNumberGenerator::m_RandomEngine;

RandomNumberGenerator::RandomNumberGenerator(unsigned min, unsigned max)
{
    m_RandomEngine.seed(time(0));

    m_Distribution = std::make_unique<std::uniform_int_distribution<unsigned> >(min, max);
}

unsigned RandomNumberGenerator::GenerateRandomNumber()
{
    return (*m_Distribution)(m_RandomEngine);
}
