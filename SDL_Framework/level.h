#pragma once
#include "PlaySideBar.h"
#include "backgrounstars.h"
#include "player.h"
#include "Butterfly.h"
#include"Formation.h"
#include "enemy.h"
#include"wasp.h"
#include "Boss.h"
#include "tinyxml2.h"
using namespace SDLFramework;
using namespace tinyxml2;

class Level : public GameEntity {
public:
	

	enum LevelStates {Running, Finished, GameOver};
	Level(int stage, PlaySideBar* sidebar, Player* player);
	~Level();
	LevelStates State();
	void Update(); //override
	void Render(); //override
	

private:
	Timer* mTimer;
	PlaySideBar* mSidebar;
	BackgroundStars* mStars;
	Player* mPlayer;
	
	Formation* mFormation;

	static const int MAX_BUTTERFLIES = 16;
	static const int MAX_WASPS = 20;
	static const int MAX_BOSSES = 4;

	int mButterflyCount;
	int mWaspCount;
	int mBossCount;
	
	Butterfly* mFormationButterflies[MAX_BUTTERFLIES];
	Wasp* mFormationWasps[MAX_WASPS];
	Boss* mFormationBoss[MAX_BOSSES];

	std::vector<Enemy*> mEnemies;

	XMLDocument mSpawningPatterns;
	int mCurrentFlyInPriority;
	int mCurrentFlyIndex;

	float mSpawnDelay;
	float mSpawnTimer;
	bool SpawningFinnished;


	int mStage;
	bool mChallengeStage;
	bool mstagestarted;

	Texture* mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Texture* mStageLabel;
	Scoreboard* mStageNumber;
	Texture* mGameOver;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	float LabelTimer;



	bool mplayerhit;
	float mRespawnDelay;
	float mrespawntimer;
	float mrespawnlabelonscreen;
	LevelStates mCurrentState;
	float mgameoverdelay;
	float mgameovertimer;
	float mGameOverLabelOnScreen;
	
	void HandleStartLabel();
	void HandleCollisions();
	void HandlePlayerDeath();
	
	void StartStage();

	bool EnemyFlyingIn();

	void HandleEnemySpawning();
	void HandleEnemyFormation();
	void HandleEnemyDiving();

};