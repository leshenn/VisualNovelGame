#include "Timer.h"
#include <iomanip>
#include <sstream>

Timer::Timer(float duration) : duration(duration), remainingTime(duration), running(false) {}

void Timer::start() {
    running = true;
}

void Timer::update(float deltaTime) {
    if (running && remainingTime > 0) {
        remainingTime -= deltaTime;
        if (remainingTime <= 0) {
            running = false;
            remainingTime = 0;
        }
    }
}

bool Timer::isFinished() const {
    return remainingTime <= 0;
}

void Timer::reset() {
    remainingTime = duration;
    running = false;
}

std::string Timer::getTimeString() const {
    int minutes = static_cast<int>(remainingTime) / 60;
    int seconds = static_cast<int>(remainingTime) % 60;
    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;

    return ss.str();
}