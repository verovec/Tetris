#include "Menu.h"


Menu::Menu() {
    _choice = 1;
}

void Menu::SetMenuNumber(int menuNumber) {
    _menuNumber = menuNumber;
}

void Menu::SetChoice(int choice) {
    if (choice > 2)
        choice = 2;
    else if (choice < 1)
        choice = 1;
    _choice = choice;
}

int Menu::GetChoice() const {
    return _choice;
}

void Menu::Draw(sf::RenderWindow *window) {
    GameManager *gameManager = GameManager::GetInstance();
    ResourceManager *rm = ResourceManager::GetInstance();
    
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture logoTexture;
    sf::Sprite logoSprite;

    float windowWidth = window->getSize().x;
    float windowHeight = window->getSize().y;
    float xPos = windowWidth / 2 - 75;
    float yPos = windowHeight / 2;

    backgroundTexture.loadFromFile("Resources/images/background.png");
    logoTexture.loadFromFile("Resources/images/logo.png");
    backgroundSprite.setTexture(backgroundTexture);
    logoSprite.setTexture(logoTexture);
    backgroundSprite.setPosition(sf::Vector2f((windowWidth / 2) - (backgroundSprite.getTexture()->getSize().x / 2), windowHeight - (backgroundSprite.getTexture()->getSize().y)));
    logoSprite.setPosition(sf::Vector2f((windowWidth / 2) - (logoSprite.getTexture()->getSize().x / 2), 50));

    sf::Text text;
    text.setFont(*rm->GetDefaultFont());
    text.setCharacterSize(60);
    text.setStyle(sf::Text::Bold);

    string firstButtonPath;
    string secondButtonPath;

    if (gameManager->GetState() == 1) {
        text.setString("Menu");
        text.setFillColor(sf::Color::White);
        text.setPosition(sf::Vector2f(xPos, yPos - 150));
        firstButtonPath = "Resources/images/sprites/play-button";
        secondButtonPath = "Resources/images/sprites/exit-game-button";
    }
    else if (gameManager->GetState() == 2) {
        text.setString("Pause");
        text.setFillColor(sf::Color::White);
        text.setPosition(sf::Vector2f(xPos - 12, yPos - 150));
        firstButtonPath = "Resources/images/sprites/resume-button";
        secondButtonPath = "Resources/images/sprites/menu-button";
    }
    else if (gameManager->GetState() == 3) {
        text.setString("Game Over");
        text.setFillColor(sf::Color::Red);
        text.setPosition(sf::Vector2f(xPos - 85, yPos - 150));
        firstButtonPath = "Resources/images/sprites/menu-button";
        secondButtonPath = "Resources/images/sprites/exit-game-button";
    }

    sf::Texture firstButtonTexture;
    sf::Sprite firstButtonSprite;

    sf::Texture secondButtonTexture;
    sf::Sprite secondButtonSprite;
    
    if (_choice == 1) {
        firstButtonTexture.loadFromFile(firstButtonPath + "-selected.png");
        firstButtonSprite.setTexture(firstButtonTexture);
        secondButtonTexture.loadFromFile(secondButtonPath + ".png");
        secondButtonSprite.setTexture(secondButtonTexture);
    } else if (_choice == 2) {
        firstButtonTexture.loadFromFile(firstButtonPath + ".png");
        firstButtonSprite.setTexture(firstButtonTexture);
        secondButtonTexture.loadFromFile(secondButtonPath + "-selected.png");
        secondButtonSprite.setTexture(secondButtonTexture);
    }

    firstButtonSprite.setPosition(sf::Vector2f(xPos, yPos - 50));
    secondButtonSprite.setPosition(sf::Vector2f(xPos, yPos + 20));

    window->draw(backgroundSprite);
    window->draw(logoSprite);
    window->draw(text);
    window->draw(firstButtonSprite);
    window->draw(secondButtonSprite);
}

void Menu::Update(sf::RenderWindow *window) {
    Draw(window);
}

