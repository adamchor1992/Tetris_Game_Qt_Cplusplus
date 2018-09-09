#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include "square.h"
#include "block.h"
#include "drawer.h"
#include "placedblocks.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void drawAllPossibleSquares();

    void drawGameArena();


private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QTimer dropTimer;

    QGraphicsRectItem *square;
    Drawer *drawer;
    Block *current_block;
    QVector<QGraphicsRectItem*> current_block_graphics_items_ptrs;
    PlacedBlocks *placedblocks;

    bool paused;

protected:
    void keyPressEvent(QKeyEvent *event);


public slots:
    void dropBlock();
};

#endif // MAINWINDOW_H
