#include "Ball.h"
#include <random>

using namespace sf;
using namespace std;

Ball::Ball(float t_x, float t_y, float v_x, float v_y)
{
	ball.setPosition(t_x, t_y);
	ball.setRadius(ballRadius);
	ball.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));
	ball.setOrigin(ballRadius, ballRadius);
	velocity = Vector2f(v_x, v_y);
}

bool Ball::update()
{
	ball.move(velocity);

	if (left() < 0)
	{
		velocity.x = -velocity.x;
	}
	else if (right() > 800)
	{
		velocity.x = -velocity.x;
	}

	if (bottom() > 600 + ballRadius * 2)
	{
		return true;
	}
	else if (top() < 0)
	{
		velocity.y = -velocity.y;
	}

	return false;
}

void Ball::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(ball, state);
}

float Ball::left()
{
	return ball.getPosition().x - ball.getRadius();
}
float Ball::right()
{
	return ball.getPosition().x + ball.getRadius();
}
float Ball::top()
{
	return ball.getPosition().y - ball.getRadius();
}
float Ball::bottom()
{
	return ball.getPosition().y + ball.getRadius();
}

void Ball::moveDown()
{
	velocity.y = ballTestVelocity;
}
void Ball::moveUp()
{
	velocity.y = -ballTestVelocity;
}
void Ball::moveRight()
{
	velocity.x = ballTestVelocity;
}
void Ball::moveLeft()
{
	velocity.x = -ballTestVelocity;
}

Vector2f Ball::getPosition()
{
	return ball.getPosition();
}

float Ball::ballCollision()
{
	return 0;
}