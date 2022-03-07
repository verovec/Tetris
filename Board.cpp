#include "Board.h"

Board::Board()
{
    Config *config = Config::GetInstance();
    for (int y = 0; y < config->GetHeight(); y++) {
        _blocks.push_back(std::vector<int>());
        for (int x = 0; x < config->GetWidth(); x++) {
            _blocks[y].push_back(0);
        }
    }

    EntityFactory *entityFactory = new EntityFactory();
    for (int i = 0; i < 3; i++)
        _nextBlocks.insert(_nextBlocks.begin(), (BlockEntity *)entityFactory->Create("BlockEntity"));
}

Board::~Board() {
    
}

void Board::AddBlock(BlockEntity *block)
{
    std::vector<std::vector<bool>> parts = block->GetParts();
    for (int y = 0; y < (int)parts.size(); y++) {
        std::vector<bool> lineParts = parts[y];
        for (int x = 0; x < (int)lineParts.size(); x++) {
            if (lineParts[x]) {
                AddBlock(block->GetY() + y, block->GetX() + x, block->GetColor());
            }
        }
    }
    AddBlockEntity();
}

void Board::AddBlock(const int y, const int x, const int color)
{
    _blocks[y][x] = color;
}

void Board::RemoveBlock(const int y, const int x)
{
    _blocks[y][x] = 0;
}

void Board::RemoveLine(int y)
{
    Config *config = Config::GetInstance();
    for (int x = 0; x < config->GetWidth(); x++) {
        RemoveBlock(y, x);
        _blocks[0][x] = 0;
    }
    for (y = y; y > 0; y--) {
        _blocks[y] = _blocks[y - 1];
    }
    _breakedLines++;
    if (_breakedLines % 2 == 0)
        config->AddLevel(1);
}

void Board::RemoveBlockEntity(BlockEntity *block) {
    std::vector<BlockEntity*>::iterator it = std::find(this->_blockEntities.begin(), this->_blockEntities.end(), block);
    this->_blockEntities.erase(it);
    block->~BlockEntity();
}

void Board::AddBlockEntity() {
    BlockEntity *nextBlock = _nextBlocks[_nextBlocks.size() - 1];
    _nextBlocks.pop_back();
    this->_blockEntities.push_back(nextBlock);
    EntityFactory *entityFactory = new EntityFactory();
    _nextBlocks.insert(_nextBlocks.begin(), (BlockEntity *)entityFactory->Create("BlockEntity"));
}

void Board::DrawScene(sf::RenderWindow *window) {
    Config *config = Config::GetInstance();
    ColorManager *colorManager = ColorManager::GetInstance();
    sf::Color color = colorManager->GetColor(8);

    int borderWidth = 20;

    sf::RectangleShape borderLeft(sf::Vector2f(borderWidth, config->GetHeight() * config->GetBlockSize() + borderWidth * 2));
    sf::RectangleShape borderRight(sf::Vector2f(borderWidth, config->GetHeight() * config->GetBlockSize() + borderWidth * 2));
    sf::RectangleShape borderTop(sf::Vector2f(config->GetWidth() * config->GetBlockSize() + borderWidth * 2 + (config->GetBlockSize() * 4), borderWidth));
    sf::RectangleShape borderBottom(sf::Vector2f(config->GetWidth() * config->GetBlockSize() + borderWidth * 2 + (config->GetBlockSize() * 4), borderWidth));
    sf::RectangleShape statusBorderRight(sf::Vector2f(borderWidth, config->GetHeight() * config->GetBlockSize() + borderWidth * 2));
    sf::RectangleShape statusBorderMiddle(sf::Vector2f(borderWidth * 2 + (config->GetBlockSize() * 4), borderWidth));

    borderLeft.setFillColor(color);
    borderRight.setFillColor(color);
    borderTop.setFillColor(color);
    borderBottom.setFillColor(color);
    statusBorderRight.setFillColor(color);
    statusBorderMiddle.setFillColor(color);

    borderLeft.setPosition(sf::Vector2f(config->GetTopLeftX() - borderWidth, config->GetTopLeftY() - borderWidth));
    borderTop.setPosition(sf::Vector2f(config->GetTopLeftX() - borderWidth, config->GetTopLeftY() - borderWidth));
    borderRight.setPosition(sf::Vector2f(config->GetTopLeftX() + config->GetWidth() * config->GetBlockSize(), config->GetTopLeftY() - borderWidth));
    borderBottom.setPosition(sf::Vector2f(config->GetTopLeftX() - borderWidth, config->GetTopLeftY() + config->GetHeight() * config->GetBlockSize()));
    statusBorderRight.setPosition(sf::Vector2f(config->GetTopLeftX() + config->GetWidth() * config->GetBlockSize() + borderWidth + (config->GetBlockSize() * 4), config->GetTopLeftY() - borderWidth));
    statusBorderMiddle.setPosition(sf::Vector2f(config->GetTopLeftX() + config->GetWidth() * config->GetBlockSize(), config->GetTopLeftY() + (config->GetBlockSize() * 16) - borderWidth / 2));

    window->draw(borderLeft);
    window->draw(borderTop);
    window->draw(borderRight);
    window->draw(borderBottom);
    window->draw(statusBorderRight);
    window->draw(statusBorderMiddle);
}

