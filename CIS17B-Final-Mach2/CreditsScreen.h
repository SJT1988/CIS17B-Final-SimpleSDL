/*

Credits are unfinished, will be done today

*/

#pragma once
#include "AnimatedTexture.h"

using namespace QuickSDL;

class CreditsScreen: public GameEntity
{
private:

	Texture* texCredits;

	GameEntity* devTeam;
	Texture* texKristian;
	Texture* texSpencer;
	Texture* texWilliam;

	Texture* dutiesKristian[4];
	Texture* dutiesSpencer[4];
	Texture* dutiesWilliam[4];

	Texture* texAcknowledgments;

	GameEntity* acknowledgments;
	Texture* texCarlBirch;
	Texture* texAtherOmar;

	Texture* texBirchEngine0;
	Texture* texBirchEngine1;
	Texture* texQuickSDL0;
	Texture* texQuickSDL1;

	Texture* texFootnote;
	AnimatedTexture* texCursor;

	Texture* EnterToReturn;

public:
	CreditsScreen();
	~CreditsScreen();

	void Update();
	void Render();
};