#include "game_window.h"
#include "ui_game_window.h"
#include <map>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), m_pUi(new Ui::GameWindow)
{
    m_pUi->setupUi(this);

    m_pDrawer = new Drawer(m_Scene);
    m_pPlacedBlocks = new PlacedBlocks();

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
    int const sceneWidth = m_pUi->m_GraphicsView->geometry().width();
    int const sceneHeight = m_pUi->m_GraphicsView->geometry().height();

    m_pUi->m_GraphicsView->setScene(&m_Scene);
    m_pUi->m_GraphicsView->setSceneRect(sceneX, sceneY, sceneWidth, sceneHeight);
}

void GameWindow::DrawGameArena()
{
    m_pDrawer->DrawGameArena();
}

void GameWindow::PrepareFirstGameRun()
{
    m_Score = 0;

    UpdateScoreLabel();

    SetInformationLabel("PRESS SPACE TO START");

    connect(&m_GameTickTimer, &QTimer::timeout, this, &GameWindow::GameTick);
}

void GameWindow::GenerateInitialBlock()
{
    if(m_pCurrentBlock == nullptr)
    {
        m_pCurrentBlock = GenerateBlock();

        m_CurrentBlockGraphicsItemsPtrs = m_pDrawer->DrawBlock(m_pCurrentBlock->GetBlockCoordinates(), m_pCurrentBlock->GetColor());
    }
}

BlockBase* GameWindow::GenerateBlock(QString shape)
{
    delete m_pCurrentBlock; //free previously allocated memory

    BlockBase* block = nullptr;

    if(shape == "random")
    {
        static std::map<int, QString> numberToShapeMapping = { {0,"S"}, {1, "Z"}, {2, "I"}, {3, "J"}, {4, "L"}, {5, "O"}, {6, "T"} };

        std::srand(static_cast<unsigned int>(std::time(nullptr))); //seed based on time

        int randomNumber = std::rand();

        shape = numberToShapeMapping.at(randomNumber % static_cast<int>(numberToShapeMapping.size()));
    }

    if(shape == "S")
    {
        block = new SBlock;
    }
    else if(shape == "Z")
    {
        block = new ZBlock;
    }
    else if(shape == "I")
    {
        block = new IBlock;
    }
    else if(shape == "J")
    {
        block = new JBlock;
    }
    else if(shape == "L")
    {
        block = new LBlock;
    }
    else if(shape == "O")
    {
        block = new OBlock;
    }
    else if(shape == "T")
    {
        block = new TBlock;
    }
    else
    {
        qDebug() << "UNKNOWN SHAPE TO BE GENERATED, ABORTING";
        assert(false);
    }

    return block;
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

    SetInformationLabel("GAME OVER\nPRESS SPACE TO RESTART");

    m_GameTickTimer.stop();

    m_GameState = GameState::GameStopped;
}

void GameWindow::StartGame()
{
    GenerateInitialBlock();

    m_GameTickTimer.start(140);

    m_pUi->m_InfoDisplayLabel->hide();

    m_GameState = GameState::GameRunning;
}

void GameWindow::RestartGame()
{
    GenerateInitialBlock();

    m_pDrawer->DeleteBlock(m_CurrentBlockGraphicsItemsPtrs);
    delete m_pPlacedBlocks;
    m_Scene.clear();

    m_pPlacedBlocks = new PlacedBlocks();
    m_pDrawer->DrawPlacedBlocks(m_pPlacedBlocks);

    SetScore(0);

    m_pUi->m_InfoDisplayLabel->hide();

    m_GameTickTimer.start();
    m_GameState = GameState::GameRunning;
}

void GameWindow::GameTick()
{
    /*Check if there is something under any of block square*/
    if(m_pCurrentBlock->IsSquaresUnderBlock(m_pPlacedBlocks))
    {
        //place block
        PlaceCurrentBlock();

        //clear current block
        m_pCurrentBlock = nullptr;

        int fullRowsCount = 0;

        //look for full rows and delete them
        while(m_pPlacedBlocks->FindFullRow() != 0)
        {
            int fullRow = m_pPlacedBlocks->FindFullRow();
            m_pPlacedBlocks->DeleteRow(fullRow);
            m_pPlacedBlocks->DropRowsAbove(fullRow);
            ++fullRowsCount;
        }

        switch(fullRowsCount)
        {
        case 0:
            qDebug() << "NO FULL ROWS";
            break;
        case 1:
            qDebug() << "1 FULL ROW, + 1 point";
            IncreaseScore(1);
            break;
        case 2:
            qDebug() << "2 FULL ROWS, + 3 points";
            IncreaseScore(3);
            break;
        case 3:
            qDebug() << "3 FULL ROWS, + 7 points";
            IncreaseScore(7);
            break;
        case 4:
            qDebug() << "4 FULL ROWS, + 10 points";
            IncreaseScore(10);
            break;
        default:
            qDebug() << "WRONG FULL ROWS NUMBER";
        }

        //repaint all already placed blocks
        m_pDrawer->DrawPlacedBlocks(m_pPlacedBlocks);

        UpdateScoreLabel();
    }

    //generate new block and return immediately so it is not lowered just after creation!
    if(m_pCurrentBlock == nullptr)
    {
        m_pCurrentBlock = GenerateBlock();

        m_CurrentBlockGraphicsItemsPtrs = m_pDrawer->DrawBlock(m_pCurrentBlock->GetBlockCoordinates(), m_pCurrentBlock->GetColor());

        QVector<int> blockCoordinates = m_pCurrentBlock->GetBlockCoordinates();

        for(int i=0; i<blockCoordinates.size(); i=i+2)
        {
            QPair<int,int> coordinatesPair(blockCoordinates.at(i),blockCoordinates.at(i+1));
            if(m_pPlacedBlocks->getPlacedBlocksMap().value(coordinatesPair) !=nullptr)
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
    delete m_pUi;
    delete m_pDrawer;
    delete m_pPlacedBlocks;
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
            m_GameTickTimer.stop();
            m_GameState = GameState::GamePaused;
        }
        else if(m_GameState == GameState::GamePaused)
        {
            qDebug() << "Unpause";
            m_GameTickTimer.start();
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

void GameWindow::UpdateScoreLabel()
{
    m_pUi->m_ScoreDisplayLabel->setText("SCORE: " + QString::number(m_Score));
}

void GameWindow::SetInformationLabel(QString text)
{
    m_pUi->m_InfoDisplayLabel->setText(text);
    m_pUi->m_InfoDisplayLabel->show();
}
