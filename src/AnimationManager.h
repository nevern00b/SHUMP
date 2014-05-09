#pragma once

#include <functional>
#include <list>

struct Animation;

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	void update();
	void addAnimation(Animation* animation);
	void removeAnimation(Animation* animation);
	void removeTarget(void* target);

	std::list<Animation*> m_animations;

};

struct Animation
{
	Animation(void* target, float& property, float startValue, float endValue, float duration, float delay, bool repeat, std::function<void()> callback);
	Animation(void* target, std::function<void()> callback, float duration, float delay, bool repeat);

	~Animation();
	bool update();
	void sendCallback();

	void* m_target;
	float* m_property;
	float m_startValue;
	float m_endValue;
	float m_time;
	float m_duration;
	float m_delay;
	bool m_repeat;
	std::function<void()> m_callback;
};