#include "game_window.h"
#include "ui_game_window.h"
#include <map>
#include "drawer.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), m_pUi(new Ui::GameWindow)
{
    m_pUi->setupUi(this);

    setWindowTitle("Tetris");
    setFocus(Qt::ActiveWindowFocusReason);

    /*Seed based on time*/
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Drawer::SetScene(&m_Scene);

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

    qDebug("Gameplay scene initialized");
}

void GameWindow::DrawGameArena()
{
    Drawer::DrawGameArena();

    qDebug("Gameplay area drawn");
}

void GameWindow::PrepareFirstGameRun()
{
    m_GameState = GameState::BeforeFirstRun;
    m_Score = 0;

    UpdateScoreLabel();

    SetInformationLabel("PRESS SPACE TO START");

    connect(&m_GameTickTimer, &QTimer::timeout, this, &GameWindow::GameTick);
}

std::unique_ptr<BlockBase> GameWindow::GenerateBlock(QString shape)
{
    std::unique_ptr<BlockBase> pBlock = nullptr;

    if(shape == "random")
    {
        static std::map<int, QString> numberToShapeMapping = { {0,"S"}, {1, "Z"}, {2, "I"}, {3, "J"}, {4, "L"}, {5, "O"}, {6, "T"} };

        int randomNumber = std::rand();

        shape = numberToShapeMapping.at(randomNumber % static_cast<int>(numberToShapeMapping.size()));
    }

    if(shape == "S")
    {
        pBlock = std::make_unique<SBlock>();
    }
    else if(shape == "Z")
    {
        pBlock = std::make_unique<ZBlock>();
    }
    else if(shape == "I")
    {
        pBlock = std::make_unique<IBlock>();
    }
    else if(shape == "J")
    {
        pBlock = std::make_unique<JBlock>();
    }
    else if(shape == "L")
    {
        pBlock = std::make_unique<LBlock>();
    }
    else if(shape == "O")
    {
        pBlock = std::make_unique<OBlock>();
    }
    else if(shape == "T")
    {
        pBlock = std::make_unique<TBlock>();
    }
    else
    {
        qDebug() << "Unknown shape";
        assert(false);
    }

    pBlock->SetBlockSquaresGraphicsRectItemPointers(Drawer::DrawBlock(pBlock->GetBlockCoordinates(), pBlock->GetColor()));

    return pBlock;
}

void GameWindow::PlaceCurrentBlock()
{
    QVector<QPair<int, int> > blockCoordinates = m_pCurrentBlock->GetBlockCoordinates();

    for(int i=0; i < blockCoordinates.size(); i++)
    {
        m_PlacedBlocks.AddSquare(blockCoordinates.at(i).first, blockCoordinates.at(i).second);
    }
}

void GameWindow::StartGame()
{
    SetGameSpeedLevel(m_pUi->m_SpeedHorizontalSlider->value());

    m_pCurrentBlock = GenerateBlock();

    m_PlacedBlocks.ClearPlacedBlocks();

    Drawer::DrawAllPlacedBlocks(m_PlacedBlocks);

    SetScore(0);
    UpdateScoreLabel();

    m_pUi->m_InfoDisplayLabel->hide();

    m_GameState = GameState::GameRunning;

    m_GameTickTimer.start();
}

void GameWindow::EndGame()
{
    m_pCurrentBlock.reset();

    qDebug() << "GAME OVER";

    SetInformationLabel("GAME OVER\nPRESS SPACE TO RESTART");

    m_GameTickTimer.stop();

    m_GameState = GameState::GameStopped;
}

GameWindow::~GameWindow()
{
    delete m_pUi;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    int sliderValue = m_pUi->m_SpeedHorizontalSlider->value();

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
            m_pCurrentBlock->RotateBlock(m_PlacedBlocks);

            Drawer::EraseBlock(m_pCurrentBlock->GetBlockSquaresGraphicsRectItemPointers());
            m_pCurrentBlock->SetBlockSquaresGraphicsRectItemPointers(Drawer::DrawBlock(m_pCurrentBlock->GetBlockCoordinates(), m_pCurrentBlock->GetColor()));
        }
        break;

    case Qt::Key_Down:
    case Qt::Key_S:
        if(m_GameState == GameState::GameRunning)
        {
            m_pCurrentBlock->DropAndPlaceBlock(m_PlacedBlocks);
            qDebug() << "Drop";
        }
        break;

    case Qt::Key_Plus:
        //Subtracting means increasing speed
        m_pUi->m_SpeedHorizontalSlider->setValue(sliderValue - 1);
        break;

    case Qt::Key_Minus:
        //Adding means decreasing speed
        m_pUi->m_SpeedHorizontalSlider->setValue(sliderValue + 1);
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
            qDebug() << "Starting game again";
            StartGame();
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

void GameWindow::SetGameSpeedLevel(int speedLevel)
{
    const int TIME_OFFSET = 50;

    m_GameTickTimer.setInterval(TIME_OFFSET + speedLevel * 20);
}

void GameWindow::on_m_SpeedHorizontalSlider_valueChanged(int value)
{
    SetGameSpeedLevel(value);
}

void GameWindow::GameTick()
{
    /*Check if there is floor or other square under any of block squares*/
    if(m_pCurrentBlock->IsSquareOrBottomWallUnderBlock(m_PlacedBlocks))
    {
        PlaceCurrentBlock();

        m_pCurrentBlock.reset();

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

        /*Redraw all already placed blocks*/
        Drawer::DrawAllPlacedBlocks(m_PlacedBlocks);

        UpdateScoreLabel();

        m_pCurrentBlock = GenerateBlock();

        QVector<QPair<int, int> > blockCoordinates = m_pCurrentBlock->GetBlockCoordinates();

        for(int i=0; i<blockCoordinates.size(); i++)
        {
            QPair<int,int> coordinatesPair(blockCoordinates.at(i).first, blockCoordinates.at(i).second);

            if(m_PlacedBlocks.GetPlacedBlocksMap().value(coordinatesPair) == PlacedBlocks::SquarePresence::SQUARE_PRESENT)
            {
                EndGame();
            }
        }

        /*Return so new block is not lowered just after creation*/
        return;
    }
    else
    {
        m_pCurrentBlock->DropBlockOneLevel();
    }
}
