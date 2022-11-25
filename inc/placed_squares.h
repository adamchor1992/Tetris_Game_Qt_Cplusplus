#pragma once

#include "coordinates.h"
#include "square.h"
#include "abstract_block.h"

#include <QMap>
#include <QObject>

using CoordinatesToSquaresMapping = QMap<Coordinates, std::shared_ptr<Square>>;

class AbstractBlock;

class PlacedSquares : public QObject
{
    Q_OBJECT

signals:
    void placedSquaresUpdatedEvent(PlacedSquares* placedSquares);

public:
    PlacedSquares() = default;
    ~PlacedSquares();

    [[nodiscard]] const CoordinatesToSquaresMapping& getCoordinatesToSquaresMapping() const
    { return coordinatesToSquaresMapping_; }

    CoordinatesToSquaresMapping& getCoordinatesToSquaresMapping()
    { return coordinatesToSquaresMapping_; }

    void removeAllPlacedSquares();
    [[nodiscard]] QVector<int> findFullRows() const;
    void removeRow(int rowNumber);
    void dropRowsAboveRow(int removedRow);
    void placeBlock(AbstractBlock* abstractBlock);

private:
    void removeSquare(const Coordinates& coordinates);

    CoordinatesToSquaresMapping coordinatesToSquaresMapping_;
};
