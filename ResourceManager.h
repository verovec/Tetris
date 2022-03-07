#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <SFML/Graphics.hpp>

class ResourceManager
{
    public:
        ResourceManager(ResourceManager &other) = delete;
        void operator=(const ResourceManager &) = delete;
        static ResourceManager *GetInstance();
        sf::Font *GetDefaultFont();
    
    private:
        ResourceManager();
        sf::Font *_defaultFont = nullptr;
        static ResourceManager *_rm;
};

#endif // RESOURCE_MANAGER_H_