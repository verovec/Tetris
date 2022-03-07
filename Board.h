#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Config.h"
#include "ColorManager.h"
#include "BlockEntity.h"
#include "EntityFactory.h"
#include "ResourceManager.h"

class Board : public AbstractEntity
{
public:
    Board();
    virtual ~Board();
    void AddBlockEntity();
    void RemoveBlockEntity(BlockEntity*);
    void AddBlock(BlockEntity *block);
    void AddBlock(const int y, const int x, const int color);
    void RemoveBlock(const int y, const int x);
    void RemoveLine(int y);
    void MoveFirstBlock(bool direction);
    void RotateFirstBlock(bool direction);
    void virtual Draw(sf::RenderWindow *window);
    void virtual Update(sf::RenderWindow *window);
    bool DownBlock();
    void DrawScene(sf::RenderWindow *window);
    void DrawNextBlock(sf::RenderWindow *window);
    void DrawScoreAndLevel(sf::RenderWindow *window);
    void AddScore(const int score);
    bool IsGameEnded();
    void RestartGame();

private:
    void UpdateBlocks(sf::RenderWindow *window);
    bool TryCollisions(BlockEntity *entity);
    void CheckLines();
    std::vector<std::vector<int>> _blocks;
    std::vector<BlockEntity*> _blockEntities;
    std::vector<BlockEntity*> _nextBlocks;
    unsigned int _score = 0;
    int _breakedLines = 0;
    bool _gameEnded = false;
};

#endif // BOARD_H
