#include <iostream>
#include "UI.h"
#include "Math.h"
#include <SFML/Graphics.hpp>

void SetShape(ConvexShape& shape, float up, float down, float left, float right, Color color)
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
	Vector2f GOMessagePos = Vector2f(windowCenter.x, windowCenter.y - 50);
	Vector2f GOEndScorePos = Vector2f(windowCenter.x - 25, windowCenter.y + 25);
	Vector2f GORetryButtonPos = Vector2f(windowCenter.x - 125, windowCenter.y + 90);
	Vector2f GORetryButtonSize = Vector2f(250, 60);
	Vector2f GORetryTextPos = Vector2f(windowCenter.x - 15, windowCenter.y + 115);
	sf::FloatRect textRect;

	SetShape(gameover.background, 0, 1080, 0, 1920, Color(50, 0, 0, 255));

	if (!gameover.messageFont.loadFromFile("ARCADE_I.TTF"))
	{
		std::cout << "Error : couldn't load font" << std::endl;
	}
	gameover.message.setFont(gameover.messageFont);
	gameover.message.setCharacterSize(75);
	gameover.message.setString("GAME OVER");
	gameover.message.setFillColor(Color(150, 20, 20, 255));
	textRect = gameover.message.getLocalBounds();
	gameover.message.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	gameover.message.setPosition(GOMessagePos);

	gameover.endScore = gameover.score->scoreDisplay;
	textRect = gameover.endScore.getLocalBounds();
	gameover.endScore.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f); 
	gameover.endScore.setPosition(GOEndScorePos);

	gameover.retryButton.setPosition(GORetryButtonPos);
	gameover.retryButton.setSize(GORetryButtonSize);
	gameover.retryButton.setOutlineColor(Color(150, 50, 50, 255));
	gameover.retryButton.setFillColor(Color(0, 0, 0, 0));
	gameover.retryButton.setOutlineThickness(3);

	gameover.retryText.setFont(gameover.messageFont);
	gameover.retryText.setCharacterSize(35);
	gameover.retryText.setString("Quit ?");
	gameover.retryText.setFillColor(Color(150, 20, 20, 255));
	gameover.retryText.getLocalBounds();
	gameover.retryText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	gameover.retryText.setPosition(GORetryTextPos);

}

void DisplayGameOver(GameOver& gameover, GAMESTATE& state)
{
	UpdateGameOverScore(gameover);
	state = GAMESTATE::GAMEOVER;
	std::cout << state << std::endl;
}

void UpdateGameOverScore(GameOver& gameover)
{
	gameover.endScore.setString(gameover.score->scoreDisplay.getString());
}

void DrawGameOver(GameOver& gameover, RenderWindow& window, float& deltaTime)
{
	window.draw(gameover.background);
	window.draw(gameover.message);
	window.draw(gameover.endScore);
	window.draw(gameover.retryButton);
	window.draw(gameover.retryText);
}

void RetryButtonF(GameOver gameover,RenderWindow& window)
{
	Mouse mouse;
	Vector2f windowCenter = Vector2f{ window.getSize().x / 2.0f ,window.getSize().y / 2.0f + 10 };
	bool isOnRetryButton = IsOverlappingCircleOnBox(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), 1, gameover.retryButton.getPosition() + gameover.retryButton.getSize() / 2.0f, gameover.retryButton.getSize());


	if (isOnRetryButton)
	{
		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			window.close();
		}
	}

}
