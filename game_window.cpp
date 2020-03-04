#include "game_window.h"
#include "ui_game_window.h"
#include <map>
#include "drawer.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), m_pUi(new Ui::GameWindow)
{
    m_pUi->setupUi(this);

    Drawer::SetScene(&m_Scene);

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
    Drawer::DrawGameArena();
}

void GameWindow::PrepareFirstGameRun()
{
    m_Score = 0;

    UpdateScoreLabel();

    SetInformationLabel("PRESS SPACE TO START");

    connect(&m_GameTickTimer, &QTimer::timeout, this, &GameWindow::GameTick);
}

void GameWindow::GenerateBlock(QString shape)
{
    delete m_pCurrentBlock; //free previously allocated memory

    if(shape == "random")
    {
        static std::map<int, QString> numberToShapeMapping = { {0,"S"}, {1, "Z"}, {2, "I"}, {3, "J"}, {4, "L"}, {5, "O"}, {6, "T"} };

        std::srand(static_cast<unsigned int>(std::time(nullptr))); //seed based on time

        int randomNumber = std::rand();

        shape = numberToShapeMapping.at(randomNumber % static_cast<int>(numberToShapeMapping.size()));
    }

    if(shape == "S")
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
        assert(false);
    }

    m_pCurrentBlock->SetBlockSquaresGraphicsRectItemPointers(Drawer::DrawBlock(m_pCurrentBlock->GetBlockCoordinates(), m_pCurrentBlock->GetColor()));
}

void GameWindow::PlaceCurrentBlock()
{
    QVector<QPair<int, int> > blockCoordinates = m_pCurrentBlock->GetBlockCoordinates();

    for(int i=0; i < blockCoordinates.size(); i++)
    {
        m_PlacedBlocks.AddSquare(blockCoordinates.at(i).first, blockCoordinates.at(i).second, m_pCurrentBlock->GetBlockSquaresGraphicsRectItemPointers().at(i));
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
    GenerateBlock();

    m_GameTickTimer.start(140);

    m_pUi->m_InfoDisplayLabel->hide();

    m_GameState = GameState::GameRunning;
}

void GameWindow::RestartGame()
{
    GenerateBlock();

    Drawer::EraseBlock(m_pCurrentBlock->GetBlockSquaresGraphicsRectItemPointers());

    m_Scene.clear();

    m_PlacedBlocks.ClearPlacedBlocks();

    Drawer::DrawAllPlacedBlocks(m_PlacedBlocks);

    SetScore(0);

    m_pUi->m_InfoDisplayLabel->hide();

    m_GameTickTimer.start();
    m_GameState = GameState::GameRunning;
}

void GameWindow::GameTick()
{
    /*Check if there is something under any of block square*/
    if(m_pCurrentBlock->IsSquareOrBottomWallUnderBlock(m_PlacedBlocks))
    {
        PlaceCurrentBlock();

        delete m_pCurrentBlock;
        m_pCurrentBlock = nullptr;

        QList<int> fullRows = m_PlacedBlocks.FindFullRows();

        for(auto row : fullRows)
        {
            m_PlacedBlocks.RemoveRow(row);
            m_PlacedBlocks.DropRowsAbove(row);
        }

        switch(fullRows.size())
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
        Drawer::DrawAllPlacedBlocks(m_PlacedBlocks);

        UpdateScoreLabel();
    }

    //generate new block and return immediately so it is not lowered just after creation!
    if(m_pCurrentBlock == nullptr)
    {
        GenerateBlock();

        QVector<QPair<int, int> > blockCoordinates = m_pCurrentBlock->GetBlockCoordinates();

        for(int i=0; i<blockCoordinates.size(); i++)
        {
            QPair<int,int> coordinatesPair(blockCoordinates.at(i).first, blockCoordinates.at(i).second);

            if(m_PlacedBlocks.GetPlacedBlocksMap().value(coordinatesPair) != nullptr)
            {
                EndGame();
            }
        }

        return;
    }

    m_pCurrentBlock->DropBlockOneLevel();
}

GameWindow::~GameWindow()
{
    delete m_pUi;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_A:
        if(m_GameState == GameState::GameRunning)
        {
            if(!(m_pCurrentBlock->IsSquareOrLeftWallLeftOfBlock(m_PlacedBlocks)))
            {
                m_pCurrentBlock->MoveBlock(Direction::left);
            }
        }
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
        if(m_GameState == GameState::GameRunning)
        {
            if(!(m_pCurrentBlock->IsSquareOrRightWallRightOfBlock(m_PlacedBlocks)))
            {
                m_pCurrentBlock->MoveBlock(Direction::right);
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
