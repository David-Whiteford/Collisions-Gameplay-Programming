#include <AnimatedSprite.h>

AnimatedSprite::AnimatedSprite() 
{
	m_current_frame = 0;
	m_currentFrameCol = 0;
	m_currentFrameRow = 0;
	setCurrentFrame();
}

AnimatedSprite::AnimatedSprite(const sf::Texture& t) : Sprite(t), m_current_frame(0), m_time(seconds(0.5f)) {}

AnimatedSprite::AnimatedSprite(const sf::Texture& t, const sf::IntRect& rect) : Sprite(t), m_current_frame(0), m_time(seconds(0.5f)) {
	m_frames.push_back(rect);
}

AnimatedSprite::~AnimatedSprite() {}

const sf::Clock& AnimatedSprite::getClock() {
	return m_clock;
}

const sf::Time& AnimatedSprite::getTime() {
	return m_time;
}

const vector<IntRect>& AnimatedSprite::getFrames() {
	return m_frames;
}

const IntRect& AnimatedSprite::getFrame(int n) {
	return m_frames[n];
}

void AnimatedSprite::addFrame(IntRect& frame) 
{
	m_frames.push_back(frame);
}

const int AnimatedSprite::getCurrentFrame() 
{
	return m_current_frame;
}

void AnimatedSprite::update()
{
	if (m_clock.getElapsedTime() > m_time)
	{
			if (m_currentFrameCol < 5)
			{
				m_currentFrameCol++;
			}
			else
			{
				m_currentFrameCol = 0;
			}
			setCurrentFrame();
			m_clock.restart();
	}

}
void AnimatedSprite::setFrameRow(int t_frameRow)
{
		m_currentFrameRow = t_frameRow;
}
void AnimatedSprite::setCurrentFrame()
{
	m_currentFrame = IntRect(3 + m_currentFrameCol * 85, 3 + m_currentFrameRow * 85, 85, 85);
}

