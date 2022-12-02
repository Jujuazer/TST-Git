#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

struct Score {
	int score = 0;
	Text scoreDisplay;
	Font scoreFont;
	float timeBeforePointsUp = 1;
	float counter = 0;
};



void SetUpScore(Score& refScore, float time);

void SetScore(Score& refScore, int scoreBonus);

void AddPerTime(Score& refScore, float deltaTime, int scoreBonus);

void UpdateDrawScore(Score& refScore, RenderWindow& window);

//void ResetDrawScore(Text& score, RenderWindow window);