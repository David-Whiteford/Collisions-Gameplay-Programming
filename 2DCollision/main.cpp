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
	AnimatedSprite m_animated_sprite;
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

	sf::ConvexShape  polygon;
	polygon.setFillColor(sf::Color::Green);
	polygon.setPosition(150, 150);
	polygon.setPointCount(3);
	polygon.setPoint(0, sf::Vector2f(0, 0));
	polygon.setPoint(1, sf::Vector2f(150, 10));
	polygon.setPoint(2, sf::Vector2f(120, 90));


	sf::CircleShape player_circle;
	player_circle.setFillColor(sf::Color::Green);
	player_circle.setRadius(50);
	player_circle.setOrigin(50, 50);

	sf::CircleShape capsuleCircleR;
	capsuleCircleR.setFillColor(sf::Color::Green);
	capsuleCircleR.setRadius(50);
	capsuleCircleR.setPosition(200 , 200);
	capsuleCircleR.setOrigin(50, 50);


	sf::CircleShape capsuleCircleL;
	capsuleCircleL.setFillColor(sf::Color::Green);
	capsuleCircleL.setRadius(50);
	capsuleCircleL.setPosition(250, 50);
	capsuleCircleL.setOrigin(50, 50);

	sf::RectangleShape capsuleRect;
	capsuleRect.setFillColor(sf::Color::Green);
	capsuleRect.setSize(sf::Vector2f(75,100));
	capsuleRect.setPosition(200, 50);
	
	sf::CircleShape playerCapsuleCircleR;
	playerCapsuleCircleR.setFillColor(sf::Color::Green);
	playerCapsuleCircleR.setRadius(50);
	playerCapsuleCircleR.setPosition(200, 200);
	playerCapsuleCircleR.setOrigin(50, 50);


	sf::CircleShape playerCapsuleCircleL;
	playerCapsuleCircleL.setFillColor(sf::Color::Green);
	playerCapsuleCircleL.setRadius(50);
	playerCapsuleCircleL.setPosition(250, 50);
	playerCapsuleCircleL.setOrigin(50, 50);

	sf::RectangleShape playerCapsuleRect;
	playerCapsuleRect.setFillColor(sf::Color::Green);
	playerCapsuleRect.setSize(sf::Vector2f(75, 100));
	playerCapsuleRect.setPosition(200, 25);


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
	player_animated_sprite.setPosition(-100, -100);
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
	circle_npc.p = c2V(npc_circle.getPosition().x,
		npc_circle.getPosition().y);
	circle_npc.r = npc_circle.getRadius();

	c2Circle circle_player;
	circle_player.p = c2V(player_circle.getPosition().x,
		player_circle.getPosition().y);
	circle_player.r = player_circle.getRadius();
	/// set up capsule
	///
	//capsules
	c2Capsule capsule_npc;
	capsule_npc.a = c2V(capsuleCircleL.getPosition().x,
		capsuleCircleL.getPosition().y);
	capsule_npc.b = c2V(capsuleCircleR.getPosition().x,
		capsuleCircleR.getPosition().y);
	capsule_npc.r = capsuleCircleR.getRadius();

	c2Capsule capsule_player;
	capsule_player.a = c2V(playerCapsuleCircleL.getPosition().x,
		playerCapsuleCircleL.getPosition().y);
	capsule_player.b = c2V(playerCapsuleCircleR.getPosition().x,
		playerCapsuleCircleR.getPosition().y);
	capsule_player.r = playerCapsuleCircleR.getRadius();


	
	c2Poly poly_npc;
	poly_npc.count = polygon.getPointCount();
	//poly_npc.verts[] = c2V(polygon.getPointCount());
	//poly_npc.norms[] = c2V(polygon.getPointCount());
	
	//Setup Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
	aabb_player.max = c2V(player.getAnimatedSprite().getGlobalBounds().width / 6, player.getAnimatedSprite().getGlobalBounds().width / 6);


	// Initialize Input
	Input input;
	int isKeyPressedOnce = 0;
	// Collision result
	int result = 0;
	int circletoAABBresult = 0;
	int capsuletoAABBresult = 0;
	int circletocircleresult = 0;
	int circletocapsuleresult = 0;
	// Direction of movement of NPC
	sf::Vector2f direction(0.1f, 0.2f);
	
	// Start the game loop
	while (window.isOpen())
	{
		
		
			player.getAnimatedSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			player_circle.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));


			playerCapsuleCircleL.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			playerCapsuleCircleR.setPosition(playerCapsuleCircleL.getPosition().x + 75, playerCapsuleCircleL.getPosition().y);
			playerCapsuleRect.setPosition(playerCapsuleCircleL.getPosition().x, playerCapsuleCircleL.getPosition().y - 50);
		

		// Move The NPC
		sf::Vector2f move_to(npc.getAnimatedSprite().getPosition().x + direction.x, npc.getAnimatedSprite().getPosition().y + direction.y );
		sf::Vector2f move(npc_circle.getPosition().x + direction.x, npc_circle.getPosition().y + direction.y);
		sf::Vector2f capsule_move(capsuleCircleL.getPosition().x + direction.x, capsuleCircleL.getPosition().y + direction.y);
		sf::Vector2f triangle_move(polygon.getPosition().x + direction.x, polygon.getPosition().y + direction.y);

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

		capsuleCircleL.setPosition(capsule_move);
		capsuleCircleR.setPosition(capsuleCircleL.getPosition().x + 75 , capsuleCircleL.getPosition().y );
		capsuleRect.setPosition(capsuleCircleL.getPosition().x , capsuleCircleL.getPosition().y - 50);
		
		
	


		npc_circle.setPosition(move);
		npc.getAnimatedSprite().setPosition(move_to);
		polygon.setPosition(triangle_move);
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

		capsule_npc.a = c2V(capsuleCircleL.getPosition().x,
			capsuleCircleL.getPosition().y);
		capsule_npc.b = c2V(capsuleCircleR.getPosition().x,
			capsuleCircleR.getPosition().y);
		capsule_npc.r = capsuleCircleR.getRadius();


		circle_player.p = c2V(player_circle.getPosition().x,
			player_circle.getPosition().y);
		circle_player.r = player_circle.getRadius();



		capsule_player.a = c2V(playerCapsuleCircleL.getPosition().x,
			playerCapsuleCircleL.getPosition().y);
		capsule_player.b = c2V(playerCapsuleCircleR.getPosition().x,
			playerCapsuleCircleR.getPosition().y);
		capsule_player.r = playerCapsuleCircleR.getRadius();


		poly_npc.count = polygon.getPointCount();
		//poly_npc.verts[3] = polygon.getPointCount();
		//poly_npc.norms[3] = polygon.getPointCount();

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				
					
				

				
			}
		}

		// Handle input to Player
		player.handleInput(input);
		npc.handleInput(input);
		// Update the Player
		player.update();

		// Update the Player
		npc.update();

		// Check for collisions
		result = c2AABBtoAABB(aabb_player, aabb_npc);
		circletoAABBresult = c2CircletoAABB(circle_npc, aabb_player);
		capsuletoAABBresult = c2AABBtoCapsule(aabb_player, capsule_npc);
		/*TriangletoAABBresult = c2AABBtoPoly(aabb_player, polygon, );*/
		circletocircleresult = c2CircletoCircle(circle_player, circle_npc);
		circletocapsuleresult = c2CircletoCapsule(circle_player , capsule_npc );



		cout << ((result != 0) ? ("AABB to AABB Collision") : "") << endl;
		cout << ((circletoAABBresult != 0) ? ("Circle to AABB Collision") : "") << endl;
		cout << ((capsuletoAABBresult != 0) ? ("Capsule to AABB Collision") : "") << endl;
		/*cout << ((TriangletoAABBresult != 0) ? ("Collision") : "") << endl;*/
		cout << ((circletocircleresult != 0) ? ("Circle to Circle Collision") : "") << endl;
		cout << ((circletocapsuleresult != 0) ? ("Circle to Capsule Collision") : "") << endl;


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

		
	
			window.draw(player.getAnimatedSprite());
		
	
		
		
		// Draw the Players Current Animated Sprite
	
		
		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSprite());
		window.draw(npc_circle);
		window.draw(capsuleCircleL);
		window.draw(capsuleCircleR);
		window.draw(capsuleRect);
		window.draw(polygon);

		/// <summary>
		/// Drawing for all the player capsules , the player square and the player circle
		/// </summary>
		/// <returns></returns>
		/*window.draw(playerCapsuleCircleL);
		window.draw(playerCapsuleCircleR);
		window.draw(playerCapsuleRect);*/
		
			window.draw(player_circle);

		
		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};