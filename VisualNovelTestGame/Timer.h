#pragma once
#include <string>
#include <algorithm>
#include <sstream>

template<typename T>
class Timer {
private:
    T duration;
    T remainingTime;
    bool running;

public:
    Timer(T duration)
        : duration(duration), remainingTime(duration), running(false) {
    }

    void start() {
        running = true;
    }

    void stop() {
        running = false;
    }

    void update(T deltaTime) {
        if (running && remainingTime > 0) {
            remainingTime -= deltaTime;
            if (remainingTime <= 0) {
                running = false;
                remainingTime = 0;
            }
        }
    }

    bool isFinished() const {
        return remainingTime <= 0;
    }

    void reset() {
        remainingTime = duration;
        running = false;
    }

    std::string getTimeString() const {
        std::ostringstream oss;
        oss.precision(2);
        oss << std::fixed << "Time: " << std::max<T>(static_cast<T>(0), remainingTime) << "s";
        return oss.str();
    }

    T getTimeRemaining() const {
        return remainingTime;
    }

    void operator=(T time) {
        duration = time;
        remainingTime = time;
    }
};
