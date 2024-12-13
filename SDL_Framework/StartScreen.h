#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include"scoreboard.h"
#include "backgrounstars.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {
public:
	StartScreen();
	~StartScreen();
	void ResetAnimation();

	int SelectedMode();

	void ChangeSelectedMode(int change);

	void Update() override;
	void Render() override;

private:
	Timer* mTimer;
	InputManager* mInputManager;

	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndpos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;


	//Top Bar Entities
	//Empty GameEntity/GameObject
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mPlayerTwo;
	Texture* mHiScore;
	Scoreboard* mplayerOneScore;
	Scoreboard* mplayerTwoScore;
	Scoreboard* mTopScore;


	//Logo Entities
	GameEntity* mLogoHolder;
	Texture* mLogo;
	AnimatedTexture* mAnimatedLogo;

	//Play Mode
	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;
	Texture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffsetPos;
	BackgroundStars* mStars;
	int mSelectedMode;

	//Bottom Bar
	GameEntity* mBottomBar;
	Texture* mNamco;
	Texture* mDates;
	Texture* mRights;
};