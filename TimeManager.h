#ifndef TIME_MANAGER_H_
#define TIME_MANAGER_H_

#include <iostream>
#include <chrono>
#include <ctime>

class TimeManager {
    private:
        std::chrono::time_point<std::chrono::system_clock> lastUpdate;
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> firstUpdate;

    public:
        static TimeManager& GetInstance()
        {
            static TimeManager instance;
            return instance;
        }

    private:
        TimeManager(){};
        TimeManager(TimeManager const&);
        void operator=(TimeManager const&);
    public:
        void Start();
        void Update();
        unsigned int GetElapsedTime() const;
        unsigned int GetStartedTime() const;
};

#endif //TIME_MANAGER_H_