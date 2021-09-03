#include "random_number_generator.h"

#include <ctime>

std::default_random_engine RandomNumberGenerator::randomEngine_;

RandomNumberGenerator::RandomNumberGenerator(unsigned min, unsigned max)
{
    randomEngine_.seed(time(0));

    distribution_ = std::make_unique<std::uniform_int_distribution<unsigned> >(min, max);
}

unsigned RandomNumberGenerator::generateRandomNumber()
{
    return (*distribution_)(randomEngine_);
}
