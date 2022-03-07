#include "Config.h"

Config *Config::_config = nullptr;

Config::Config()
{
}

void Config::Init(sf::Window *window, const int width, const int height, const int blockSize)
{
    _blockSize = blockSize;
    _width = width;
    _height = height;
    _topleftX = window->getSize().x / 2.0f - (_width / 2) * _blockSize;
    _topleftY = window->getSize().y / 10.0f;
}

int Config::GetWidth()
{
    return _width;
}

int Config::GetHeight()
{
    return _height;
}

float Config::GetTopLeftY()
{
    return _topleftY;
}

float Config::GetTopLeftX()
{
    return _topleftX;
}

int Config::GetBlockSize()
{
    return _blockSize;
}

Config *Config::GetInstance()
{
    if (_config == nullptr)
        _config = new Config();
    return _config;
}

int Config::GetLevel()
{
    return _level;
}

void Config::AddLevel(const int level)
{
    _level += level;
}