#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

class GameManager {
    public:
        GameManager(GameManager const&) = delete;
        void operator=(GameManager const&) = delete;
        static GameManager *GetInstance();
        int GetState();
        void SetState(int);

    private:
        GameManager();
        static GameManager *_gameManager;
        int _state;
};

#endif // GAME_MANAGER_H_