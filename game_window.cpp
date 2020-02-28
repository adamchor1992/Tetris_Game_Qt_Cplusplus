#include "game_window.h"
#include "ui_game_window.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    m_GameState = GameState::BeforeFirstRun;

    InitializeGameplayAreaScene();
    DrawGameArena();
    PrepareFirstGameRun();
}

void GameWindow::InitializeGameplayAreaScene()
{
    m_Scene.setParent(this);

    int const sceneX = 0;
    int const sceneY = 0;
    int const sceneWidth = ui->m_GraphicsView->geometry().width();
    int const sceneHeight = ui->m_GraphicsView->geometry().height();

    ui->m_GraphicsView->setScene(&m_Scene);
    ui->m_GraphicsView->setSceneRect(sceneX, sceneY, sceneWidth, sceneHeight);
}

void GameWindow::DrawGameArena()
{
    int const wallThickness = 5;

    QBrush whiteBrush(Qt::white);
    QPen wallPen(whiteBrush, wallThickness);

    int const leftBorderX = 0;
    int const leftBorderXOffset = +2;
    int const rightBorderX = 305;
    int const rightBorderXOffset = +2;
    int const bottomY = 610;
    int const bottomYOffset = -3;
    int const topY = 0;
    int const topYOffset = +2;

    /*Left wall*/
    m_Scene.addLine(leftBorderX + leftBorderXOffset, bottomY, leftBorderX + leftBorderXOffset, topY, wallPen);
    /*Right wall*/
    m_Scene.addLine(rightBorderX + rightBorderXOffset, bottomY, rightBorderX + rightBorderXOffset, topY, wallPen);
    /*Bottom wall*/
    m_Scene.addLine(leftBorderX, bottomY + bottomYOffset, rightBorderX, bottomY + bottomYOffset, wallPen);
    /*Top wall*/
    m_Scene.addLine(leftBorderX, topY + topYOffset, rightBorderX, topY + topYOffset, wallPen);
}

void GameWindow::PrepareFirstGameRun()
{
    m_pDrawer = new Drawer(&m_Scene);
    m_pPlacedBlocks = new PlacedBlocks();

    QFont font( "Arial", 16, QFont::Bold);
    ui->m_ScoreDisplayLabel->setFont(font);
    ui->m_ScoreDisplayLabel->setText("SCORE: " + QString::number(m_Score));

    connect(&m_DropTimer, &QTimer::timeout, this, &GameWindow::GameTick);
}

void GameWindow::GenerateBlock(QString shape)
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

void GameWindow::GenerateRandomBlock()
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

    m_CurrentBlockGraphicsItemsPtrs = m_pDrawer->DrawBlock(m_pCurrentBlock->GetBlockCoordinates(), m_pCurrentBlock->GetColor());
}

void GameWindow::RedrawBlock()
{
    m_pDrawer->DeleteBlock(m_CurrentBlockGraphicsItemsPtrs);
    m_CurrentBlockGraphicsItemsPtrs = m_pDrawer->DrawBlock(m_pCurrentBlock->GetBlockCoordinates(), m_pCurrentBlock->GetColor());
}

void GameWindow::PlaceCurrentBlock()
{
    QVector<int> blockCoordinates = m_pCurrentBlock->GetBlockCoordinates();

    for(int i=0, j=0 ; i < blockCoordinates.size(); i=i+2, j++)
    {
        m_pPlacedBlocks->AddSquare(blockCoordinates.at(i), blockCoordinates.at(i+1), m_CurrentBlockGraphicsItemsPtrs.at(j));
    }
}

void GameWindow::EndGame()
{
    qDebug() << "GAME OVER";

    //ui->statusBar->showMessage("GAME OVER, FINAL SCORE: " + QString::number(m_Score), 4000);
    //ui->statusBar->showMessage("PRESS SPACE TO RESTART");

    m_DropTimer.stop();

    m_GameState = GameState::GameStopped;
}

void GameWindow::StartGame()
{
    m_DropTimer.start(140);

    m_GameState = GameState::GameRunning;
}

