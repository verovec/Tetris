#ifndef ABSTRACT_ENTITY_H_
#define ABSTRACT_ENTITY_H_

#include <SFML/Graphics.hpp>

class AbstractEntity
{
    public:
        virtual void Draw(sf::RenderWindow *window) = 0;
        virtual void Update(sf::RenderWindow *window) = 0;
};

#endif // ABSTRACT_ENTITY_H_