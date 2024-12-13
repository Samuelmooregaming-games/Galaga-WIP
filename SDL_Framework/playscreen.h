#pragma once
#include "audiomanager.h"
#include "level.h"
#include "player.h"


//using namespace SDLFramework;

class PlayScreen : public GameEntity {
public:
	PlayScreen();
	~PlayScreen();
	void StartNextLevel();
	void StartNewGame();
	void Update() override;
	bool GameOver();
	void Render() override;

private:
	Timer* mTimer;
	AudioManager* mAudio;

	BackgroundStars* mStars;
	PlaySideBar* mSideBar;

	Texture* mStartLabel;
	
	Level* mLevel;
	Player * mPlayer;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;
	bool mLevelStarted;
	
	int mCurrentStage;
};