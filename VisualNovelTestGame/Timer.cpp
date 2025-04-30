/*#include "Timer.h"
#include <iomanip>
#include <sstream>

Timer::Timer(float duration) : duration(duration), remainingTime(duration), running(false) {}

void Timer::start() {
    running = true;
}

void Timer::stop() {
    running = false;
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
    std::string ss;
    ss = "Time: " + std::to_string(std::max(0, (int)remainingTime)) + "s";
    return ss;
}

float Timer::getTimeRemaining() {
    return remainingTime;
}

void Timer::operator=(float time) {
    duration = time;
}*/