void GameWindow::RestartGame()
{
    m_pDrawer->DeleteBlock(m_CurrentBlockGraphicsItemsPtrs);
    delete m_pPlacedBlocks;
    m_Scene.clear();

    m_pPlacedBlocks = new PlacedBlocks();
    m_pDrawer->DrawPlacedBlocks(m_pPlacedBlocks);

    m_Score = 0;
    ui->m_ScoreDisplayLabel->setText("SCORE: " + QString::number(m_Score));

    m_DropTimer.start();
    m_GameState = GameState::GameRunning;
}

void GameWindow::GameTick()
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
        m_pDrawer->DrawPlacedBlocks(m_pPlacedBlocks);

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
    m_CurrentBlockGraphicsItemsPtrs = m_pDrawer->DrawBlock(m_pCurrentBlock->GetBlockCoordinates(), m_pCurrentBlock->GetColor());
}

GameWindow::~GameWindow()
{
    delete ui;
    delete m_pDrawer;
    delete m_pPlacedBlocks;
}

void GameWindow::DrawAllPossibleSquares()
{
    QPen redPen(Qt::red);
    QPen bluePen(Qt::blue);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);

    int const wallOffset = 5;

    for(int column = 0; column < GameArenaParameters::MAX_BLOCK_COLUMNS; ++column)
    {
        for(int row = 0; row < GameArenaParameters::MAX_BLOCK_ROWS; ++row)
        {
            /*Different block colour every second column*/
            if(column % 2 == 0)
            {
                if(row % 2 == 0) /*Different block colour every second row*/
                {
                    m_Scene.addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + wallOffset,
                                    row * GameArenaParameters::BLOCK_SQUARE_SIZE + wallOffset,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    Qt::NoPen,
                                    blueBrush);
                }
                else
                {
                    m_Scene.addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + wallOffset,
                                    row * GameArenaParameters::BLOCK_SQUARE_SIZE + wallOffset,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    Qt::NoPen,
                                    redBrush);
                }
            }
            else
            {
                if(row % 2 != 0)
                {
                    m_Scene.addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + wallOffset,
                                    row * GameArenaParameters::BLOCK_SQUARE_SIZE + wallOffset,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    Qt::NoPen,
                                    blueBrush);
                }
                else
                {
                    m_Scene.addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + wallOffset,
                                    row * GameArenaParameters::BLOCK_SQUARE_SIZE + wallOffset,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    Qt::NoPen,
                                    redBrush);
                }
            }
        }
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_A:
        if(m_GameState == GameState::GameRunning)
        {
            if(!(m_pCurrentBlock->IsSquaresLeftOfBlock(m_pPlacedBlocks)))
            {
                m_pCurrentBlock->MoveBlock(Direction::left);
                RedrawBlock();
            }
        }
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
        if(m_GameState == GameState::GameRunning)
        {
            if(!(m_pCurrentBlock->IsSquaresRightOfBlock(m_pPlacedBlocks)))
            {
                m_pCurrentBlock->MoveBlock(Direction::right);
                RedrawBlock();
            }
        }
        break;

    case Qt::Key_Up:
    case Qt::Key_W:
        if(m_GameState == GameState::GameRunning)
        {
            m_pCurrentBlock->RotateBlock();
        }
        break;

    case Qt::Key_Down:
    case Qt::Key_S:
        if(m_GameState == GameState::GameRunning)
        {
            qDebug() << "Drop";
        }
        break;

    case Qt::Key_P:
        if(m_GameState == GameState::GameRunning)
        {
            qDebug() << "Pause";
            m_DropTimer.stop();
            m_GameState = GameState::GamePaused;
        }
        else if(m_GameState == GameState::GamePaused)
        {
            qDebug() << "Unpause";
            m_DropTimer.start();
            m_GameState = GameState::GameRunning;
        }
        break;

    case Qt::Key_Space:
        if(m_GameState == GameState::BeforeFirstRun)
        {
            qDebug() << "Start game";
            StartGame();
        }
        else if(m_GameState == GameState::GameStopped)
        {
            qDebug() << "Restart game";
            RestartGame();
        }
        break;

    default:
        qDebug() << "Unknown key";
    }
}