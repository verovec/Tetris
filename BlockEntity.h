#ifndef BLOCK_ENTITY_H
#define BLOCK_ENTITY_H

#include "tgmath.h"
#include <iostream>

#include <SFML/System.hpp>
#include <vector>

#include "Config.h"
#include "ColorManager.h"
#include "AbstractEntity.h"
#include "TimeManager.h"

class BlockEntity : public AbstractEntity
{
public:
    BlockEntity(int);
    virtual ~BlockEntity();
    std::vector<std::vector<bool>> GetParts() const;
    void SetParts(std::vector<std::vector<bool>>);
    int GetColor() const;
    int GetY() const;
    int GetX() const;
    void SetX(int);
    void SetY(int);
    void Draw(sf::RenderWindow *window);
    void DrawAt(sf::RenderWindow *window, int x, int y);
    void Update(sf::RenderWindow *window);
    int GetHeight() const;
    void MoveRight();
    void MoveLeft();
    void RotateRight();
    void RotateLeft();

private:
    int _color;
    std::vector<std::vector<bool>> _parts;
    int _x = 0;
    int _y = 0;
    float _timePassed;
};

#endif // BLOCK_ENTITY_H
