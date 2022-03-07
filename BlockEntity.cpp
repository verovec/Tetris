#include "BlockEntity.h"

BlockEntity::BlockEntity(int color)
{
    _color = color;
}

BlockEntity::~BlockEntity()
{

}

std::vector<std::vector<bool>> BlockEntity::GetParts() const
{
    return _parts;
}

void BlockEntity::SetParts(std::vector<std::vector<bool>> parts) {
    _parts = parts;
}

int BlockEntity::GetColor() const
{
    return _color;
}

void BlockEntity::SetY(int y) {
    _y = y;
}

int BlockEntity::GetY() const
{
    return _y;
}

void BlockEntity::SetX(int x) {
    _x = x;
}

int BlockEntity::GetX() const
{
    return _x;
}

int BlockEntity::GetHeight() const
{
    return _parts.size();
}

void BlockEntity::DrawAt(sf::RenderWindow *window, int posX, int posY)
{
    Config *config = Config::GetInstance();
    ColorManager *colorManager = ColorManager::GetInstance();
    sf::Color color = colorManager->GetColor(_color);
    int blockSize = config->GetBlockSize();
    for (int y = 0; y < (int)_parts.size(); y++)
    {
        std::vector<bool> partsLine = _parts[y];
        for (int x = 0; x < (int)partsLine.size(); x++)
        {
            if (partsLine[x])
            {
                sf::RectangleShape cube(sf::Vector2f(blockSize, blockSize));
                cube.setFillColor(color);
                cube.setOutlineThickness(1);
                cube.setOutlineColor(sf::Color(150, 150, 150));
                float xPos = posX + x * blockSize;
                float yPos = posY + y * blockSize;
                cube.setPosition(sf::Vector2f(xPos, yPos));
                window->draw(cube);
            }
        }
    }
}

void BlockEntity::Draw(sf::RenderWindow *window)
{
    Config *config = Config::GetInstance();
    ColorManager *colorManager = ColorManager::GetInstance();
    int boardX = config->GetTopLeftX();
    int boardY = config->GetTopLeftY();
    sf::Color color = colorManager->GetColor(_color);
    int blockSize = config->GetBlockSize();
    for (int y = 0; y < (int)this->_parts.size(); y++)
    {
        std::vector<bool> partsLine = this->_parts[y];
        for (int x = 0; x < (int)partsLine.size(); x++)
        {
            if (partsLine[x])
            {
                sf::RectangleShape cube(sf::Vector2f(blockSize, blockSize));
                cube.setFillColor(color);
                cube.setOutlineThickness(1);
                cube.setOutlineColor(sf::Color(150, 150, 150));
                float xPos = boardX + (blockSize * (_x + x));
                float yPos = boardY + (blockSize * (_y + y));
                cube.setPosition(sf::Vector2f(xPos, yPos));
                window->draw(cube);
            }
        }
    }
}

void BlockEntity::Update(sf::RenderWindow *window)
{
    (void)window;

    Config *config = Config::GetInstance();
    TimeManager& tm = TimeManager::GetInstance();
    unsigned int elapsedTime = tm.GetElapsedTime();
    _timePassed += (elapsedTime / 1000.0f);

    if (_timePassed >= 1.0f / (float)config->GetLevel()) {
        _timePassed = 0.0f;
        _y++;
    }
}

void BlockEntity::MoveRight()
{
    Config *config = Config::GetInstance();
    if (_x + (int)_parts[0].size() < config->GetWidth())
        _x++;
}

void BlockEntity::MoveLeft()
{
    if (_x > 0)
        _x--;
}

void BlockEntity::RotateLeft()
{
    std::vector<std::vector<bool>> rotated;
    int height = _parts.size();
    int width = _parts[0].size();

    for (int x = 0; x < width; x++) {
        rotated.push_back(std::vector<bool>());
        for (int y = 0; y < height; y++) {
            rotated[x].push_back(false);
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            rotated[width - 1 - x][y] = _parts[y][x];
        }
    }
    
    _parts = rotated;
}

void BlockEntity::RotateRight()
{
    std::vector<std::vector<bool>> rotated;
    int height = _parts.size();
    int width = _parts[0].size();

    for (int x = 0; x < width; x++) {
        rotated.push_back(std::vector<bool>());
        for (int y = 0; y < height; y++) {
            rotated[x].push_back(false);
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            rotated[x][height - 1 - y] = _parts[y][x];
        }
    }
    
    _parts = rotated;
}