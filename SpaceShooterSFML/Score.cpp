#include <iostream>
#include "Score.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void SetUpScore(Score& refScore, float time)
{
	refScore.timeBeforePointsUp = time;
	if (!refScore.scoreFont.loadFromFile("ARCADE_I.TTF"))
	{
		std::cout << "Error : couldn't load font" << std::endl;
	}
	refScore.scoreDisplay.setFont(refScore.scoreFont);
	refScore.scoreDisplay.setCharacterSize(50);
	refScore.scoreDisplay.setString("0");

}

void SetScore(Score& refScore, int scoreBonus)
{
	refScore.score += scoreBonus;
	refScore.scoreDisplay.setString(std::to_string(refScore.score));

}

void AddPerTime(Score& refScore, float deltaTime, int scoreBonus)
{
	refScore.counter += deltaTime;
	// debug
	// std::cout << refScore.counter << " ; " << refScore.timeBeforePointsUp << std::endl;
	// end of debug
	if (refScore.timeBeforePointsUp < refScore.counter)
	{
		SetScore(refScore, scoreBonus);
		refScore.counter = 0;
	}
}

void UpdateDrawScore(Score& refScore, RenderWindow& window)
{

	window.draw(refScore.scoreDisplay);
}