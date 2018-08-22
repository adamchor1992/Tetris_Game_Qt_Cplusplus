#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QTimer>
#include <square.h>

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

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QTimer dropTimer;

    QGraphicsRectItem *square;

public slots:
    void dropBlock();
};

#endif // MAINWINDOW_H
