#include "Block.h"

Block::Block(float t_x, float t_y, float t_width, float t_height, Color color)
	: shape(Vector2f(t_width, t_height)), color(color)
{
	shape.setPosition(t_x, t_y);
	shape.setSize({ t_width, t_height });
	shape.setFillColor(color);
	shape.setOrigin(t_width / 2.f, t_height / 2.f);
}

void Block::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(shape, state);
}

float Block::left()
{
	return shape.getPosition().x - shape.getSize().x / 2.f;
}
float Block::right()
{
	return shape.getPosition().x + shape.getSize().x / 2.f;
}
float Block::top()
{
	return shape.getPosition().y - shape.getSize().y / 2.f;
}
float Block::bottom()
{
	return shape.getPosition().y + shape.getSize().y / 2.f;
}

Vector2f Block::getPosition()
{
	return shape.getPosition();
}

bool Block::isDestroyed()
{
	return destroyed;
}

void Block::destroy()
{
	destroyed = true;
}
Vector2f Block::getSize()
{
	return shape.getSize();
}

void Block::changeColor()
{
	if (color == Color::Cyan)
	{
		color = Color::Magenta;
	}
	else if (color == Color::Magenta)
	{
		color = Color::Blue;
	}
	else if (color == Color::Blue)
	{
		color = Color(139, 69, 19); // Brown color
	}
	else if (color == Color(139, 69, 19))
	{
		color = Color::White;
	}
	else if (color == Color::White)
	{
		destroy();
	}
	shape.setFillColor(color);
}

void Block::update()
{
}