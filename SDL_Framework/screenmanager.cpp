#include "screenmanager.h"
#include"GameManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}
	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();

	mBackgroundStars = BackgroundStars::Instance();
	mStartScreen = new StartScreen();
	mPlayscreen = new PlayScreen();
	

	mCurrentScreen = Start;
	
	
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;

	BackgroundStars::Release();
	mBackgroundStars = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayscreen;
	mPlayscreen = nullptr;
	
	
}

void ScreenManager::Update() {
	mBackgroundStars->Update();

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			mCurrentScreen = Play;
			mStartScreen->ResetAnimation();
			mPlayscreen->StartNewGame();


			
			}
			break;
	case Play:
		mPlayscreen->Update();


		if (mPlayscreen->GameOver()) {
			mCurrentScreen = Start;
		}
		break;
		
	
	}
}

void ScreenManager::Render() {
	mBackgroundStars->Render();

	switch (mCurrentScreen)
	{
	case Start:
		mStartScreen->Render();
		
		break;
	case Play:
		mPlayscreen->Render();
		
		break;
	
	}
}