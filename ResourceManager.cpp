#include "ResourceManager.h"

ResourceManager *ResourceManager::_rm = nullptr;

ResourceManager::ResourceManager()
{
}

sf::Font *ResourceManager::GetDefaultFont()
{
    if (_defaultFont == nullptr) {
        _defaultFont = new sf::Font();
        _defaultFont->loadFromFile("Resources/arial.ttf");
    }

    return _defaultFont;
}

ResourceManager *ResourceManager::GetInstance()
{
    if (_rm == nullptr) {
        _rm = new ResourceManager();
    }
    return _rm;
}