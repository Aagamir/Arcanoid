#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
class Ball : public Drawable
{
public:
	Ball(float t_x, float t_y, float v_x, float v_y);

	bool update();

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	float left();
	float right();
	float top();
	float bottom();

	Vector2f getPosition();

	float ballCollision();

private:
	CircleShape ball;
	const float ballRadius{ 10.0f };
	const float ballTestVelocity{ 3.0f };
	Vector2f velocity{ ballTestVelocity, ballTestVelocity };

	void draw(RenderTarget& target, RenderStates state) const override;
};
