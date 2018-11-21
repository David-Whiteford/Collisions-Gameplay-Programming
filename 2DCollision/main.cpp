#include <iostream>
#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include <tinyc2.h>
#include <AnimatedSprite.h>
#include <GameObject.h>
#include <Player.h>
#include <NPC.h>
#include <Input.h>
#include <Debug.h>

using namespace std;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// Load a NPC's sprites to display
	sf::Texture npc_texture;
	if (!npc_texture.loadFromFile("assets\\grid.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Load a mouse texture to display
	sf::Texture player_texture;
	if (!player_texture.loadFromFile("assets\\player.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	//sf::Texture circle_texture;
	//if (!circle_texture.loadFromFile("assets\\circle.png")) {
	//	DEBUG_MSG("Failed to load file");
	//	return EXIT_FAILURE;
	//}
	//AnimatedSprite npc_circle(circle_texture);

	sf::CircleShape capsuleCircleR;
	capsuleCircleR.setFillColor(sf::Color::Green);
	capsuleCircleR.setRadius(50);
	capsuleCircleR.setPosition(200 , 50);
	capsuleCircleR.setOrigin(50, 50);


	sf::CircleShape capsuleCircleL;
	capsuleCircleL.setFillColor(sf::Color::Green);
	capsuleCircleL.setRadius(50);
	capsuleCircleL.setPosition(250, 50);
	capsuleCircleL.setOrigin(50, 50);

	sf::RectangleShape capsuleRect;
	capsuleRect.setFillColor(sf::Color::Green);
	capsuleRect.setSize(sf::Vector2f(50,50));
	capsuleRect.setPosition(200, 50);
	capsuleRect.setOrigin(50, 50);

	
	sf::CircleShape npc_circle;
	npc_circle.setFillColor(sf::Color::Red);
	npc_circle.setRadius(50);
	npc_circle.setPosition(100, 0);
	npc_circle.setOrigin(50, 50);
	
	// Setup NPC's Default Animated Sprite
	AnimatedSprite npc_animated_sprite(npc_texture);
	npc_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	// Setup Players Default Animated Sprite
	AnimatedSprite player_animated_sprite(player_texture);
	player_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	
		// Setup the NPC
		GameObject &npc = NPC(npc_animated_sprite);
	
		
		
	
	
	
	// Setup the Player
	GameObject &player = Player(player_animated_sprite);
	//Setup NPC AABB
	c2AABB aabb_npc;

	aabb_npc.min = c2V(npc.getAnimatedSprite().getPosition().x, npc.getAnimatedSprite().getPosition().y);
	aabb_npc.max = c2V(
		npc.getAnimatedSprite().getPosition().x +
		npc.getAnimatedSprite().getGlobalBounds().width,
		npc.getAnimatedSprite().getPosition().y +
		npc.getAnimatedSprite().getGlobalBounds().height);

	c2Circle circle_npc;

	/*circle_npc.x = npc_circle.getGlobalBounds().x;*/
	circle_npc.p = c2V(npc_circle.getPosition().x,
		npc_circle.getPosition().y);
	circle_npc.r = npc_circle.getRadius();

	c2Capsule capsule_npc;
	capsule_npc.a = c2V(capsuleCircleL.getPosition().x,
		capsuleCircleL.getPosition().y);
	capsule_npc.b = c2V(capsuleCircleR.getPosition().x,
		capsuleCircleR.getPosition().y);

	
	//Setup Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
	aabb_player.max = c2V(player.getAnimatedSprite().getGlobalBounds().width / 6, player.getAnimatedSprite().getGlobalBounds().width / 6);


	// Initialize Input
	Input input;

	// Collision result
	int result = 0;
	int circletoAABBresult = 0;

	// Direction of movement of NPC
	sf::Vector2f direction(0.1f, 0.2f);
	
	// Start the game loop
	while (window.isOpen())
	{
		// Move Sprite Follow Mouse
		player.getAnimatedSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		
		// Move The NPC
		sf::Vector2f move_to(npc.getAnimatedSprite().getPosition().x + direction.x, npc.getAnimatedSprite().getPosition().y + direction.y );
		sf::Vector2f move(npc_circle.getPosition().x + direction.x, npc_circle.getPosition().y + direction.y);
		/*sf::Vector2f capsule_move(npc_capsule.getPosition().x + direction.x, npc_capsule.getPosition().y + direction.y);*/

		if (move_to.x < 0)
		{
			direction.x *= -1;
			move_to.x = 0 + npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.x + npc.getAnimatedSprite().getGlobalBounds().width >= 800)
		{ 
			direction.x *= -1;
			move_to.x = 800 - npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.y < 0 )
		{ 
			direction.y *= -1;
			move_to.y = 0 + npc.getAnimatedSprite().getGlobalBounds().height;
		}
		else if (move_to.y + npc.getAnimatedSprite().getGlobalBounds().height >= 600 
		)
		{
			direction.y *= -1;
			move_to.y = 600 - npc.getAnimatedSprite().getGlobalBounds().height;
		}




		npc_circle.setPosition(move);
		npc.getAnimatedSprite().setPosition(move_to);

		// Update NPC AABB set x and y
		aabb_npc.min = c2V
		(
			npc.getAnimatedSprite().getPosition().x, 
			npc.getAnimatedSprite().getPosition().y
		);

		aabb_npc.max = c2V
		(
			npc.getAnimatedSprite().getPosition().x +
			npc.getAnimatedSprite().getGlobalBounds().width,
			npc.getAnimatedSprite().getPosition().y +
			npc.getAnimatedSprite().getGlobalBounds().height
		);

		// Update Player AABB
		aabb_player.min = c2V
		(
			player.getAnimatedSprite().getPosition().x, 
			player.getAnimatedSprite().getPosition().y
		);
		aabb_player.max = c2V
		(
			player.getAnimatedSprite().getPosition().x +
			player.getAnimatedSprite().getGlobalBounds().width, 
			player.getAnimatedSprite().getPosition().y + 
			player.getAnimatedSprite().getGlobalBounds().height
		);
		//updated npc circle
		circle_npc.p = c2V(npc_circle.getPosition().x ,
			npc_circle.getPosition().y);
		circle_npc.r = npc_circle.getRadius();


		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					input.setCurrent(Input::Action::LEFT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					input.setCurrent(Input::Action::RIGHT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					input.setCurrent(Input::Action::UP);
				}
				break;
			default:
				input.setCurrent(Input::Action::IDLE);
				break;
			}
		}

		// Handle input to Player
		player.handleInput(input);

		// Update the Player
		player.update();

		// Update the Player
		npc.update();

		// Check for collisions
		result = c2AABBtoAABB(aabb_player, aabb_npc);
		circletoAABBresult = c2CircletoAABB(circle_npc, aabb_player);
		cout << ((result != 0) ? ("Collision") : "") << endl;
		cout << ((circletoAABBresult != 0) ? ("Collision") : "") << endl;
		
		
		if (result || circletoAABBresult)
		{
			player.getAnimatedSprite().setColor(sf::Color::Magenta);
		}
		else 
		{
			player.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
		}

		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		window.draw(player.getAnimatedSprite());

		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSprite());
		window.draw(npc_circle);
		window.draw(capsuleCircleL);
		window.draw(capsuleCircleR);
		window.draw(capsuleRect);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};