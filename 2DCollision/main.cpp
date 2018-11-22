/// <summary>
/// Author : David Whiteford 
/// Time taken : 24hrs
/// Collsiion detection between different shapes. press space to change shape
/// </summary>
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
	//press space to cahnge shape
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
	int playerShape = 0;
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
	poly_npc.verts[0] = c2V(polygon.getPoint(0).x , polygon.getPoint(0).y);
	poly_npc.verts[1] = c2V(polygon.getPoint(1).x, polygon.getPoint(1).y);
	poly_npc.verts[2] = c2V(polygon.getPoint(2).x, polygon.getPoint(2).y);
	//poly_npc.norms[] = c2V(polygon.getPointCount());
	
	//Setup Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
	aabb_player.max = c2V(player.getAnimatedSprite().getGlobalBounds().width / 6, player.getAnimatedSprite().getGlobalBounds().width / 6);


	// Initialize Input
	Input input;
	int isKeyPressedOnce = 0;
	// Collision result

	// Direction of movement of NPC
	sf::Vector2f direction(0.1f, 0.2f);
	
	// Start the game loop
	while (window.isOpen())
	{
		switch (playerShape)
		{
		case 0:
			player.getAnimatedSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			player_circle.setPosition(-100, -100);
			playerCapsuleCircleL.setPosition(-100, -100);
			break;

		case 1:
			player_circle.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			player.getAnimatedSprite().setPosition(-100 , -100);
			playerCapsuleCircleL.setPosition(-100, -100);
			break;

		case 2:
			playerCapsuleCircleL.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			player.getAnimatedSprite().setPosition(-100, -100);
			player_circle.setPosition(-100, -100);
			break;
		}
		//sets the player capsule to the left capsule circle
			playerCapsuleCircleR.setPosition(playerCapsuleCircleL.getPosition().x + 75, playerCapsuleCircleL.getPosition().y);
			playerCapsuleRect.setPosition(playerCapsuleCircleL.getPosition().x, playerCapsuleCircleL.getPosition().y - 50);
		

		// Move The NPC
		sf::Vector2f move_to(npc.getAnimatedSprite().getPosition().x + direction.x, npc.getAnimatedSprite().getPosition().y + direction.y );
		sf::Vector2f move(npc_circle.getPosition().x + direction.x, npc_circle.getPosition().y + direction.y);
		sf::Vector2f capsule_move(capsuleCircleL.getPosition().x + direction.x, capsuleCircleL.getPosition().y + direction.y);
		sf::Vector2f triangle_move(polygon.getPosition().x + direction.x, polygon.getPosition().y + direction.y);

		if (move_to.x < 0)
		{
			direction.x *= -0.1;
			move_to.x = 0 /*+ npc.getAnimatedSprite().getGlobalBounds().width*/;
		}
		else if (move_to.x + npc.getAnimatedSprite().getGlobalBounds().width >= 800)
		{ 
			direction.x *= -0.1;
			move_to.x = 800 - npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.y < 0 )
		{ 
			direction.y *= -0.1;
			move_to.y = 0 /*+ npc.getAnimatedSprite().getGlobalBounds().height*/;
		}
		else if (move_to.y + npc.getAnimatedSprite().getGlobalBounds().height >= 600 
		)
		{
			direction.y *= -0.1;
			move_to.y = 600 - npc.getAnimatedSprite().getGlobalBounds().height;
		}
		//sets new pos to move
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
		//updated set pos for capsule npc
		capsule_npc.a = c2V(capsuleCircleL.getPosition().x,
			capsuleCircleL.getPosition().y);
		capsule_npc.b = c2V(capsuleCircleR.getPosition().x,
			capsuleCircleR.getPosition().y);
		capsule_npc.r = capsuleCircleR.getRadius();

		//updated set pos for circle player
		circle_player.p = c2V(player_circle.getPosition().x,
			player_circle.getPosition().y);
		circle_player.r = player_circle.getRadius();


		//updated set pos for capsule player
		capsule_player.a = c2V(playerCapsuleCircleL.getPosition().x,
			playerCapsuleCircleL.getPosition().y);
		capsule_player.b = c2V(playerCapsuleCircleR.getPosition().x,
			playerCapsuleCircleR.getPosition().y);
		capsule_player.r = playerCapsuleCircleR.getRadius();

		//set pos of polygon updated npc
		poly_npc.count = polygon.getPointCount();
		poly_npc.verts[0] = c2V(polygon.getPoint(0).x, polygon.getPoint(0).y);
		poly_npc.verts[1] = c2V(polygon.getPoint(1).x, polygon.getPoint(1).y);
		poly_npc.verts[2] = c2V(polygon.getPoint(2).x, polygon.getPoint(2).y);
		//poly_npc.norms[] = c2V(polygon.getPointCount());

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{

			//key press to change shape
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				//uses player shape variable to change shape
				if (playerShape < 2)
				{
					playerShape++;
				}
				else
				{
					playerShape = 0;
				}

			}
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();

			}
		}
		//sets up variables for the results
		int result = 0;
		int circletoAABBresult = 0;
		int capsuletoAABBresult = 0;
		int circletocircleresult = 0;
		int circletocapsuleresult = 0;
		int playerCircletoAABBresult = 0;
		int playerCapsuletoAABBresult = 0 ;
		int circletoplayerCapsuleresult = 0;
		int playerCapsuletoCapsule = 0;
		int TriangletoAABBresult = 0;
		int Triangletocircleresult = 0;
		int Triangletocapsuleresult = 0;
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
		TriangletoAABBresult = c2AABBtoPoly(aabb_player, &poly_npc, NULL);
		
		Triangletocircleresult = c2CircletoPoly(circle_player, &poly_npc, NULL);
		Triangletocapsuleresult = c2CapsuletoPoly(capsule_player, &poly_npc, NULL);


		circletocircleresult = c2CircletoCircle(circle_player, circle_npc);
		circletocapsuleresult = c2CircletoCapsule(circle_player , capsule_npc );
		playerCircletoAABBresult = c2CircletoAABB(circle_player, aabb_npc);
		playerCapsuletoAABBresult = c2AABBtoCapsule(aabb_npc, capsule_player); 
		circletoplayerCapsuleresult = c2CircletoCapsule(circle_npc, capsule_player); 
		playerCapsuletoCapsule =   c2CapsuletoCapsule(capsule_player, capsule_npc);

		//outputs message if there is a collision
		cout << ((result != 0) ? ("AABB to AABB Collision") : "") << endl;
		cout << ((circletoAABBresult != 0) ? ("Circle to AABB Collision") : "") << endl;
		cout << ((capsuletoAABBresult != 0) ? ("Capsule to AABB Collision") : "") << endl;
		cout << ((TriangletoAABBresult != 0) ? ("Poly Collision") : "") << endl;
		cout << ((circletocircleresult != 0) ? ("Circle to Circle Collision") : "") << endl;
		cout << ((circletocapsuleresult != 0) ? ("Circle to Capsule Collision") : "") << endl;
		cout << ((playerCircletoAABBresult != 0) ? ("Circle to Capsule Collision") : "") << endl;
		cout << ((playerCapsuletoCapsule != 0) ? ("Circle to Capsule Collision") : "") << endl;
		cout << ((circletoplayerCapsuleresult != 0) ? ("Circle to Capsule Collision") : "") << endl;
		cout << ((playerCapsuletoAABBresult != 0) ? ("Circle to Capsule Collision") : "") << endl;
		cout << ((Triangletocircleresult != 0) ? ("Circle to Capsule Collision") : "") << endl;
		cout << ((Triangletocapsuleresult != 0) ? ("Circle to Capsule Collision") : "") << endl;

		//checks if any of the collisions happen and then chnges color of player shape to red
		if (result || circletoAABBresult || capsuletoAABBresult || circletocircleresult || circletocapsuleresult || playerCircletoAABBresult 
			|| playerCapsuletoAABBresult || circletoplayerCapsuleresult || playerCapsuletoCapsule || TriangletoAABBresult || Triangletocapsuleresult || Triangletocircleresult)
		{
			player.getAnimatedSprite().setColor(sf::Color::Red);
			player_circle.setFillColor(sf::Color::Red);
			playerCapsuleCircleL.setFillColor(sf::Color::Red);
			playerCapsuleCircleR.setFillColor(sf::Color::Red);
			playerCapsuleRect.setFillColor(sf::Color::Red);
		}
		else 
		{
			player.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
			player_circle.setFillColor(sf::Color::Green);
			playerCapsuleCircleL.setFillColor(sf::Color::Green);
			playerCapsuleCircleR.setFillColor(sf::Color::Green);
			playerCapsuleRect.setFillColor(sf::Color::Green);
		}

		// Clear screen
		window.clear();

	

	
		
		// Draw the NPC's capsule circle polygon and square
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
		window.draw(playerCapsuleCircleL);
		window.draw(playerCapsuleCircleR);
		window.draw(playerCapsuleRect);
		window.draw(player.getAnimatedSprite());
		window.draw(player_circle);

		
		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};