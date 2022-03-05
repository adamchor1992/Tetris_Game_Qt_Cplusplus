#include "random_number_generator.h"

#include <ctime>

RandomNumberGenerator::RandomNumberGenerator(unsigned min, unsigned max)
{
    randomEngine_.seed(time(nullptr));

    distribution_ = std::make_unique<std::uniform_int_distribution<unsigned> >(min, max);
}

unsigned int RandomNumberGenerator::generateRandomNumber()
{
    return (*distribution_)(randomEngine_);
}
