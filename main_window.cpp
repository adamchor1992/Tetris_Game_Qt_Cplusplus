#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_Scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_Scene);
    ui->graphicsView->setSceneRect(0,0,302,585);

    DrawGameArena();

    m_pDrawer = new Drawer(m_Scene);
    m_pPlacedBlocks = new PlacedBlocks();

    QFont font( "Arial", 16, QFont::Bold);
    ui->m_ScoreDisplayLabel->setFont(font);
    ui->m_ScoreDisplayLabel->setText("SCORE: " + QString::number(m_Score));

    connect(&m_DropTimer, &QTimer::timeout, this, &MainWindow::GameTick);
    m_DropTimer.start(140);
}

void MainWindow::DrawGameArena()
{
    QBrush whiteBrush(Qt::white);
    QPen sideWallsPen(whiteBrush, 6);
    QPen bottomWallPen(whiteBrush, 5);

    m_Scene->addLine(3, 0, 3, 585, sideWallsPen);
    m_Scene->addLine(299, 0, 299, 585, sideWallsPen);
    m_Scene->addLine(3, 582, 298, 582, bottomWallPen);
}

void MainWindow::GenerateBlock(QString shape)
{
    if(shape == nullptr)
    {
        //random shape
    }
    else if(shape == "S")
    {
        m_pCurrentBlock = new SBlock;
    }
    else if(shape == "Z")
    {
        m_pCurrentBlock = new ZBlock;
    }
    else if(shape == "I")
    {
        m_pCurrentBlock = new IBlock;
    }
    else if(shape == "J")
    {
        m_pCurrentBlock = new JBlock;
    }
    else if(shape == "L")
    {
        m_pCurrentBlock = new LBlock;
    }
    else if(shape == "O")
    {
        m_pCurrentBlock = new OBlock;
    }
    else if(shape == "T")
    {
        m_pCurrentBlock = new TBlock;
    }
    else
    {
        qDebug() << "UNKNOWN SHAPE TO BE GENERATED, ABORTING";
        return;
    }
}

void MainWindow::GenerateRandomBlock()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); //seed based on time

    delete m_pCurrentBlock; //free previously allocated memory

    switch(std::rand() % 7) //choose random shape from 0 to 6
    {
    case 0:
        m_pCurrentBlock = new OBlock;
        break;
    case 1:
        m_pCurrentBlock = new JBlock;
        break;
    case 2:
        m_pCurrentBlock = new LBlock;
        break;
    case 3:
        m_pCurrentBlock = new SBlock;
        break;
    case 4:
        m_pCurrentBlock = new ZBlock;
        break;
    case 5:
        m_pCurrentBlock = new TBlock;
        break;
    case 6:
        m_pCurrentBlock = new IBlock;
        break;
    default:
        qDebug() << "BAD RANDOM NUMBER";
    }

    m_CurrentBlockGraphicsItemsPtrs = m_pDrawer->paintBlock(m_pCurrentBlock->GetBlockCoordinates(), m_pCurrentBlock->GetColor());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_A:
        if(!(m_pCurrentBlock->IsSquaresLeftOfBlock(m_pPlacedBlocks)))
        {
            m_pCurrentBlock->MoveBlock(0);
            RedrawBlock();
        }
        break;

    case Qt::Key_D:
        if(!(m_pCurrentBlock->IsSquaresRightOfBlock(m_pPlacedBlocks)))
        {
            m_pCurrentBlock->MoveBlock(1);
            RedrawBlock();
        }
        break;

    case Qt::Key_W:
        m_pCurrentBlock->RotateBlock();
        break;

    case Qt::Key_S:
        qDebug() << "Drop";
        break;

    case Qt::Key_P:
        qDebug() << "Pause";
        if(m_Paused == false)
        {
            m_DropTimer.stop();
            m_Paused = true;
        }
        else
        {
            m_DropTimer.start();
            m_Paused = false;
        }
        break;

    case Qt::Key_Space:
        qDebug() << "Restart game";
        if(m_ReadyToRestart)
        {
            RestartGame();
        }
        break;

    default:
        qDebug() << "Unknown key";
    }
}

void MainWindow::DrawAllPossibleSquares()
{
    QPen redPen(Qt::red);
    QPen bluePen(Qt::blue);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);

    int const squareSize = 28; //actually its 29x29 pixels because of pen outline

    int order=0;

    for(int j = 0; j<20; j++)
    {
        for(int i = 0; i<10; i++) //rows
        {
            if(order%2 == 0) //every second row
            {
                if(i%2 == 0)
                    m_Scene->addRect(6 + i * 29, j*29, squareSize, squareSize, redPen, redBrush);
                else
                    m_Scene->addRect(6 + i * 29, j*29, squareSize, squareSize, bluePen, blueBrush);
            }
            else
            {
                if(i%2 != 0)
                    m_Scene->addRect(6 + i * 29, j*29, squareSize, squareSize, redPen, redBrush);
                else
                    m_Scene->addRect(6 + i * 29, j*29, squareSize, squareSize, bluePen, blueBrush);
            }
        }
        order++;
    }
}

