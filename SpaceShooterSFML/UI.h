#pragma once
#include <SFML/Graphics.hpp>
#include "Score.h"
using namespace sf;


struct GameOver {
	ConvexShape background;
	Text message;
	Font messageFont;
	Score* endScore;
};

void SetShape(ConvexShape& shape, int up, int down,int left, int right, Color color);

void SetGameOver(GameOver& gameover, RenderWindow& window);

void DrawGameOver(GameOver& gameover, RenderWindow& window, float& deltaTime);

