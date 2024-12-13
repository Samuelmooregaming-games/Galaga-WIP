#include "Level.h"
#include "screenmanager.h"

void Level::HandleStartLabel()
{
	LabelTimer += mTimer->DeltaTime();

	if (LabelTimer >= mStageLabelOffScreen) {
		mStars->Scroll(true);
		mPlayer->Active(true);
		mPlayer->Visible(true);
		if (mStage > 1) {
			StartStage();
		}
		else {
			//READY label will only display at the start of level 1
			if (LabelTimer >= mReadyLabelOffScreen) {
				StartStage();

			}
		}
	}
}

void Level::HandleCollisions()
{
	if (!mplayerhit) {
		//sanity test
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_X)) {
			mPlayer->WasHit();
			mSidebar->SetShips(mPlayer->Lives());

			mplayerhit = true;
			mrespawntimer = 0.0f;
			mPlayer->Active(false);
			mStars->Scroll(false);
		}
	}
}

void Level::HandlePlayerDeath()
{
	if (!mPlayer->IsAnimating()) {
		if (mPlayer->Lives() > 0) {
			if (mrespawntimer == 0.0f) {
				mPlayer->Visible(false);
			}

			mrespawntimer += mTimer->DeltaTime();
			if (mrespawntimer >= mRespawnDelay) {
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mplayerhit = false;
				mStars->Scroll(true);
			}
		}
		else {
			if (mgameovertimer == 0.0f) {
				mPlayer->Visible(false);
			}
			mgameovertimer += mTimer->DeltaTime();
			if (mgameovertimer >= mgameoverdelay) {
				mCurrentState = GameOver;
			}
		}
	}
}

void Level::HandleEnemySpawning() {
	//todo concider removing when testing finnished
	//if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_S) &&
	//	mButterflyCount < MAX_BUTTERFLIES) {
	//	mEnemies.push_back(new Butterfly(0, mButterflyCount++, false));
	//	//mButterflyCount++;
	//}

	//if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_W) &&
	//	mWaspCount < MAX_WASPS) {
	//	mEnemies.push_back(new Wasp(0, mWaspCount++, false, false));
	//	//mWaspCount++;
	//}
	//if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_F) &&
	//	mBossCount < MAX_BOSSES) {
	//	mEnemies.push_back(new Boss(0, mBossCount++, false));
	//}

	mSpawnTimer += mTimer->DeltaTime();

	if (mSpawnTimer >= mSpawnDelay) {
		XMLElement* element = mSpawningPatterns.FirstChildElement("Level")->FirstChild()->NextSiblingElement();
		bool spawned = false;
		bool priorityFound = false;

		while (element != nullptr) {
			int priority = element->IntAttribute("priority");

			if (mCurrentFlyInPriority == priority) {
				priorityFound = true;
				int path = element->IntAttribute("path");
				XMLElement* child = element->FirstChildElement();
				//always give next/last child
				////based on flyinindex
				for (int i = 0; i < mCurrentFlyIndex && child != nullptr; i++) {
					child = child->NextSiblingElement();
				}

				if (child != nullptr) {
					std::string type = child->Attribute("type");
					int index = child->IntAttribute("index");

					if (type.compare("Butterfly") == 0) {
						if (!mChallengeStage) {
							//add butterfly to formation
							mFormationButterflies[index] = new Butterfly(path, index, false);
						}
						else {
							//todo change challenge to true once challenge stage 
							mEnemies.push_back(new Butterfly(path, index, false));
						}
						
					}
					spawned = true;
				}
			}
			
			//extract data
			element = element->NextSiblingElement();
		}
		if (!priorityFound) {
			//no priorities found no more spawn element
			SpawningFinnished = true;
		}
		else {
			if (!spawned) {
				//spawn element waiting nothing spawned
				if (!EnemyFlyingIn()) {
					mCurrentFlyInPriority++;
					mCurrentFlyIndex = 0;
}
			} else {
				//not finnish spawn
				mCurrentFlyIndex++;
			}
		}
		mSpawnTimer = 0.0f;
	
	}

}
bool Level::EnemyFlyingIn() {
	for (Butterfly* butterfly : mFormationButterflies) {
		if (butterfly != nullptr && 
			butterfly->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}
	return false;
}

void Level::HandleEnemyFormation() {
	mFormation->Update();

	if (mButterflyCount == MAX_BUTTERFLIES && 
		mWaspCount == MAX_WASPS &&
		mBossCount == MAX_BOSSES) {
		bool flyin = false;
		
		for (auto enemy : mEnemies) {
			if (enemy->CurrentState() == Enemy::FlyIn) {
				flyin = true;
				break;
			}
		}
		if (!flyin) {
			mFormation->Lock();
		}
	
	}
}

void Level::HandleEnemyDiving() { 
	if (mFormation->Locked()) {
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_B)) {
			for (auto enemy : mEnemies) {
				if (enemy->Type() == Enemy::Butterfly &&
					enemy->CurrentState() == Enemy::InFormation) {
					enemy->Dive();
					break;
				}
			}
		}
		
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_V)) {
			for (auto enemy : mEnemies) {
				if (enemy->Type() == Enemy::Wasp &&
					enemy->CurrentState() == Enemy::InFormation) {
					enemy->Dive();
					break;
				}
			}
		}

		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_H)) {
			for (auto enemy : mEnemies) {
				if (enemy->Type() == Enemy::Boss &&
					enemy->CurrentState() == Enemy::InFormation) {
					enemy->Dive();
					
					int index = enemy->Index();
					int firstEscortIndex = (index % 2 == 0) ?
						(index * 2) : (index * 2 - 1);
					int seccondEscortIndex = firstEscortIndex + 4;

					for (auto butterfly : mEnemies) {
						//verify enemy is butterfly in formation & 1rst/2nd index
						if(butterfly->Type() == Enemy::Butterfly &&
							butterfly->CurrentState() == Enemy::InFormation)
						{
							if (butterfly->Index() == firstEscortIndex || 
								butterfly->Index() == seccondEscortIndex) {
								butterfly->Dive(1);

						}
						
}

					}
					
					break;
				}
			}
		}
	}
}

