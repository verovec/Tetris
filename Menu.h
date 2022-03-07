#ifndef MENU_H_
#define MENU_H_

#include "AbstractEntity.h"
#include "GameManager.h"
#include "ResourceManager.h"

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

class Menu : public AbstractEntity
{
    public:
        Menu();
        void Draw(sf::RenderWindow *window);
        void Update(sf::RenderWindow *window);
        void SetMenuNumber(int);
        void SetChoice(int);
        int GetChoice() const;

    private:
        int _menuNumber;
        int _choice;
};

#endif // MENU_H_
