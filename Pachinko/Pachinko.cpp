#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
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

void resetGame(int& spawnPoints, int& pointPoints, list<Ball>& balls, vector<Block>& blocks, const int blocksX, const int blocksY, const int blockWithd, const int blockHeight, int level)
{
	spawnPoints = 1;
	pointPoints = 0;
	balls.clear();
	blocks.clear();
	int mid = blocksY / 2;

	switch (level)
	{
	case 0:
		for (int i = 0; i < blocksY; i++)
		{
			for (int j = 0; j < blocksX; j++)
			{
				blocks.emplace_back((j + 1) * (blockWithd + 10), (i + 1) * (blockHeight + 10), blockWithd, blockHeight, Color::Cyan);
			}
		}
		break;
	case 1:
		for (int i = 0; i < blocksY; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				blocks.emplace_back((j + 1) * (blockWithd + 10), (i + 1) * (blockHeight + 10), blockWithd, blockHeight, Color::Cyan);
			}
		}
		break;
	case 2:
		for (int i = 0; i < blocksY; i++)
		{
			for (int j = 0; j < blocksX - i; j++)
			{
				blocks.emplace_back((j + 1) * (blockWithd + 10), (i + 1) * (blockHeight + 10), blockWithd, blockHeight, Color::Cyan);
			}
		}
		break;
	case 3:
		for (int i = 0; i < blocksY; i++)
		{
			int start = abs(mid - i);
			int end = blocksX - start;
			for (int j = start; j < end; j++)
			{
				blocks.emplace_back((j + 1) * (blockWithd + 10), (i + 1) * (blockHeight + 10), blockWithd, blockHeight, Color::Cyan);
			}
		}
		break;
	case 4:
		int centerX = 800 / 2;
		int centerY = 600 / 4;
		int radius = 100;

		for (int i = 0; i < blocksY; i++)
		{
			for (int j = 0; j < blocksX; j++)
			{
				float x = (j + 1) * (blockWithd + 10);
				float y = (i + 1) * (blockHeight + 10);
				if (sqrt(pow(x - centerX, 2) + pow(y - centerY, 2)) < radius)
				{
					blocks.emplace_back(x, y, blockWithd, blockHeight, Color::Cyan);
				}
			}
		}
		break;
	}
}

int chooseLevel()
{
	int level = rand() % 5;
	cout << "Level: " << level << endl;
	return level;
}

int main()
{
	const int window_width = 800;
	const int window_height = 600;
	int level = chooseLevel();
	bool screen = false;
	int spawnPoints = 1;
	int pointPoints = 0;
	Spawn spawn(window_width / 2, 550);
	list<Ball> balls;

	RenderWindow window{ VideoMode{window_width, window_height}, "Arcan oid" };
	window.setFramerateLimit(60);

	Event event;
	unsigned blocksX = 10, blocksY = 10, blockWithd = 60, blockHeight = 20;
	int mid = blocksY / 2;

	vector<Block> blocks;

	switch (level)
	{
	case 0:
		for (int i = 0; i < blocksY; i++)
		{
			for (int j = 0; j < blocksX; j++)
			{
				blocks.emplace_back((j + 1) * (blockWithd + 10), (i + 1) * (blockHeight + 10), blockWithd, blockHeight, Color::Cyan);
			}
		}
		break;
	case 1:
		for (int i = 0; i < blocksY; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				blocks.emplace_back((j + 1) * (blockWithd + 10), (i + 1) * (blockHeight + 10), blockWithd, blockHeight, Color::Cyan);
			}
		}
		break;
	case 2:
		for (int i = 0; i < blocksY; i++)
		{
			for (int j = 0; j < blocksX - i; j++)
			{
				blocks.emplace_back((j + 1) * (blockWithd + 10), (i + 1) * (blockHeight + 10), blockWithd, blockHeight, Color::Cyan);
			}
		}
		break;
	case 3:
		for (int i = 0; i < blocksY; i++)
		{
			int start = abs(mid - i);
			int end = blocksX - start;
			for (int j = start; j < end; j++)
			{
				blocks.emplace_back((j + 1) * (blockWithd + 10), (i + 1) * (blockHeight + 10), blockWithd, blockHeight, Color::Cyan);
			}
		}
		break;
	case 4:
		int centerX = window_width / 2;
		int centerY = window_height / 4;
		int radius = 100;

		for (int i = 0; i < blocksY; i++)
		{
			for (int j = 0; j < blocksX; j++)
			{
				float x = (j + 1) * (blockWithd + 10);
				float y = (i + 1) * (blockHeight + 10);
				if (sqrt(pow(x - centerX, 2) + pow(y - centerY, 2)) < radius)
				{
					blocks.emplace_back(x, y, blockWithd, blockHeight, Color::Cyan);
				}
			}
		}
		break;
	}

	Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
	{
		cout << "Error loading font" << endl;
	}
	Text text;
	Text ballNumber;

	Texture endScreen;
	if (!endScreen.loadFromFile("C:\\Users\\User\\source\\repos\\Pachinko\\Pachinko\\endScreen.png"))
	{
		cout << "Skibidi Toilet" << endl;
	}
	RectangleShape square(sf::Vector2f(800.f, 600.f));
	square.setPosition(0, 0);
	square.setTexture(&endScreen);

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
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
		{
			int level = chooseLevel();
			resetGame(spawnPoints, pointPoints, balls, blocks, blocksX, blocksY, blockWithd, blockHeight, level);

			screen = false;
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

		if (balls.empty() && spawnPoints == 0)
		{
			screen = true;
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
		if (screen) {
			window.draw(square);
		}
		window.display();
	}

	return 0;
}