#pragma once

#include "placed_squares.h"
#include "common.h"
#include "coordinates.h"
#include "random_generator.h"
#include "next_rotation_state_generator.h"

#include <QObject>

typedef int RotationState;

class PlacedSquares;

class AbstractBlock : public QObject
{
Q_OBJECT

    friend std::ostream& operator<<(std::ostream& ofs, AbstractBlock& block);

signals:
    void blockUpdatedEvent(AbstractBlock* abstractBlock);

public:
    explicit AbstractBlock(const QColor& color, const TransformationCoefficients& transformationCoefficientsVsCentralSquare, int rotationCount);
    virtual ~AbstractBlock();

    virtual void rotate(const PlacedSquares& placedSquares) = 0;

    [[nodiscard]] const QVector<std::shared_ptr<Square>>& getSquares() const
    { return squares_; }

    [[nodiscard]] QVector<Coordinates> getSquaresCoordinates() const;
    [[nodiscard]] const Coordinates& getSquareCoordinates(int i) const;
    [[nodiscard]] bool isSquareOrBottomWallUnderBlock(const PlacedSquares& placedSquares) const;
    void dropAndPlace(const PlacedSquares& placedSquares);
    void dropBlockOneLevel();
    void processMove(Direction direction, const PlacedSquares& placedSquares);
    void place(PlacedSquares& placedSquares);
    void processRotation(const PlacedSquares& placedSquares, const RotationCoefficients& rotationCoefficients);

    [[nodiscard]] const QColor& getColor() const
    { return COLOR; }

    static const int SIZE = 4;

protected:
    int currentRotation_ = 0;

private:
    const QColor COLOR;
    static constexpr Coordinates STARTING_CENTRAL_SQUARE_COORDINATES{5, 1};
    QVector<std::shared_ptr<Square>> squares_;
    NextRotationStateGenerator nextRotationStateGenerator_;
};
