#pragma once

#include "placed_squares.h"
#include "random_generator.h"
#include "common.h"
#include "rotation_coefficients_database.h"

class Block
{
    friend std::ostream& operator<<(std::ostream& ofs, Block& block);

public:
    explicit Block(const BlockShape& blockShape, const QColor& color);

    [[nodiscard]] const BlockCoordinatesArray& getAllSquaresCoordinates() const;
    [[nodiscard]] BlockCoordinatesArray& getAllSquaresCoordinates();
    [[nodiscard]] const Coordinates& getSquareCoordinates(int i) const;
    [[nodiscard]] Coordinates& getSquareCoordinates(int i);
    [[nodiscard]] Coordinates getCentralSquareCoordinates() const;

    [[nodiscard]] const QColor& getColor() const
    { return color_; }

    [[nodiscard]] const RotationStateToRotationCoefficientsContainerMapping& getRotationCoefficients() const
    { return rotationStateToRotationCoefficientsContainerMapping; }

    [[nodiscard]] const RotationStateIterator& getRotationStateIterator() const
    { return rotationStateIterator_; }

    [[nodiscard]] RotationStateIterator& getRotationStateIterator()
    { return rotationStateIterator_; }

    void setBlockCoordinates(const BlockCoordinatesArray& blockCoordinatesArray);

private:
    const BlockShape blockShape_;
    const QColor color_;
    const RotationStateToRotationCoefficientsContainerMapping& rotationStateToRotationCoefficientsContainerMapping;

    RotationStateIterator rotationStateIterator_;
    BlockCoordinatesArray squaresCoordinates_{};
};
