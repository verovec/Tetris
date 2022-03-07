#include "TimeManager.h"

void TimeManager::Start() {
    start = std::chrono::system_clock::now();
}

void TimeManager::Update() {
    firstUpdate = lastUpdate;
    lastUpdate = std::chrono::system_clock::now();
}

unsigned int TimeManager::GetElapsedTime() const {
    unsigned int time_elapse_between_update = std::chrono::duration_cast<std::chrono::milliseconds >
            (lastUpdate-firstUpdate).count();
    return time_elapse_between_update;
}

unsigned int TimeManager::GetStartedTime() const {
    unsigned int time_elapse_start = std::chrono::duration_cast<std::chrono::milliseconds >
            (lastUpdate-start).count();
    return time_elapse_start;
}
