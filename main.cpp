#include "Config.h"
#include "Board.h"
#include "EntityFactory.h"
#include "GameManager.h"
#include "Menu.h"

#include <cstdio>
#include <unistd.h>
#include <SFML/Audio.hpp>

int main()
{
    srand(time(NULL));
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Tetris", sf::Style::Fullscreen);
    window->setFramerateLimit(60);

    Config *config = Config::GetInstance();
    config->Init(window, 10, 20, 40);

    GameManager *gameManager = GameManager::GetInstance();
    gameManager->SetState(1);

    Menu *menu = new Menu();

    Board *board = new Board();

    EntityFactory entityFactory = EntityFactory();

    sf::SoundBuffer buffer;
    sf::Sound sound;

    buffer.loadFromFile("Resources/sound/Tetris.ogg");
    sound.setBuffer(buffer);
    sound.play();
    sound.setLoop(true);
    
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (gameManager->GetState() != 0) {
                if (event.type == sf::Event::MouseWheelScrolled) {
                    if (event.mouseWheelScroll.delta > 0) {
                        menu->SetChoice(menu->GetChoice() - 1);
                    }
                    if (event.mouseWheelScroll.delta < 0) {
                        menu->SetChoice(menu->GetChoice() + 1);
                    }
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        if (gameManager->GetState() == 1) {
                            if (menu->GetChoice() == 1) {
                                gameManager->SetState(0);
                                board->AddBlockEntity();
                            }
                        }
                        if (gameManager->GetState() == 2) {
                            if (menu->GetChoice() == 1)
                                gameManager->SetState(0);
                            else {
                                if (menu->GetChoice() == 2) {
                                    menu->SetChoice(1);
                                    gameManager->SetState(1);
                                    delete board;
                                    board = new Board();
                                }
                            }
                        }
                        if (gameManager->GetState() == 3) {
                            if (menu->GetChoice() == 1) {
                                gameManager->SetState(1);
                                delete board;
                                board = new Board();
                            }
                        }
                        if (menu->GetChoice() == 2) {
                            window->close();
                            break;
                        }
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window->close();
                    break;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    board->MoveFirstBlock(sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
                    gameManager->SetState(0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                    board->RotateFirstBlock(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    if (board->DownBlock()) {
                        board->AddScore(1);
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    while(board->DownBlock()) {
                        board->AddScore(2);
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    gameManager->SetState(2);
                }
            }
        }

        window->clear();

        if (board->IsGameEnded())
            gameManager->SetState(3);

        if(gameManager->GetState() == 0)
            board->Update(window);
        else
            menu->Draw(window);
        
        window->display();
    }
    if (window->isOpen())
        window->close();
    return 0;
}
