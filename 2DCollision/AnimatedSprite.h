#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Clock.hpp>
#include <vector>
#include <Debug.h>

using namespace std;
using namespace sf;

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite();
	AnimatedSprite(const Texture&);
	AnimatedSprite(const Texture&, const IntRect&);
	~AnimatedSprite();

	const Clock& getClock();
	const Time& getTime();
	const vector<IntRect>& getFrames();
	const IntRect& getFrame(int);
	void addFrame(IntRect&);
	const int getCurrentFrame();
	void setCurrentFrame();
	void update();
	void setFrameRow(int t_frameRow);
	
private:
	Clock m_clock;
	Time m_time;
	vector<IntRect> m_frames;
	unsigned int m_current_frame;
	
	int m_currentFrameCol;
	int m_currentFrameRow;
	IntRect m_currentFrame;
};

#endif // !ANIMATED_SPRITE_H
