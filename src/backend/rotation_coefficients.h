#pragma once

#include <vector>

class RotationCoefficients
{
public:
    explicit RotationCoefficients(const std::pair<int, int>& rotationCoefficients) : rotationCoefficients_(rotationCoefficients)
    {}

    [[nodiscard]] const std::pair<int, int>& getRotationCoefficients() const
    {return rotationCoefficients_;}

private:
    std::pair<int, int> rotationCoefficients_;
};

class RotationCoefficientsContainer
{
public:
    RotationCoefficientsContainer(const std::initializer_list<std::pair<int, int>>& rotationCoefficients);
    [[nodiscard]] std::pair<int, int> getRotationCoefficientsPair(size_t rotationCoefficientsPairIndex) const;

private:
    std::vector<std::pair<int, int>> rotationCoefficients_;
};
