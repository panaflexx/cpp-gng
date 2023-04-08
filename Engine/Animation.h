#pragma once
#include <vector>

class AnimationFrame;

class Animation final
{
public:
	explicit Animation(const std::vector<AnimationFrame*>& frames);
	Animation& operator=(const Animation& rhs) = delete;
	Animation& operator=(Animation&& rhs) = delete;
	Animation(const Animation& rhs) = delete;
	Animation(Animation&& rhs) = delete;
	~Animation();

	AnimationFrame* GetFrame(int frameNr) const;
	std::vector<AnimationFrame*> GetFrames() const;
	float GetTotalDuration() const;

private:
	std::vector<AnimationFrame*> m_Frames;
	float m_TotalDuration{ 0 };
};