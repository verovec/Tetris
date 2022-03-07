#ifndef CONFIG_H_
#define CONFIG_H_

#include <SFML/Graphics.hpp>

class Config {
    public:
        Config(Config const&) = delete;
        void operator=(Config const&) = delete;
        static Config *GetInstance();
        int GetWidth();
        int GetHeight();
        float GetTopLeftY();
        float GetTopLeftX();
        int GetBlockSize();
        void Init(sf::Window *window, const int width, const int height, const int blockSize);
        int GetLevel();
        void AddLevel(const int level);

    private:
        Config();
        static Config *_config;
        int _height;
        int _width;
        float _topleftX;
        float _topleftY;
        int _blockSize;
        int _level = 1;
};

#endif // CONFIG_H_

