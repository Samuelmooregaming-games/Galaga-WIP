#include "StartScreen.h"

StartScreen::StartScreen() {
	mtimer = Timer::Instance();

	mTopbar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.0f);
	mPlayerone = new texture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
	mPlayertwo = new texture("2UP", "emulogic.ttf", 32, { 200, 0, 0 });
	mHighScore = new texture("HI SCORE", "emulogic.ttf", 32, { 200, 0, 0 });

	mTopbar->Parent(this);
	mPlayerone->Parent(mTopbar);
	mPlayertwo->Parent(mTopbar);
	mHighScore->Parent(mTopbar);

	mPlayerone->Position(-Graphics::SCREEN_WIDTH * 0.35f, 0.0f);
	mPlayertwo->Position(Graphics::SCREEN_WIDTH * 0.2f, 0.0f);
	mHighScore->Position(-30, 0.0f);
}

void StartScreen::Update() { }

void StartScreen::Render() {
	mPlayerone->Render();
	mPlayertwo->Render();
	mHighScore->Render();
}

StartScreen::~StartScreen() {
	//topbar
	delete mTopbar;
	mTopbar = nullptr;

	delete mPlayerone;
	mPlayerone = nullptr;

	delete mPlayertwo;
	mPlayertwo = nullptr;

	delete mHighScore;
	mHighScore = nullptr;
}