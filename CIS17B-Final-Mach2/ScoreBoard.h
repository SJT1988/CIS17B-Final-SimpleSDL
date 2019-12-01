#pragma once
#include "Texture.h"
#include <vector>

using namespace QuickSDL;

class ScoreBoard : public GameEntity
{
private:

	std::vector<Texture*> mScore;
	SDL_Color mColor;

public:
	// Default constructor uses white text
	ScoreBoard();
	// Scoreboard with custom RGB text
	ScoreBoard(SDL_Color color);
	~ScoreBoard();

	// Set the score to an integral value
	void Score(int score);

	void Render();

private:

	void ClearBoard();
};