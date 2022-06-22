#pragma once

#include <exception>
#include <QVector>

class Coefficients
{
public:
    [[nodiscard]] virtual std::pair<int, int> getCoefficientsPair(int coefficientsPair) const;

protected:
    Coefficients(std::initializer_list<int> coefficients);

private:
    QVector<int> coefficients_;
};

class RotationCoefficients : public Coefficients
{
public:
    RotationCoefficients(std::initializer_list<int> coefficients) : Coefficients(coefficients) {}
};

class TransformationCoefficients : public Coefficients
{
public:
    TransformationCoefficients(std::initializer_list<int> coefficients) : Coefficients(coefficients) {}
};
