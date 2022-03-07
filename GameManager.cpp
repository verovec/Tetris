#include "GameManager.h"

GameManager *GameManager::_gameManager = nullptr;

GameManager::GameManager()
{
    
}

GameManager *GameManager::GetInstance()
{
    if (_gameManager == nullptr)
        _gameManager = new GameManager();
    return _gameManager;
}

int GameManager::GetState()
{
    return _state;
}

void GameManager::SetState(int state)
{
    _state = state;
}