Level::LevelStates Level::State() {
	return mCurrentState;
}

void Level::StartStage() {
	mstagestarted = true;
}

Level::Level(int stage, PlaySideBar* sideBar, Player* player) {
	mTimer = Timer::Instance();
	mSidebar = sideBar;
	mSidebar->SetLevel(stage);
	mStars = BackgroundStars::Instance();

	mStage = stage;
	mstagestarted = false;

	LabelTimer = 0.0f;

	mStageLabel = new Texture("STAGE", "emulogic.ttf", 32, { 75, 75, 200 });
	mStageLabel->Parent(this);
	mStageLabel->Position(Graphics::SCREEN_WIDTH * 0.35f, Graphics::SCREEN_HEIGHT * 0.5f);

	mStageNumber = new Scoreboard({ 75, 75, 200 });
	mStageNumber->Score(stage);
	mStageNumber->Parent(this);
	mStageNumber->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	mReadyLabel = new Texture("READY", "emulogic.ttf", 32, { 150, 0, 0 });
	mReadyLabel->Parent(this);
	mReadyLabel->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;
	
	mPlayer = player;
	mplayerhit = false;
	mRespawnDelay = 3.0f;
	mrespawnlabelonscreen = 2.0f;
	
	mGameOver = new Texture("GAME OVER", "emulogic.ttf", 32, { 255, 0, 0 });
	mGameOver->Position(Vector2(440, 460));

	mgameoverdelay = 6.0f;
	mgameovertimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = Running;

	

	mButterflyCount = 0;
	mWaspCount = 0;
	mBossCount = 0;

	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Data/Level1.xml");
	mSpawningPatterns.LoadFile(fullpath.c_str());

	mChallengeStage = mSpawningPatterns.FirstChildElement("Level")->FirstChildElement()->BoolAttribute("Value");
	
	if (!mChallengeStage) {
		//make forrmation
		
	mFormation = new Formation();
	mFormation->Position(Graphics::SCREEN_WIDTH * 0.4f, 150.0f);
	Enemy::SetFormation(mFormation);
	//initialize enemy arrays

	for (int i = 0; i < MAX_BUTTERFLIES; i++) {
		mFormationButterflies[i] = nullptr;

	}

	for (int i = 0; i < MAX_WASPS; i++) {
		mFormationWasps[i] = nullptr;

	}

	for (int i = 0; i < MAX_BOSSES; i++) {
		mFormationBoss[i] = nullptr;

	}
	
}
	mCurrentFlyInPriority = 0;
	mCurrentFlyIndex = 0;
	mSpawnDelay = 0.2f;
	mSpawnTimer = 0.0f;
	SpawningFinnished = false;

}

Level::~Level() {
	mTimer = nullptr;
	mSidebar = nullptr;
	mStars = nullptr;
	mPlayer = nullptr;
	
	delete mFormation;
	mFormation = nullptr;
	
	for (int i = 0; i < MAX_BUTTERFLIES; i++) {
		delete mFormationButterflies[i];
		mFormationButterflies[i] = nullptr;

	}

	for (int i = 0; i < MAX_WASPS; i++) {
		delete mFormationWasps[i];
		mFormationWasps[i] = nullptr;

	}

	for (int i = 0; i < MAX_BOSSES; i++) {
		delete mFormationBoss[i];
		mFormationBoss[i] = nullptr;

	}

	delete mStageLabel;
	mStageLabel = nullptr;
	delete mStageNumber;
	mStageNumber = nullptr;
	delete mReadyLabel;
	mReadyLabel = nullptr;
	delete mGameOver;
	mGameOver = nullptr;

	for (auto enemy : mEnemies) {
		delete enemy;
		enemy = nullptr;
	}
	mEnemies.clear();
}


void Level::Update() {
	if (!mstagestarted) {
		HandleStartLabel();
	}
	else {
		if (!SpawningFinnished) {
			HandleEnemySpawning();
		}
		if (!mChallengeStage) {
			HandleEnemyFormation();
		} 
		else {
		for (auto enemy : mEnemies) {
			
			enemy->Update();
		}
	}
		
		

		

		HandleCollisions();

		if (mplayerhit) {
			HandlePlayerDeath();
		}
		else {
			if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N)) {
				mCurrentState = Finished;
			}
		}
	}
}
		void Level::Render() {
			if (!mstagestarted) {
				if (LabelTimer > mStageLabelOnScreen && LabelTimer < mStageLabelOffScreen) {
					mStageLabel->Render();
					mStageNumber->Render();
				}
				else if (LabelTimer > mReadyLabelOnScreen && LabelTimer < mReadyLabelOffScreen) {
					mReadyLabel->Render();
				}
				
			}
			else {
				for (auto enemy : mEnemies) {
					enemy->Render();
				}

				if (mplayerhit) {
					if (mrespawntimer >= mReadyLabelOnScreen) {
						mReadyLabel->Render();
					}

					if (mgameovertimer >= mGameOverLabelOnScreen) {
						mGameOver->Render();
					}
				}
			}
		}
	