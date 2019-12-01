#pragma once
#include "Texture.h"
#include <vector>

using namespace QuickSDL;

class ScoreBoard :	public GameEntity
{
private:
	
	std::vector<Texture*> mScore;
	SDL_Color mColor;
	int mSize;
	char mAlignment;

public:
	/* parameters:
	size: the size of the font, default is 32;
	color: RGB struct, i.e. {255,255,255} (default value);
	alignment: if 'l' or 'L', ScoreBoard will expand to the right,
	           if 'r' or 'R', ScoreBoard will expand to the left.
	*/
	ScoreBoard();
	// Scoreboard with custom RGB text
	ScoreBoard(int size, SDL_Color color, char alignment);
	~ScoreBoard();

	/* Set the score to an integral value.
	You must also set the size and alignment, L or R.
	*/
	void Score(int score);

	void Render();

private:

	void ClearBoard();
};

