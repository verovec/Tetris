#include "ColorManager.h"

ColorManager *ColorManager::_colorManager = nullptr;

ColorManager::ColorManager()
{
    
}

ColorManager *ColorManager::GetInstance()
{
    if (_colorManager == nullptr)
        _colorManager = new ColorManager();
    return _colorManager;
}

sf::Color ColorManager::GetColor(const int colorIndex)
{
    if (colorIndex < 1 || colorIndex > (int)_colors.size())
        return _colors.at(0);
    return _colors.at(colorIndex - 1);
}