#ifndef COLOR_MANAGER_H_
#define COLOR_MANAGER_H_

#include <vector>

#include <SFML/Graphics.hpp>

class ColorManager {
    public:
        ColorManager(ColorManager const&) = delete;
        void operator=(ColorManager const&) = delete;
        static ColorManager *GetInstance();
        sf::Color GetColor(const int colorIndex);

    private:
        ColorManager();
        static ColorManager *_colorManager;
        std::vector<sf::Color> _colors = {
            sf::Color::Red,
            sf::Color::Green,
            sf::Color(255, 111, 0),
            sf::Color::Yellow,
            sf::Color(130, 2, 166),
            sf::Color::Blue,
            sf::Color::Cyan,
            sf::Color(0, 85, 255)
        };
};

#endif // COLOR_MANAGER_H_