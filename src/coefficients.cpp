#include "coefficients.h"

Coefficients::Coefficients(std::initializer_list<int> coefficients) : coefficients_(coefficients)
{}

[[nodiscard]] std::pair<int, int> Coefficients::getCoefficientsPair(int coefficientsPair) const
{
    switch(coefficientsPair)
    {
        case 0:
            return {coefficients_.at(0), coefficients_.at(1)};
        case 1:
            return {coefficients_.at(2), coefficients_.at(3)};
        case 2:
            return {coefficients_.at(4), coefficients_.at(5)};
        default:
            throw std::runtime_error("Wrong number of coefficients pair");
    }
}
