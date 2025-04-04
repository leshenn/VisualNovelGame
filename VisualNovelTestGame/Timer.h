#ifndef Timer_H
#define Timer_H

#include <SFML/Graphics.hpp>
#include <string>

class Timer {
public:
	Timer(float duration);
	void start();
	void update(float deltaTime);
	bool isFinished() const;
	void reset();
	std::string getTimeString() const;

private:
	float duration;
	float remainingTime;
	bool running;

};
#endif