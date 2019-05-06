#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <iostream>



int game(sf::RenderWindow& window)
{
	//all variables are initialised
	int y, p1 = 0, p2 = 0, ballX = 0, ballY = 0, offset, factorSpeed = 2;
	bool started = false, quit = false;;

	sf::Texture texture;
	texture.loadFromFile("resources\\background.png");

	//creates a shape rectangle for player1, player2
	sf::RectangleShape player1, player2, background, dash;

	dash.setFillColor(sf::Color::White);
	dash.setSize(sf::Vector2f(15, 5));
	dash.setPosition(window.getSize().x / 2, 90);
	dash.setOrigin(15, 0);

	//sets characteristics for player1
	player1.setSize(sf::Vector2f(20, 160));
	player1.setOrigin(10, 80);
	player1.setPosition(10, window.getSize().y / 2);

	//sets characteristics for player1
	player2.setSize(sf::Vector2f(20, 160));
	player2.setOrigin(10, 80);
	player2.setPosition(window.getSize().x -10 , window.getSize().y / 2);

	//fix setTexture
	background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	background.setTexture(&texture);

	//sets fonts for texts
	sf::Font font;
	font.loadFromFile("resources\\pongfont.ttf");

	sf::Text p1score, p2score, win;
	p1score.setFont(font);
	p1score.setCharacterSize(60);
	p1score.setString(std::to_string(0));
	p1score.setPosition((window.getSize().x) / 2 - 45, 50);
	p1score.setFillColor(sf::Color::White);

	p2score.setFont(font);
	p2score.setCharacterSize(60);
	p2score.setString(std::to_string(0));
	p2score.setPosition((window.getSize().x) / 2 + 5, 50);
	p2score.setFillColor(sf::Color::White);

	win.setFont(font);
	win.setCharacterSize(50);
	win.setPosition(220, 300);
	win.setFillColor(sf::Color::White);

	//creates a circle for the ball.
	sf::CircleShape ball(10.0f);
	ball.setOrigin(5, 5);
	ball.setPosition(window.getSize().x / 2 + 200, window.getSize().y / 2);

	//creates a buffer to store sounds
	sf::SoundBuffer bounce, loose;
	bounce.loadFromFile("resources\\bounce.wav");
	loose.loadFromFile("resources\\loose.wav");

	//creates sound variable
	sf::Sound sound;
	
	//creates time related variables
	sf::Clock clock;
	sf::Time elapsed;

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
			if (y < (window.getSize().y - 80))
			{
				player1.move(0, 10);
			}
		}

		//if W is pressed move p1 up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			y = player1.getPosition().y;
			if (y > 80)
			{
				player1.move(0, -10);
			}
		}

		//if downKey is pressed move p2 down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			y = player2.getPosition().y;
			if (y < (window.getSize().y - 80))
			{
				player2.move(0, 10);
			}
		}

		//if upKey is pressed move p2 up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			y = player2.getPosition().y;
			if (y > 80)
			{
				player2.move(0, -10);
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
				ballX = -10;
				ballY = 0;
			}
		}

		//checks if ball is in reach of p1
		if (ball.getPosition().x <= 20)
		{
			//checks if y coordinates of ball are in p1
			if ((ball.getPosition().y < player1.getPosition().y + 80) && (ball.getPosition().y > player1.getPosition().y - 80))
			{
				//play bounce sound
				sound.setBuffer(bounce);
				sound.play();

				//reverses x speed
				ballX *= -1;

				//creates offset (angle for the ball)
				offset = ball.getPosition().y - player1.getPosition().y;

				//moves the ball in that diretion (offset)
				ballY = (offset * 1.5) / 5;
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
				ball.setPosition(window.getSize().x / 2 + 200, window.getSize().y / 2);
				ballX = -10;
				ballY = 0;
			}
		}

		//checks if ball is in reach of p1
		if (ball.getPosition().x >= window.getSize().x - 30)
		{
			//checks if y coordinates of ball are in p2
			if ((ball.getPosition().y < player2.getPosition().y + 80) && (ball.getPosition().y > player2.getPosition().y - 80))
			{
				//play bounce sound
				sound.setBuffer(bounce);
				sound.play();

				//reverses x speed
				ballX *= -1;

				//creates offset (angle for the ball)
				offset = ball.getPosition().y - player2.getPosition().y;

				//moves the ball in that diretion (offset)
				ballY = (offset * 1.5) / 5;
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
				ball.setPosition(window.getSize().x / 2 + 200, window.getSize().y / 2);
				ballX = 10;
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
			clock.restart();
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
				
				elapsed = clock.getElapsedTime();

				if (elapsed.asSeconds() >= 5)
				{
					quit = true;
					return 0;
				}

				window.clear(sf::Color::Black);
				window.draw(win);
				window.display();
			}
		}


		//increase speed of the ball
		elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() >= 5)
		{
			clock.restart();
			if ((ballX > 0 && ballX <= 15) || (ballX < 0 && ballX > -15))
			{
				if (ballX > 0)
				{
					ballX += factorSpeed;
				}
				else if (ballX < 0)
				{
					ballX -= factorSpeed;
				}
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
		window.draw(p1score);
		window.draw(p2score);
		window.draw(dash);
		window.draw(win);

		//don't know what that exactly does
		window.display();
	}
	return 0;
}

int main()
{
	int selectPosition = 0;

	sf::Image icon;
	icon.loadFromFile("resources\\icon.png");

	//initialises the window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pong", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


	sf::Music music;
	music.openFromFile("resources\\music.wav");
	music.setLoop(true);
	music.setLoopPoints({ sf::seconds(2.0f),sf::seconds(214.0f) });
	music.play();
	music.setVolume(25);

	sf::Font fontMenu;
	fontMenu.loadFromFile("resources\\menu.ttf");

	sf::Color white = sf::Color::White, grey = sf::Color (137, 137, 137);

	sf::Text title, play, close, name;
	title.setFont(fontMenu);
	play.setFont(fontMenu);
	close.setFont(fontMenu);
	name.setFont(fontMenu);

	title.setCharacterSize(120);
	title.setString("PONG");
	title.setPosition((window.getSize().x / 2), 327);
	title.setOrigin(title.getLocalBounds().width / 2, 0);

	play.setCharacterSize(60);
	play.setString("Play");
	play.setPosition((window.getSize().x / 2), 675);
	play.setOrigin(play.getLocalBounds().width / 2, 0);
	play.setFillColor(white);

	close.setCharacterSize(80);
	close.setString("Close");
	close.setPosition((window.getSize().x / 2), 755);
	close.setOrigin(close.getLocalBounds().width / 2, 0);
	close.setFillColor(grey);

	name.setCharacterSize(50);
	name.setString("A game by OPFC");
	name.setPosition((window.getSize().x / 2), 947);
	name.setOrigin(name.getLocalBounds().width / 2, 0);
	name.setFillColor(white);


	sf::Texture backgroundMenuTexture;
	backgroundMenuTexture.loadFromFile("resources\\backgroundMenu.png");

	sf::RectangleShape backgroundMenu;
	backgroundMenu.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	backgroundMenu.setTexture(&backgroundMenuTexture);
	
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			play.setFillColor(white);
			close.setFillColor(grey);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			play.setFillColor(grey);
			close.setFillColor(white);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (play.getFillColor() == white)
			{
				game(window);
			}
			else if (close.getFillColor() == white)
			{
				window.close();
			}
		}

		window.clear();
		window.draw(backgroundMenu);
		window.draw(title);
		window.draw(play);
		window.draw(close);
		window.draw(name);
		window.display();
	}
}