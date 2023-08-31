#include "rotation_coefficients.h"
#include <stdexcept>

RotationCoefficientsContainer::RotationCoefficientsContainer(const std::initializer_list<std::pair<int, int>>& rotationCoefficients)
{
    for(const auto& elem : rotationCoefficients)
    {
        rotationCoefficients_.push_back(elem);
    }
}

std::pair<int, int> RotationCoefficientsContainer::getRotationCoefficientsPair(size_t rotationCoefficientsPairIndex) const
{
    switch(rotationCoefficientsPairIndex)
    {
        case 0:
            return {rotationCoefficients_.at(0).first, rotationCoefficients_.at(0).second};
        case 1:
            return {rotationCoefficients_.at(1).first, rotationCoefficients_.at(1).second};
        case 2:
            return {rotationCoefficients_.at(2).first, rotationCoefficients_.at(2).second};
        default:
            throw std::runtime_error("Error, wrong number of coefficients pair");
    }
}