void MainWindow::RedrawBlock()
{
    m_pDrawer->DeleteBlock(m_CurrentBlockGraphicsItemsPtrs);
    m_CurrentBlockGraphicsItemsPtrs = m_pDrawer->paintBlock(m_pCurrentBlock->GetBlockCoordinates(), m_pCurrentBlock->GetColor());
}

void MainWindow::PlaceCurrentBlock()
{
    QVector<int> blockCoordinates = m_pCurrentBlock->GetBlockCoordinates();

    for(int i=0, j=0 ; i < blockCoordinates.size(); i=i+2, j++)
    {
        m_pPlacedBlocks->AddSquare(blockCoordinates.at(i), blockCoordinates.at(i+1), m_CurrentBlockGraphicsItemsPtrs.at(j));
    }
}

void MainWindow::EndGame()
{
    qDebug() << "GAME OVER";

    ui->statusBar->showMessage("GAME OVER, FINAL SCORE: " + QString::number(m_Score), 4000);
    ui->statusBar->showMessage("PRESS SPACE TO RESTART");

    m_DropTimer.stop();

    m_ReadyToRestart = true;
}

void MainWindow::RestartGame()
{
    m_ReadyToRestart = false;

    m_pDrawer->DeleteBlock(m_CurrentBlockGraphicsItemsPtrs);
    delete m_pPlacedBlocks;
    m_Scene->clear();

    m_pPlacedBlocks = new PlacedBlocks();
    m_pDrawer->PaintPlacedBlocks(m_pPlacedBlocks);

    m_Score = 0;
    ui->m_ScoreDisplayLabel->setText("SCORE: " + QString::number(m_Score));

    m_DropTimer.start();
}

void MainWindow::GameTick()
{
    //create initial block
    if(m_pCurrentBlock == nullptr)
    {
        GenerateRandomBlock();
        return;
    }

    //check if there is something under any of block square
    if(m_pCurrentBlock->IsSquaresUnderBlock(m_pPlacedBlocks))
    {
        //place block
        PlaceCurrentBlock();

        //clear current block
        m_pCurrentBlock = nullptr;

        int howManyFullRows = 0;

        //look for full rows and delete them
        while(m_pPlacedBlocks->FindFullRows() != 0)
        {
            int fullRow = m_pPlacedBlocks->FindFullRows();
            m_pPlacedBlocks->DeleteRow(fullRow);
            m_pPlacedBlocks->DropRowsAbove(fullRow);
            ++howManyFullRows;
        }

        switch(howManyFullRows)
        {
        case 0:
            qDebug() << "NO FULL ROWS";
            break;
        case 1:
            qDebug() << "1 FULL ROW, + 1 point";
            m_Score+=1;
            break;
        case 2:
            qDebug() << "2 FULL ROWS, + 2 points";
            m_Score+=3;
            break;
        case 3:
            qDebug() << "3 FULL ROWS, + 3 points";
            m_Score+=7;
            break;
        case 4:
            qDebug() << "4 FULL ROWS, + 4 points";
            m_Score+=10;
            break;
        default:
            qDebug() << "WRONG FULL ROWS NUMBER";
        }

        //repaint all already placed blocks
        m_pDrawer->PaintPlacedBlocks(m_pPlacedBlocks);

        //update m_Score label
        ui->m_ScoreDisplayLabel->setText("SCORE: " + QString::number(m_Score));
    }

    //generate new block and return immediately so it is not lowered just after creation!
    if(m_pCurrentBlock == nullptr)
    {
        GenerateRandomBlock();

        QVector<int> blockCoordinates = m_pCurrentBlock->GetBlockCoordinates();

        for(int i=0; i<blockCoordinates.size(); i=i+2)
        {
            QPair<int,int> coordinatesPair(blockCoordinates.at(i),blockCoordinates.at(i+1));
            if(m_pPlacedBlocks->m_PlacedBlocksArray.value(coordinatesPair) !=nullptr)
            {
                EndGame();
            }
        }

        return;
    }

    m_pDrawer->DeleteBlock(m_CurrentBlockGraphicsItemsPtrs);
    m_pCurrentBlock->DropBlockCoordinates();
    m_CurrentBlockGraphicsItemsPtrs = m_pDrawer->paintBlock(m_pCurrentBlock->GetBlockCoordinates(), m_pCurrentBlock->GetColor());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pDrawer;
    delete m_pPlacedBlocks;
}
