#include <iostream>
#include "UI.h"
#include <SFML/Graphics.hpp>

void SetShape(ConvexShape& shape, int up, int down, int left, int right)
{
	shape.setPointCount(4);
	shape.setPoint(0, Vector2f(left, up));
	shape.setPoint(1, Vector2f(right, up));
	shape.setPoint(2, Vector2f(right, down));
	shape.setPoint(3, Vector2f(left, down));
	shape.setFillColor(Color(30, 30, 30, 255));

}