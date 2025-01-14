#include "Spawn.h"
#include <vector>

Spawn::Spawn(float t_x, float t_y)
{
	shape.setPosition(t_x, t_y);
	shape.setSize({ spawnWidth, spawnHeight });
	shape.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));
	shape.setOrigin(spawnWidth / 2.f, spawnHeight / 2.f);
}

void Spawn::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(shape, state);
}

Vector2f Spawn::update()
{
	shape.move(velocity);

	if (Keyboard::isKeyPressed(Keyboard::Key::A) && left() > 0)
	{
		velocity.x = -spawnVelocity;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D) && right() < 800)
	{
		velocity.x = spawnVelocity;
	}
	else
	{
		velocity.x = 0;
	}

	return shape.getPosition();
}

float Spawn::left()
{
	return shape.getPosition().x - shape.getSize().x / 2.f;
}
float Spawn::right()
{
	return shape.getPosition().x + shape.getSize().x / 2.f;
}
float Spawn::top()
{
	return shape.getPosition().y - shape.getSize().y / 2.f;
}
float Spawn::bottom()
{
	return shape.getPosition().y + shape.getSize().y / 2.f;
}

Vector2f Spawn::getPosition()
{
	return shape.getPosition();
}