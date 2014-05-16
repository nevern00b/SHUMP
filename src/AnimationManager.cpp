#include "AnimationManager.h"

#include "Globals.h"
#include "UIManager.h"


AnimationManager::AnimationManager()
{

}

AnimationManager::~AnimationManager()
{

}

void AnimationManager::update()
{
	auto it = m_animations.begin();
	while (it != m_animations.end())
	{
		Animation* animation = *it;
		if (!animation->update())
		{
			m_animations.erase(it++);
			delete animation;
		}
		else
		{
			++it;
		}
	}
}

void AnimationManager::addAnimation(Animation* animation)
{
	
}

void AnimationManager::removeTarget(void* target)
{
	// Remove all animations that have this target
	auto it = m_animations.begin();
	while (it != m_animations.end())
	{
		Animation* animation = *it;
		if (animation->m_target == target)
		{
			m_animations.erase(it++);
			delete animation;
		}
		else
		{
			++it;
		}
	}

}

Animation::Animation(void* target, float& property, float startValue, float endValue, float duration, float delay, bool repeat, std::function<void()> callback) :
	m_target(target),
	m_property(&property),
	m_startValue(startValue),
	m_endValue(endValue),
	m_time(0.0f),
	m_duration(duration),
	m_delay(delay),
	m_repeat(repeat),
	m_callback(callback)
{
	Globals::m_animationManager->m_animations.push_back(this);
	update(); // Update right away

}

Animation::Animation(void* target, std::function<void()> callback, float duration, float delay, bool repeat) :
	m_target(target),
	m_callback(callback),
	m_time(0.0f),
	m_duration(duration),
	m_delay(delay),
	m_repeat(repeat),
	m_property(0)
{
	Globals::m_animationManager->m_animations.push_back(this);
}

Animation::~Animation()
{
	
}

bool Animation::update()
{
	// Don't animate if it hasn't reached the delay
	if (m_delay > 0.0f)
	{
		if (m_time < m_delay)
		{
			return true;
		}
		else
		{
			m_delay = 0.0f;
			m_time = 0.0f;
		}
	}

	if (m_time > m_duration)
	{
		if (m_repeat) // Repeat
		{
			m_time = 0.0f;
			sendCallback();
		}
		else // Destroy
		{
			sendCallback();
			return false;
		}
	}

	if (m_property)
	{
		float alpha = m_time / m_duration;
		float value = m_startValue * (1.0f - alpha) + m_endValue * alpha;
		*m_property = value;
	}

	// Increment time
	m_time += Globals::m_uiManager->m_frameTime;
	
	return true;
}

void Animation::sendCallback()
{
	if (m_callback != nullptr)
	{
		m_callback();
	}
}