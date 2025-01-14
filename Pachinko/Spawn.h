#pragma once
#include <SFML\Graphics.hpp>
using namespace std;
using namespace sf;
class Spawn : public Drawable
{
public:
	Spawn(float t_x, float t_y);
	Vector2f update();

	float left();
	float right();
	float top();
	float bottom();

	Vector2f getPosition();
private:
	void draw(RenderTarget& target, RenderStates state) const override;
	RectangleShape shape;
	const float spawnWidth{ 80.0f };
	const float spawnHeight{ 20.0f };
	const float spawnVelocity{ 9.0f };
	Vector2f velocity{ spawnVelocity,0.f };
	Vector2f velocity2{ spawnVelocity,0.f };
};
