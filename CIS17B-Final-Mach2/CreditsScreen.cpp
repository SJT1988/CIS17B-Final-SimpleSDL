/*

Credits are unfinished, will be done today

*/

#include "CreditsScreen.h"
#include <iostream>
#include <array>

CreditsScreen::CreditsScreen()
{
	//+--------------------------------+
	//|           DEV HEADER           |
	//+--------------------------------+

	texCredits = new Texture("DEV TEAM", "impact.ttf", 48, { 255,255,255 });
	texCredits->Parent(this);
	texCredits->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.1f));

	//+--------------------------------+
	//|            DEV TEAM            |
	//+--------------------------------+

	devTeam = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f,
		Graphics::Instance()->SCREEN_HEIGHT*0.25f));
	devTeam->Parent(this);
	
	texKristian = new Texture("Kristian Dompor", "impact.ttf", 36, { 255,255,255 });
	texKristian->Parent(devTeam);
	texKristian->Pos(Vector2(-384.0f, 0.0f));

	texSpencer = new Texture("Spencer Trumbore", "impact.ttf", 36, { 255,255,255 });
	texSpencer->Parent(devTeam);
	texSpencer->Pos(VEC2_ZERO);

	texWilliam = new Texture("Shuai Xiong", "impact.ttf", 36, { 255,255,255 });
	texWilliam->Parent(devTeam);
	texWilliam->Pos(Vector2(384.0f, 0.0f));
	
	//+--------------------------------+
	//|          DEV TEAM LIST         |
	//+--------------------------------+
	dutiesKristian[0] = new Texture("Systems Engineering", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	dutiesKristian[1] = new Texture("Artificial Intelligence", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	dutiesKristian[2] = new Texture("User Interface", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	dutiesKristian[3] = new Texture("QA Analysis", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	for (int i = 0; i < 4; i++)
	{
		dutiesKristian[i]->Pos(Vector2(texKristian->Pos().x, texKristian->Pos().y + 16.0f + 40.0f*(i + 1)));
		dutiesKristian[i]->Parent(texKristian);
	}

	dutiesSpencer[0] = new Texture("Systems Engineering", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	dutiesSpencer[1] = new Texture("Art", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	dutiesSpencer[2] = new Texture("Animation", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	dutiesSpencer[3] = new Texture("Sound Engineering", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	for (int i = 0; i < 4; i++)
	{
		dutiesSpencer[i]->Pos(Vector2(texSpencer->Pos().x, texSpencer->Pos().y + 16.0f + 40.0f*(i + 1)));
		dutiesSpencer[i]->Parent(texSpencer);
	}

	dutiesWilliam[0] = new Texture("Algorithm Engineering", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	dutiesWilliam[1] = new Texture("Level Design", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	dutiesWilliam[2] = new Texture("Animation", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	dutiesWilliam[3] = new Texture("QA Analysis", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	for (int i = 0; i < 4; i++)
	{
		dutiesWilliam[i]->Pos(Vector2(texWilliam->Pos().x, texWilliam->Pos().y + 16.0f + 40.0f*(i + 1)));
		dutiesWilliam[i]->Parent(texWilliam);
	}

	//+--------------------------------+
	//|     ACKNOWLEDGMENTS HEADER     |
	//+--------------------------------+

	texAcknowledgments = new Texture("ACKNOWLEDGMENTS", "impact.ttf", 48, { 255,255,255 });
	texAcknowledgments->Parent(this);
	texAcknowledgments->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.6f));

	acknowledgments = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f,
		Graphics::Instance()->SCREEN_HEIGHT*0.75f));
	acknowledgments->Parent(this);

	texCarlBirch = new Texture("Carl Birch", "impact.ttf", 36, { 255,255,255 });
	texCarlBirch->Pos(acknowledgments->Pos() - (VEC2_RIGHT*192.0f));
	texCarlBirch->Parent(acknowledgments);

	texBirchEngine0 = new Texture("Creator of", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	texBirchEngine0->Pos(texCarlBirch->Pos() + VEC2_UP * 56.0f);
	texBirchEngine0->Parent(texCarlBirch);
	texBirchEngine1 = new Texture("Birch Engine", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	texBirchEngine1->Pos(texCarlBirch->Pos() + VEC2_UP * 96.0f);
	texBirchEngine1->Parent(texCarlBirch);


	texAtherOmar = new Texture("Ather Omar", "impact.ttf", 36, { 255,255,255 });
	texAtherOmar->Pos(acknowledgments->Pos() + (VEC2_RIGHT*192.0f));
	texAtherOmar->Parent(acknowledgments);

	texQuickSDL0 = new Texture("Creator of", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	texQuickSDL0->Pos(texAtherOmar->Pos() + VEC2_UP * 56.0f);
	texQuickSDL0->Parent(texAtherOmar);
	texQuickSDL1 = new Texture("QuickSDL", "forgotmybazookaathome.ttf", 24, { 255,255,255 });
	texQuickSDL1->Pos(texAtherOmar->Pos() + VEC2_UP * 96.0f);
	texQuickSDL1->Parent(texAtherOmar);


	texFootnote = new Texture("Music, soundFX and this font ripped off from Square/Nintendo. Press \'ESC\' to continue.", "forgotmybazookaathome.ttf", 18, { 255,255,255 });
	texFootnote->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f,Graphics::Instance()->SCREEN_HEIGHT*0.95f));
	texFootnote->Parent(this);
	texCursor = new AnimatedTexture("monster.png", 0.0f, 0.0f, 64, 64, 4, 0.25f, AnimatedTexture::horizontal);
	texCursor->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.95f, Graphics::Instance()->SCREEN_HEIGHT*0.95f));
	texCursor->Parent(this);
}

CreditsScreen::~CreditsScreen()
{
	delete texCredits;
	texCredits = NULL;
	delete texKristian;
	texKristian = NULL;
	delete texSpencer;
	texSpencer = NULL;
	delete texWilliam;
	texWilliam = NULL;

	for (Texture* t : dutiesKristian)
	{
		delete t;
		t = NULL;
	}
	for (Texture* t : dutiesSpencer)
	{
		delete t;
		t = NULL;
	}
	for (Texture* t : dutiesWilliam)
	{
		delete t;
		t = NULL;
	}

	delete texAcknowledgments;
	texAcknowledgments = NULL;
	delete texCarlBirch;
	texCarlBirch = NULL;
	delete texAtherOmar;
	texAtherOmar = NULL;
	delete texBirchEngine0;
	texBirchEngine0 = NULL;
	delete texBirchEngine1;
	texBirchEngine1 = NULL;
	delete texQuickSDL0;
	texQuickSDL0 = NULL;
	delete texQuickSDL1;
	texQuickSDL1 = NULL;
	delete texFootnote;
	texFootnote = NULL;
	delete texCursor;
	texCursor = NULL;
}

void CreditsScreen::Update()
{
	texCursor->Update();
}

void CreditsScreen::Render()
{
	texCredits->Render();
	texKristian->Render();
	texSpencer->Render();
	texWilliam->Render();
	
	for (int i = 0; i < 4; i++)
	{
		dutiesKristian[i]->Render();
		dutiesSpencer[i]->Render();
		dutiesWilliam[i]->Render();
	}

	texAcknowledgments->Render();
	texCarlBirch->Render();
	texAtherOmar->Render();
	texBirchEngine0->Render();
	texBirchEngine1->Render();
	texQuickSDL0->Render();
	texQuickSDL1->Render();
	texFootnote->Render();
	texCursor->Render();
}
