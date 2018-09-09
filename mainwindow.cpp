#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene); // show QGraphicsScene on GUI widget
    ui->graphicsView->setSceneRect(0,0,302,585);

    qDebug() << "Rozmiar graphics view: " << ui->graphicsView->size();
    qDebug() << "Scene height: " << scene->height();
    qDebug() << "Scene width: " << scene->width();

    drawGameArena();

    drawer = new Drawer(scene, this);

    //Square mysquare;
    //QVector<QPoint> possiblesquares = mysquare.getPossibleSquarePositions_Paint();
    //QVector<int> block_to_draw = {5,5,6,6,7,7,8,8};

//    Block my_block("I", this);
//    Block my_block("J", this);
//    Block my_block("L", this);
//    Block my_block("S", this);
//    Block my_block("Z", this);
//    Block my_block("O", this);

    current_block = new Block("O", this);

//    qDebug() << "VECTOR 1";
//    for(int item : my_block.getBlockCoordinates())
//    {
//        qDebug() << item;
//    }

    current_block_graphics_items_ptrs = drawer->paintBlock(current_block->getBlockCoordinates());

    placedblocks = new PlacedBlocks(this);

    paused = false;

    connect(&dropTimer, SIGNAL(timeout()), this, SLOT(dropBlock()));
    dropTimer.start(60);
}

void MainWindow::drawGameArena()
{
    QBrush white_brush(Qt::white);
    QPen side_walls_pen(white_brush, 6);
    QPen bottom_wall_pen(white_brush, 5);

    scene->addLine(3,0,3,585,side_walls_pen);
    scene->addLine(299,0,299,585,side_walls_pen);
    scene->addLine(3,582,298,582,bottom_wall_pen);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_A:
        if(!(current_block->isSquaresLeftOfBlock(placedblocks)))
        {
            current_block->moveBlock(0);
        }
        break;

    case Qt::Key_D:
        if(!(current_block->isSquaresRightOfBlock(placedblocks)))
        {
            current_block->moveBlock(1);
        }
        break;

    case Qt::Key_W:
        qDebug() << "Rotate";
        break;

    case Qt::Key_S:
        qDebug() << "Drop";
        break;

    case Qt::Key_P:
        qDebug() << "Pause";
        if(paused == false)
        {
            dropTimer.stop();
            paused = true;
        }
        else
        {
            dropTimer.start(60);
            paused = false;
        }

        break;

    default:
        qDebug() << "Unknown key";
    }
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
    bool new_block = false;
    //qDebug() << "Timeout";

    //check if there is something under any of block square
    if(current_block->isSquaresUnderBlock(placedblocks))
    {
        //place block
        QVector<int> block_coordinates = current_block->getBlockCoordinates();

        for(int i=0, j=0 ; i < block_coordinates.size(); i=i+2, j++)
        {
            placedblocks->addSquare(block_coordinates.at(i), block_coordinates.at(i+1), current_block_graphics_items_ptrs.at(j));
        }

        while(placedblocks->findFullRows() != 0)
        {
            int full_row = placedblocks->findFullRows();
            qDebug() << "Full row: " << full_row;
            placedblocks->deleteRow(full_row);
            qDebug() << "Deleting row number: " << full_row;
            placedblocks->dropRowsAbove(full_row);
        }

        drawer->paintPlacedBlocks(placedblocks);

        current_block = new Block("O", this);

        new_block = true;

//        for(auto item : placedblocks->placedBlocksArray.keys())
//        {
//            qDebug() << item;
//        }
    }

    if(!new_block)
    {
        drawer->deleteBlock(current_block_graphics_items_ptrs);
    }

    current_block->dropBlockCoordinates();
    current_block_graphics_items_ptrs = drawer->paintBlock(current_block->getBlockCoordinates());
}



MainWindow::~MainWindow()
{
    delete ui;
}
