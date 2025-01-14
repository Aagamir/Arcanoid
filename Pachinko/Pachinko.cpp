#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include "Ball.h"
#include "Spawn.h"
#include "Block.h"

using namespace std;
using namespace sf;

template <class T1, class T2> bool isIntersecting(T1& A, T2& B)
{
	return A.right() >= B.left() && A.left() <= B.right() && A.bottom() >= B.top() && A.top() <= B.bottom();
}

bool collisionTest(Spawn& spawn, Ball& ball)
{
	if (!isIntersecting(spawn, ball)) return false;

	ball.moveUp();

	if (ball.getPosition().x < spawn.getPosition().x)
	{
		ball.moveLeft();
	}
	else if (ball.getPosition().x > spawn.getPosition().x)
	{
		ball.moveRight();
	}

	if (ball.getPosition().y < spawn.getPosition().y)
	{
		ball.moveUp();
	}
	else if (ball.getPosition().y > spawn.getPosition().y)
	{
		ball.moveDown();
	}
}

bool collisionTest(Block& block, Ball& ball)
{
	if (!isIntersecting(block, ball)) return false;

	block.changeColor();

	float overlapLeft{ ball.right() - block.left() };
	float overlapRight{ block.right() - ball.left() };
	float overlapTop{ ball.bottom() - block.top() };
	float overlapBottom{ block.bottom() - ball.top() };

	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

	if (abs(minOverlapX) < abs(minOverlapY))
	{
		ballFromLeft ? ball.moveLeft() : ball.moveRight();
	}
	else
	{
		ballFromTop ? ball.moveUp() : ball.moveDown();
	}

	return true;
}

int main()
{
	const int window_width = 800;
	const int window_height = 600;

	vector<float> x;
	vector<float> y;
	vector<float> vx;
	vector<float> vy;
	int spawnPoints = 1;
	int pointPoints = 0;
	Spawn spawn(window_width / 2, 550);
	list<Ball> balls;

	RenderWindow window{ VideoMode{window_width, window_height}, "PAAAAAAAA-CHIN-KO" };
	window.setFramerateLimit(60);

	Event event;
	unsigned blocksX = 10, blocksY = 4, blockWithd = 60, blockHeight = 20;

	vector<Block> blocks;

	for (int i = 0; i < blocksY; i++)
	{
		for (int j = 0; j < blocksX; j++)
		{
			blocks.emplace_back((j + 1) * (blockWithd + 10), (i + 1) * (blockHeight + 10), blockWithd, blockHeight, Color::Cyan);
		}
	}

	Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
	{
		cout << "Error loading font" << endl;
	}
	Text text;
	Text ballNumber;

	Image image;
	if (!image.loadFromFile("endScreen.png"))
	{
		cout << "Error loading image" << endl;
	}

	while (true)
	{
		window.clear(Color::Black);
		window.pollEvent(event);

		if (event.type == Event::Closed)
		{
			window.close();
			break;
		}
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
		{
			window.close();
			break;
		}
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::P)
		{
			spawnPoints++;
		}

		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
		{
			if (spawnPoints > 0)
			{
				spawnPoints--;
				float randomXVelocity = -4 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (7 - (-7))));
				float randomYVelocity = -10 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0 - (-3))));
				Ball ball(spawn.getPosition().x, spawn.getPosition().y, randomXVelocity, randomYVelocity);
				balls.push_back(ball);
			}
		}

		for (auto it = balls.begin(); it != balls.end();)
		{
			if (it->update())
			{
				it = balls.erase(it); // Remove the ball if it should be deleted
			}
			else
			{
				collisionTest(spawn, *it);
				window.draw(*it);
				++it;
			}
		}

		if (balls.empty())
		{
			//przegrywasz
		}

		Vector2f currentSpawnPosition = spawn.update();

		text.setFont(font);
		text.setString("Points: " + to_string(spawnPoints));
		text.setCharacterSize(24);
		text.setFillColor(Color::White);
		text.setPosition(10, 550);
		window.draw(text);

		ballNumber.setFont(font);
		ballNumber.setString("Balls: " + to_string(balls.size()));
		ballNumber.setCharacterSize(24);
		ballNumber.setFillColor(Color::White);
		ballNumber.setPosition(650, 550);
		window.draw(ballNumber);

		for (auto& block : blocks)
		{
			for (auto& ball : balls)
			{
				if (collisionTest(block, ball))
				{
					pointPoints++;
					if (pointPoints == 5)
					{
						spawnPoints++;
						pointPoints = 0;
					}
					auto iterator = remove_if(begin(blocks), end(blocks), [](Block& block) { return block.isDestroyed(); }); // przesuwa zniszczone bloki na koniec
					blocks.erase(iterator, end(blocks));
					break;
				}
			}
		}

		window.draw(spawn);

		for (auto& block : blocks)
		{
			window.draw(block);
		}

		window.display();
	}

	return 0;
}