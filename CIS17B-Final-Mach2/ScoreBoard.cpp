#include "ScoreBoard.h"
#include <cctype>
#include <string>
#include <iostream>

ScoreBoard::ScoreBoard() : ScoreBoard(32, { 255,255,255 }, 'l')
{
	
}

ScoreBoard::ScoreBoard(int size, SDL_Color color, char alignment)
{
	try
	{
		mColor = color;
		Score(0);
		mSize = size;
		if (toupper(alignment) == 'L' || toupper(alignment) == 'R')
		{
			mAlignment = toupper(alignment);
		}
		else
			throw "Scoreboard alignment error: Must use 'l', 'L', 'r' or 'R'";
	}
	catch (const char* exp) {
		std::cout << "Exception caught \n ";
		std::cout << exp << std::endl;
	}
}

ScoreBoard::~ScoreBoard()
{
	ClearBoard();
}

void ScoreBoard::ClearBoard()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		delete mScore[i];
		mScore[i] = NULL;
	}

	mScore.clear();
}

void ScoreBoard::Score(int score)
{
	ClearBoard();

	if (score == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			mScore.push_back(new Texture("0", "forgotmybazookaathome.ttf", mSize, mColor));
			mScore[i]->Parent(this);
			if (mAlignment == 'L') mScore[i]->Pos(Vector2(static_cast<float>(mSize)*i, 0.0f));
			else if (mAlignment == 'R') mScore[i]->Pos(Vector2(static_cast<float>(mSize)*i, 0.0f));
			//mScore[i]->Pos(Vector2((mAlignment == 'L' ? static_cast<float>(mSize)*i : -static_cast<float>(mSize)*i), 0.0f));
		}
	}

	else
	{
		std::string str = std::to_string(score);
		int lastIndex = str.length() - 1;

		for (int i = 0; i <= lastIndex; i++)
		{
			mScore.push_back(new Texture(str.substr(i, 1), "forgotmybazookaathome.ttf", mSize, mColor));
			mScore[i]->Parent(this);
			if (mAlignment == 'L') mScore[i]->Pos(Vector2(static_cast<float>(mSize)*(lastIndex - i), 0.0f));
			else if (mAlignment == 'R') mScore[i]->Pos(Vector2(-static_cast<float>(mSize)*(lastIndex - i), 0.0f));
			// mScore[i]->Pos(Vector2((mAlignment == 'L' ? static_cast<float>(mSize)*(lastIndex - i) : -static_cast<float>(mSize)*(lastIndex - i)), 0.0f));
			std::cout << mScore[i]->Pos(world) << std::endl;
		}
	}
}

void ScoreBoard::Render()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		mScore[i]->Render();
	}
}