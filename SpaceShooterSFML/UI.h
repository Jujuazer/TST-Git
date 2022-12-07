#pragma once
#include <SFML/Graphics.hpp>
#include "Score.h"
#include "game.h"
using namespace sf;


struct GameOver {
	ConvexShape background;

	Text message;
	Font messageFont;

	Score* score;
	Text endScore;

	RectangleShape retryButton;
	Text retryText;
};

void SetShape(ConvexShape& shape, float up, float down, float left, float right, Color color = Color(0, 0, 0, 0));

void SetGameOver(GameOver& gameover, RenderWindow& window);

void UpdateGameOverScore(GameOver& gameover);

void DisplayGameOver(GameOver& gameover, GAMESTATE& state);

void DrawGameOver(GameOver& gameover, RenderWindow& window, float& deltaTime);

void RetryButtonF(GameOver gameover, RenderWindow& window);