void Board::DrawNextBlock(sf::RenderWindow *window)
{
    Config *config = Config::GetInstance();
    int x = config->GetTopLeftX() + (config->GetWidth() + 1) * config->GetBlockSize();
    int y = config->GetTopLeftY();

    int nextBlocksNumber = (int)_nextBlocks.size();
    for (int i = nextBlocksNumber - 1; i >= 0; i--) {
        int blockY = y + config->GetBlockSize();
        _nextBlocks[i]->DrawAt(window, x, blockY);
        y += (_nextBlocks[i]->GetParts().size() + 1) * config->GetBlockSize();
    }
}

void Board::DrawScoreAndLevel(sf::RenderWindow *window)
{
    Config *config = Config::GetInstance();
    ResourceManager *rm = ResourceManager::GetInstance();

    sf::Text text;
    text.setString("Score : " + std::to_string(_score) + "\nLevel : " + std::to_string(config->GetLevel()));
    text.setFont(*rm->GetDefaultFont());
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);

    text.setPosition(sf::Vector2f(config->GetTopLeftX() + config->GetWidth() * config->GetBlockSize() + 30, config->GetTopLeftY() + (config->GetBlockSize() * 16) + 30));

    window->draw(text);
}

void Board::Draw(sf::RenderWindow *window)
{
    Config *config = Config::GetInstance();
    ColorManager *colorManager = ColorManager::GetInstance();
    int blockPositionX = 0;
    int blockPositionY = 0;

    for (const auto &col: this->_blocks)
    {
        for (const auto &block : col)
        {
            sf::RectangleShape cube(sf::Vector2f(config->GetBlockSize(), config->GetBlockSize()));
            cube.setFillColor(block == 0 ? sf::Color(30, 30, 30) : colorManager->GetColor(block));
            cube.setOutlineThickness(1);
            cube.setOutlineColor(sf::Color(150, 150, 150));
            float positionX = config->GetTopLeftX() + blockPositionX;
            float positionY = config->GetTopLeftY() + blockPositionY;
            cube.setPosition(sf::Vector2f(positionX, positionY));
            window->draw(cube);
            blockPositionX += config->GetBlockSize();
        }
        blockPositionX = 0;
        blockPositionY += config->GetBlockSize();
    }

    DrawScene(window);
    DrawNextBlock(window);
    DrawScoreAndLevel(window);
}

bool Board::TryCollisions(BlockEntity *entity)
{
    for (int y = 0; y < (int)entity->GetParts().size(); y++)
    {
        std::vector<bool> partsLine = entity->GetParts()[y];
        for (int x = 0; x < (int)partsLine.size(); x++)
        {
            if (y + (entity->GetY() + 1) > (int)_blocks.size() - 1) {
                continue;
            }
            if (partsLine[x] && _blocks[y + (entity->GetY() + 1)][x + entity->GetX()] > 0) {
                if (entity->GetY() == 0) {
                    _gameEnded = true;
                    return true;
                }
                AddBlock(entity);
                RemoveBlockEntity(entity);
                return true;
            }
        }
    }
    return false;
}

