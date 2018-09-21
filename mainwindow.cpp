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

    drawGameArena();

    drawer = new Drawer(scene, this);
    placedblocks = new PlacedBlocks(this);

    QFont font( "Arial", 16, QFont::Bold);
    ui->score_display_label->setFont(font);
    ui->score_display_label->setText("SCORE: " + QString::number(score));

    connect(&dropTimer, SIGNAL(timeout()), this, SLOT(updater()));
    dropTimer.start(140);
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

void MainWindow::generateBlock(QString shape)
{
    if(shape == nullptr)
    {
        //random shape
    }
    else if(shape == "S")
    {
        current_block = new SBlock;
    }
    else if(shape == "Z")
    {
        current_block = new ZBlock;
    }
    else if(shape == "I")
    {
        current_block = new IBlock;
    }
    else if(shape == "J")
    {
        current_block = new JBlock;
    }
    else if(shape == "L")
    {
        current_block = new LBlock;
    }
    else if(shape == "O")
    {
        current_block = new OBlock;
    }
    else if(shape == "T")
    {
        current_block = new TBlock;
    }
    else
    {
        qDebug() << "UNKNOWN SHAPE TO BE GENERATED, ABORTING";
        return;
    }
}

void MainWindow::generateRandomBlock()
{
    std::srand(std::time(nullptr)); //seed based on time

    delete current_block; //free previously allocated memory

    switch(std::rand() % 7) //choose random shape from 0 to 6
    {
    case 0:
        current_block = new OBlock;
        break;
    case 1:
        current_block = new JBlock;
        break;
    case 2:
        current_block = new LBlock;
        break;
    case 3:
        current_block = new SBlock;
        break;
    case 4:
        current_block = new ZBlock;
        break;
    case 5:
        current_block = new TBlock;
        break;
    case 6:
        current_block = new IBlock;
        break;
    default:
        qDebug() << "BAD RANDOM NUMBER";
    }

    current_block_graphics_items_ptrs = drawer->paintBlock(current_block->getBlockCoordinates(), current_block->getColor());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_A:
        if(!(current_block->isSquaresLeftOfBlock(placedblocks)))
        {
            current_block->moveBlock(0);
            redrawBlock();
        }
        break;

    case Qt::Key_D:
        if(!(current_block->isSquaresRightOfBlock(placedblocks)))
        {
            current_block->moveBlock(1);
            redrawBlock();
        }
        break;

    case Qt::Key_W:
        current_block->rotateBlock();
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
            dropTimer.start();
            paused = false;
        }
        break;

    case Qt::Key_Space:
        qDebug() << "Restart game";
        if(readyToRestart)
        {
            restartGame();
        }

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

void MainWindow::redrawBlock()
{
    drawer->deleteBlock(current_block_graphics_items_ptrs);
    current_block_graphics_items_ptrs = drawer->paintBlock(current_block->getBlockCoordinates(), current_block->getColor());
}

void MainWindow::placeCurrentBlock()
{
    QVector<int> block_coordinates = current_block->getBlockCoordinates();
    for(int i=0, j=0 ; i < block_coordinates.size(); i=i+2, j++)
    {
        placedblocks->addSquare(block_coordinates.at(i), block_coordinates.at(i+1), current_block_graphics_items_ptrs.at(j));
    }
}

void MainWindow::endGame()
{
    qDebug() << "GAME OVER";

    ui->statusBar->showMessage("GAME OVER, FINAL SCORE: " + QString::number(score), 4000);
    ui->statusBar->showMessage("PRESS SPACE TO RESTART");

    dropTimer.stop();

    readyToRestart = true;
}

void MainWindow::restartGame()
{
    readyToRestart = false;

    drawer->deleteBlock(current_block_graphics_items_ptrs);
    delete placedblocks;
    scene->clear();

    placedblocks = new PlacedBlocks(this);
    drawer->paintPlacedBlocks(placedblocks);

    score = 0;
    ui->score_display_label->setText("SCORE: " + QString::number(score));

    dropTimer.start();
}

void MainWindow::updater() //SLOT
{
    //create initial block
    if(current_block == nullptr)
    {
        generateRandomBlock();
        return;
    }

    //check if there is something under any of block square
    if(current_block->isSquaresUnderBlock(placedblocks))
    {
        //place block
        placeCurrentBlock();

        //clear current block
        current_block = nullptr;

        int howManyFullRows = 0;

        //look for full rows and delete them
        while(placedblocks->findFullRows() != 0)
        {
            int full_row = placedblocks->findFullRows();
            placedblocks->deleteRow(full_row);
            placedblocks->dropRowsAbove(full_row);
            howManyFullRows++;
        }

        switch(howManyFullRows)
        {
        case 0:
            qDebug() << "NO FULL ROWS";
            break;
        case 1:
            qDebug() << "1 FULL ROW, + 1 point";
            score+=1;
            break;
        case 2:
            qDebug() << "2 FULL ROWS, + 2 points";
            score+=3;
            break;
        case 3:
            qDebug() << "3 FULL ROWS, + 3 points";
            score+=7;
            break;
        case 4:
            qDebug() << "4 FULL ROWS, + 4 points";
            score+=10;
            break;
        default:
            qDebug() << "WRONG FULL ROWS NUMBER";
        }

        //repaint all already placed blocks
        drawer->paintPlacedBlocks(placedblocks);

        //update score label
        ui->score_display_label->setText("SCORE: " + QString::number(score));
    }

    //generate new block and return immediately so it is not lowered just after creation!
    if(current_block == nullptr)
    {
        generateRandomBlock();

        QVector<int> blockcoordinates = current_block->getBlockCoordinates();

        for(int i=0; i<blockcoordinates.size(); i=i+2)
        {
            QPair<int,int> coordinates_pair(blockcoordinates.at(i),blockcoordinates.at(i+1));
            if(placedblocks->placedBlocksArray.value(coordinates_pair) !=nullptr)
            {
                endGame();
            }
        }

        return;
    }

    drawer->deleteBlock(current_block_graphics_items_ptrs);
    current_block->dropBlockCoordinates();
    current_block_graphics_items_ptrs = drawer->paintBlock(current_block->getBlockCoordinates(), current_block->getColor());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete drawer;
    delete placedblocks;
}
