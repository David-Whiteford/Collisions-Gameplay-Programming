#include <iostream>
#include <Player.h>
#include <Idle.h>
#include <Debug.h>
#include <SFML/Graphics.hpp>

Player::Player() : GameObject()
{
	m_player_fsm.setCurrent(new Idle());
	m_player_fsm.setPrevious(new Idle());
}

Player::Player(const AnimatedSprite& s) : GameObject(s)
{
	m_player_fsm.setCurrent(new Idle());
	m_player_fsm.setPrevious(new Idle());
}

Player::~Player()
{
}

AnimatedSprite& Player::getAnimatedSprite()
{
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	return m_animated_sprite;
}

void Player::handleInput(Input in)
{

	DEBUG_MSG("Handle Input");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_player_fsm.jumping();
		m_animated_sprite.setFrameRow(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_player_fsm.jumping();
		m_animated_sprite.setFrameRow(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		m_player_fsm.jumping();
		m_animated_sprite.setFrameRow(2);
	}
}

void Player::update()
{
	//std::cout << "Handle Update" << std::endl;
	m_animated_sprite.update();
}