void Board::UpdateBlocks(sf::RenderWindow *window)
{
    Config *config = Config::GetInstance();
    for (BlockEntity *entity: _blockEntities) {
        if (entity == nullptr) {
            continue;
        }

        if (TryCollisions(entity)) {
            continue;
        }
            
        if (entity->GetY() + entity->GetHeight() >= config->GetHeight()) {
            AddBlock(entity);
            RemoveBlockEntity(entity);
            continue;
        } else {
            entity->Update(window);
            entity->Draw(window);
        }
    }
}

void Board::CheckLines()
{
    int removedLines = 0;
    int removedLinesScores[4] = {40, 100, 300, 1200};
    Config *config = Config::GetInstance();
    for (int y = 0; y < config->GetHeight(); y++) {
        for (int x = 0; x < config->GetWidth(); x++) {
            if (_blocks[y][x] == 0)
                break;
            if (x == config->GetWidth() - 1) {
                RemoveLine(y);
                removedLines++;
            }
        }
    }
    if (removedLines > 0) {
        _score += removedLinesScores[removedLines - 1] * config->GetLevel();
    }
}

void Board::Update(sf::RenderWindow *window)
{
    if (_gameEnded)
        return;
    TimeManager &tm = TimeManager::GetInstance();
    tm.Update();

    Draw(window);

    UpdateBlocks(window);

    CheckLines();
}

void Board::MoveFirstBlock(bool direction)
{
    if (_blockEntities.size() == 0)
        return;
    BlockEntity *block = _blockEntities[0];
    std::vector<std::vector<bool>> parts = block->GetParts();
    int blockX = block->GetX();
    int blockY = block->GetY();

    int searchX = direction ? blockX + parts[0].size() : blockX - 1;

    for (int y = 0; y < (int)parts.size(); y++)
        if (_blocks[y + blockY][searchX] > 0)
            return;
    direction ? block->MoveRight() : block->MoveLeft();
}

void Board::RotateFirstBlock(bool direction)
{
    if (_blockEntities.size() == 0)
        return;
    BlockEntity *block = _blockEntities[0];
    Config *config = Config::GetInstance();

    std::vector<std::vector<bool>> previousParts = block->GetParts();
    int previousX = block->GetX();

    direction ? block->RotateRight() : block->RotateLeft();
    int blockEndX = block->GetX() + (int)block->GetParts()[0].size();
    if (blockEndX >= config->GetWidth())
        block->SetX(config->GetWidth() - (int)block->GetParts()[0].size());

    std::vector<std::vector<bool>> nextParts = block->GetParts();

    for (int y = 0; y < (int)nextParts.size(); y++) {
        for (int x = 0; x < (int)nextParts[y].size(); x++) {
            if (nextParts[y][x] && _blocks[block->GetY() + y][block->GetX() + x] > 0) {
                block->SetX(previousX);
                block->SetParts(previousParts);
                return;
            }
        }
    }
}

bool Board::DownBlock()
{
    if (_blockEntities.size() == 0)
        return false;
    BlockEntity *block = _blockEntities[0];
    if (block == nullptr)
        return false;
    
    int blockY = block->GetY();
    int blockX = block->GetX();
    std::vector<std::vector<bool>> parts = block->GetParts();
    Config *config = Config::GetInstance();

    if (blockY + (int)parts.size() >= config->GetHeight())
        return false;

    for (int y = 0; y < (int)parts.size(); y++) {
        for (int x = 0; x < (int)parts[y].size(); x++) {
            if (parts[y][x] && _blocks[blockY + y + 1][blockX + x] > 0) {
                return false;
            }
        }
    }

    block->SetY(blockY + 1);
    return true;
}

void Board::AddScore(const int score)
{
    _score += score;
}

bool Board::IsGameEnded()
{
    return _gameEnded;
}

void Board::RestartGame()
{
    _blocks.clear();
    _gameEnded = false;
}
