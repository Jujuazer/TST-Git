#include <iostream>
#include "UI.h"
#include <SFML/Graphics.hpp>

void SetShape(ConvexShape& shape, int up, int down, int left, int right, Color color)
{
	shape.setPointCount(4);
	shape.setPoint(0, Vector2f(left, up));
	shape.setPoint(1, Vector2f(right, up));
	shape.setPoint(2, Vector2f(right, down));
	shape.setPoint(3, Vector2f(left, down));
	shape.setFillColor(color);

}

void SetGameOver(GameOver& gameover, RenderWindow& window)
{
	Vector2f windowCenter = Vector2f{ window.getSize().x / 2.0f ,window.getSize().y / 2.0f + 10 };

	SetShape(gameover.background, 0, 1080, 0, 1920, Color(50, 0, 0, 255));
		if (!gameover.messageFont.loadFromFile("ARCADE_I.TTF"))
		{
			std::cout << "Error : couldn't load font" << std::endl;
		}
	gameover.message.setFont(gameover.messageFont);
	gameover.message.setCharacterSize(30);
	gameover.message.setString("0");
	gameover.message.setPosition(windowCenter);

	gameover.endScore->scoreDisplay.setPosition(Vector2f(windowCenter.x, windowCenter.y + 40));

}

void DrawGameOver(GameOver& gameover, RenderWindow& window, float& deltaTime)
{
	window.draw(gameover.background);
	window.draw(gameover.message);
	window.draw(gameover.endScore->scoreDisplay);
	deltaTime = 0;
}