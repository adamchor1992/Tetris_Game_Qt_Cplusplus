#include "game_engine.h"

GameEngine::GameEngine()
{
    m_GameState = GameState::GameStopped;

    QObject::connect(&m_GameSpeedManager.GetGameTickTimer(), &QTimer::timeout, this, &GameEngine::GameTickHandler);
}

void GameEngine::StartGame()
{
    m_PlacedSquares.RemoveAllPlacedSquares();

    m_GameSpeedManager.SetGameSpeed();
    m_ScoreManager.RestartScore();
    m_InfoDisplayManager.HideInfo();

    m_pActiveBlock.reset();
    m_pActiveBlock = BlockBase::MakeBlock();

    m_GameSpeedManager.Start();
    m_GameState = GameState::GameRunning;
}

void GameEngine::EndGame()
{
    m_GameState = GameState::GameStopped;
    m_GameSpeedManager.Stop();

    qDebug() << "GAME OVER";
    m_InfoDisplayManager.SetLabel("GAME OVER\nPRESS SPACE TO RESTART");
}

void GameEngine::TogglePause()
{
    if(m_GameState == GameState::GameRunning)
    {
        m_GameSpeedManager.Stop();
        m_GameState = GameState::GamePaused;
    }
    else if(m_GameState == GameState::GamePaused)
    {
        m_GameSpeedManager.Start();
        m_GameState = GameState::GameRunning;
    }
}

void GameEngine::GameTickHandler()
{
    if(m_GameState == GameState::GameRunning)
    {
        /*Check if there is floor or other square under any of block squares*/
        if(m_pActiveBlock->IsSquareOrBottomWallUnderBlock(m_PlacedSquares))
        {
            m_pActiveBlock->PlaceBlock(m_PlacedSquares);

            m_pActiveBlock.reset();

            QVector<int> fullRows = m_PlacedSquares.FindFullRows();

            if(!fullRows.empty())
            {
                m_ScoreManager.RewardPlayerForFullRows(fullRows.size());

                for(auto row : fullRows)
                {
                    m_PlacedSquares.RemoveFullRow(row);
                    m_PlacedSquares.DropRowsAbove(row);
                }
            }

            m_pActiveBlock = BlockBase::MakeBlock();

            if(m_pActiveBlock->CheckForOverlappingSquares(m_pActiveBlock->GetBlockCoordinates(), m_PlacedSquares))
            {
                EndGame();
            }
        }

        else
        {
            m_pActiveBlock->DropBlockOneLevel();
        }
    }
}

void GameEngine::ProcessKey(QString key)
{
    if(m_GameState == GameState::GameRunning)
    {
        if(key == "left")
        {
            if(m_pActiveBlock->CheckMovePossibility(Direction::left, m_PlacedSquares))
            {
                m_pActiveBlock->MoveBlock(Direction::left);
            }
        }
        else if(key == "right")
        {
            if(m_pActiveBlock->CheckMovePossibility(Direction::right, m_PlacedSquares))
            {
                m_pActiveBlock->MoveBlock(Direction::right);
            }
        }
        else if(key == "up")
        {
            m_pActiveBlock->RotateBlock(m_PlacedSquares);
        }
        else if(key == "down")
        {
            m_pActiveBlock->DropAndPlaceBlock(m_PlacedSquares);
        }
        else if(key == "plus")
        {
            /*Subtracting means increasing speed*/
            m_GameSpeedManager.DecrementSpeed();
        }
        else if(key == "minus")
        {
            /*Adding means decreasing speed*/
            m_GameSpeedManager.IncrementSpeed();
        }
        else if(key == "pause")
        {
            TogglePause();
        }
    }
    else if(m_GameState == GameState::GameStopped)
    {
        if(key == "space")
        {
            StartGame();
        }
    }
    else if(m_GameState == GameState::GamePaused)
    {
        if(key == "pause")
        {
            TogglePause();
        }
    }
}
