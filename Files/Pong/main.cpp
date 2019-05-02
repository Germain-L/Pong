#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>


int main()
{
	//all variables are initialised
	int y, p1 = 0, p2 = 0, ballX = 0, ballY = 0, offset;
	bool started = false;

	sf::Image icon;
	icon.loadFromFile("resources\\icon.png");


	//initialises the windoz
	sf::RenderWindow window(sf::VideoMode(800, 500), "Pong", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::Texture texture;
	texture.loadFromFile("resources\\background.png");

	//creates a shape rectangle for player1, player2 and midline
	sf::RectangleShape player1, player2, midLine, background;

	//sets characteristics for player1
	player1.setSize(sf::Vector2f(20, 80));
	player1.setOrigin(10, 40);
	player1.setPosition(10, 40);

	//sets characteristics for player1
	player2.setSize(sf::Vector2f(20, 80));
	player2.setOrigin(10, 40);
	player2.setPosition(790, 40);

	//sets characteristics for player2
	midLine.setSize(sf::Vector2f(3, window.getSize().y));
	midLine.setFillColor(sf::Color::White);
	midLine.setPosition(window.getSize().x / 2, 0);

	//fix setTexture
	background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	background.setTexture(&texture);

	//sets fonts for texts
	sf::Font font;
	font.loadFromFile("resources\\pongfont.ttf");

	sf::Text p1score, p2score, win;
	p1score.setFont(font);
	p1score.setCharacterSize(40);
	p1score.setString(std::to_string(0));
	p1score.setPosition((window.getSize().x) / 2 - 20, 0);

	p2score.setFont(font);
	p2score.setCharacterSize(40);
	p2score.setString(std::to_string(0));
	p2score.setPosition((window.getSize().x) / 2 + 5, 0);

	win.setFont(font);
	win.setCharacterSize(50);
	win.setPosition(220, 300);
	win.setFillColor(sf::Color::White);

	//creates a circle for the ball.
	sf::CircleShape ball(10.0f);
	ball.setOrigin(5, 5);
	ball.setPosition(500, 300);

	//creates a buffer to store sounds
	sf::SoundBuffer bounce, loose;
	bounce.loadFromFile("resources\\bounce.wav");
	loose.loadFromFile("resources\\loose.wav");

	//creates sound variable
	sf::Sound sound;

	//create music variable and sets it
	sf::Music music;
	music.openFromFile("resources\\music.wav");
	music.setLoop(true);
	music.setLoopPoints({ sf::seconds(2.0f),sf::seconds(214.0f) });
	music.play();
	music.setVolume(25);



	//starts the game
	while (window.isOpen())
	{
		//events are handled
		sf::Event evnt;

		//closes the window if needed
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window.close();
		}

		//checks for bounces at the top and bottom
		if (ball.getPosition().y >= (window.getSize().y) - 15 || ball.getPosition().y <= 5)
		{
			//play bounce sound
			sound.setBuffer(bounce);
			sound.play();

			ballY = ballY * -1;
		}

		//if s is pressed move p1 down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			y = player1.getPosition().y;
			if (y < (window.getSize().y - 40))
			{
				player1.move(0, 5);
			}
		}

		//if W is pressed move p1 up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			y = player1.getPosition().y;
			if (y > 40)
			{
				player1.move(0, -5);
			}
		}

		//if downKey is pressed move p2 down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			y = player2.getPosition().y;
			if (y < (window.getSize().y - 40))
			{
				player2.move(0, 5);
			}
		}

		//if upKey is pressed move p2 up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			y = player2.getPosition().y;
			if (y > 40)
			{
				player2.move(0, -5);
			}
		}

		//starts the game if spaceKey is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			//makes sure it only starts the game once
			if (started == false)
			{
				started = true;

				//initializes the movement of the ball
				ballX = -5;
				ballY = 0;
			}
		}

		//checks if ball is in reach of p1
		if (ball.getPosition().x == (player1.getPosition().x) + 10)
		{
			//checks if y coordinates of ball are in p1
			if ((ball.getPosition().y < player1.getPosition().y + 40) && (ball.getPosition().y > player1.getPosition().y - 40))
			{
				//play bounce sound
				sound.setBuffer(bounce);
				sound.play();

				//reverses x speed
				ballX *= -1;

				//creates offset (angle for the ball)
				offset = ball.getPosition().y - player1.getPosition().y;

				//moves the ball in that diretion (offset)
				ballY = (offset / 1.5) / 5;
			}
			else //if ball passes p1, p2 gains a point
			{
				//play loose sound
				sound.setBuffer(loose);
				sound.play();

				//increment and displays p2 score
				p2 += 1;
				p2score.setString(std::to_string(p2));

				//resets ball
				ball.setPosition(500, 300);
				ballX = -5;
				ballY = 0;
			}
		}

		//checks if ball is in reach of p1
		if (ball.getPosition().x == (player2.getPosition().x) - 20)
		{
			//checks if y coordinates of ball are in p2
			if ((ball.getPosition().y < player2.getPosition().y + 40) && (ball.getPosition().y > player2.getPosition().y - 40))
			{
				//play bounce sound
				sound.setBuffer(bounce);
				sound.play();

				//reverses x speed
				ballX *= -1;

				//creates offset (angle for the ball)
				offset = ball.getPosition().y - player2.getPosition().y;

				//moves the ball in that diretion (offset)
				ballY = (offset / 1.5) / 5;
			}
			else // if ball passes p1, p2 gains a point
			{
				//play loose sound
				sound.setBuffer(loose);
				sound.play();

				//increment and displays p1 score
				p1 += 1;
				p1score.setString(std::to_string(p1));

				//resets ball
				ball.setPosition(300, 300);
				ballX = 5;
				ballY = 0;
			}
		}

		//checks if any score is higher or equal to 6
		if (p1 >= 6 && p2 < 6)
		{
			//stops game and display the winner
			win.setString("Player 1 wins!");

			//loops indefinitely here to show player1 won
			while (true)
			{
				//closes the window if needed
				while (window.pollEvent(evnt))
				{
					if (evnt.type == sf::Event::Closed)
						window.close();
				}

				window.clear(sf::Color::Black);
				window.draw(win);
				window.display();
			}
		}

		if (p2 >= 6 && p1 < 6)
		{
			win.setString("Player 2 wins!");
			//loops indefinitely here to show player1 won
			while (true)
			{
				//closes the window if needed
				while (window.pollEvent(evnt))
				{
					if (evnt.type == sf::Event::Closed)
						window.close();
				}

				window.clear(sf::Color::Black);
				window.draw(win);
				window.display();
			}
		}

		//make ball move every frame
		ball.move(ballX, ballY);

		//clears the frame from aerything and set it to black
		window.clear(sf::Color::Black);

		//draw everything needed
		window.draw(background);
		window.draw(player1);
		window.draw(player2);
		window.draw(ball);
		window.draw(midLine);
		window.draw(p1score);
		window.draw(p2score);
		window.draw(win);

		//don't know what that exactly does
		window.display();
	}
}