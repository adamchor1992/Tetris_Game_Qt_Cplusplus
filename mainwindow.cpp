#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    //connect(&dropTimer, SIGNAL(timeout()), this, SLOT(dropBlock()));
    //dropTimer.start(1000);

    ui->graphicsView->setScene(scene); // show QGraphicsScene on GUI widget

    ui->graphicsView->setSceneRect(0,0,302,585);

    qDebug() << "Rozmiar graphics view: " << ui->graphicsView->size();
    qDebug() << "Scene height: " << scene->height();
    qDebug() << "Scene width: " << scene->width();

    QBrush white_brush(Qt::white);
    QPen side_walls_pen(white_brush, 6);
    QPen bottom_wall_pen(white_brush, 5);

    scene->addLine(3,0,3,585,side_walls_pen);
    scene->addLine(299,0,299,585,side_walls_pen);
    scene->addLine(3,582,298,582,bottom_wall_pen);

    Square mysquare;
    QVector<QPoint> possiblesquares = mysquare.getPossibleSquarePositions_Paint();

    scene->addRect(possiblesquares.at(20).x(),possiblesquares.at(20).y(),28,28,QPen(Qt::red),QBrush(Qt::red));

    scene->addRect(possiblesquares.at(31).x(),possiblesquares.at(31).y(),28,28,QPen(Qt::red),QBrush(Qt::red));

    scene->addRect(possiblesquares.at(37).x(),possiblesquares.at(37).y(),28,28,QPen(Qt::red),QBrush(Qt::red));
//    foreach(QPoint item, possiblesquares)
//    {
//        scene->addRect(item.x(),item.y(),28,28,QPen(Qt::red),QBrush(Qt::red));
//    }

    //square = scene->addRect(6 + 29,29,28,28,QPen(Qt::red),QBrush(Qt::red));

    //drawAllPossibleSquares();
}

void MainWindow::drawAllPossibleSquares()
{
    QPen red_pen(Qt::red);
    QPen white_pen(Qt::white);
    QPen blue_pen(Qt::blue);
    QPen green_pen(Qt::green);

    QBrush red_brush(Qt::red);
    QBrush white_brush(Qt::white);
    QBrush blue_brush(Qt::blue);
    QBrush green_brush(Qt::green);

    const int square_size = 28; //actually its 29x29 pixels...

    int order=0;

    for(int j = 0; j<20; j++)
    {
        for(int i = 0; i<10; i++) //rows
        {
            if(order%2 == 0) //every second row
            {
                if(i%2 == 0)
                    scene->addRect(6 + i * 29,j*29,square_size,square_size,red_pen,red_brush);
                else
                    scene->addRect(6 + i * 29,j*29,square_size,square_size,blue_pen,blue_brush);
            }
            else
            {
                if(i%2 != 0)
                    scene->addRect(6 + i * 29,j*29,square_size,square_size,red_pen,red_brush);
                else
                    scene->addRect(6 + i * 29,j*29,square_size,square_size,blue_pen,blue_brush);
            }
        }
        order++;
    }
}

void MainWindow::dropBlock() //SLOT
{
    qDebug() << "Timeout";
    square->moveBy(0,29);
}

MainWindow::~MainWindow()
{
    delete ui;
}
