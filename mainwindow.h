#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include "block.h"
#include "drawer.h"
#include "placedblocks.h"

#include "iblock.h"
#include "sblock.h"
#include "zblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "tblock.h"

#include <random>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void drawAllPossibleSquares();

    void drawGameArena();

    void generateBlock(QString shape = "0"); //if no argument, then generate random shape
    void generateRandomBlock();

    void placeBlock();

    void findAndDeleteFullRows();

    void redrawBlock();

    void placeCurrentBlock();

    void endGame();
    void restartGame();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QTimer dropTimer;

    QGraphicsRectItem *square;
    Drawer *drawer;
    Block *current_block = nullptr;
    QVector<QGraphicsRectItem*> current_block_graphics_items_ptrs;
    PlacedBlocks *placedblocks;

    bool paused = false;
    int score = 0;
    bool readyToRestart = false;

protected:
    void keyPressEvent(QKeyEvent *event);


public slots:
    void updater();
};

#endif // MAINWINDOW_H
