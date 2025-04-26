#ifndef Timer_H
#define Timer_H

#include <SFML/Graphics.hpp>
#include <string>

class Timer {
public:
	Timer(float duration);
	void start();
	void stop();
	void update(float deltaTime);
	bool isFinished() const;
	void reset();
	std::string getTimeString() const;
	float getTimeRemaining();
	void setDuration(float time);
	void operator =(float time);

private:
	float duration;
	float remainingTime;
	bool running;

};
#endif