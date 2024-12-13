#include "enemy.h"

std::vector<std::vector<Vector2>> Enemy::sPaths;
Player* Enemy::sPlayer = nullptr;
Formation* Enemy::sFormation = nullptr;

void Enemy::CreatePaths() {
	int screenMidPoint = (int)(Graphics::Instance()->SCREEN_WIDTH * 0.4f);

	int currentPath = 0;
	BeziarPath* path = new BeziarPath();
	path->AddCurve({
		Vector2(screenMidPoint + 50.0f, -10.0f),
		Vector2(screenMidPoint + 50.0f, -20.0f),
		Vector2(screenMidPoint + 50.0f, 30.0f),
		Vector2(screenMidPoint + 50.0f, 20.0f) }, 1);
	path->AddCurve({
		Vector2(screenMidPoint + 50.0f, 20.0f),
		Vector2(screenMidPoint + 50.0f, 100.0f),
		Vector2(75.0f, 325.0f),
		Vector2(75.0f, 425.0f) }, 25);
	path->AddCurve({
		Vector2(75.0f, 425.0f),
		Vector2(75.0f, 650.0f),
		Vector2(350.0f, 650.0f),
		Vector2(350.0f, 425.0f) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path->sample(&sPaths[currentPath]);
	delete path;

	currentPath = 1;
	path = new BeziarPath();
	int fullScreen = screenMidPoint * 2;
	path->AddCurve({
		Vector2(screenMidPoint - 50.0f, -10.0f),
		Vector2(screenMidPoint - 50.0f, -20.0f),
		Vector2(screenMidPoint - 50.0f, 30.0f),
		Vector2(screenMidPoint - 50.0f, 20.0f) }, 1);
	path->AddCurve({
		Vector2(screenMidPoint - 50.0f, 20.0f),
		Vector2(screenMidPoint - 50.0f, 100.0f),
		Vector2(fullScreen - 75.0f, 325.0f),
		Vector2(fullScreen - 75.0f, 425.0f) }, 25);
	path->AddCurve({
		Vector2(fullScreen - 75.0f, 425.0f),
		Vector2(fullScreen - 75.0f, 650.0f),
		Vector2(fullScreen - 350.0f, 650.0f),
		Vector2(fullScreen - 350.0f, 425.0f) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path->sample(&sPaths[currentPath]);
	delete path;

	currentPath = 2;
	float temp = screenMidPoint - 100.0f;

	path = new BeziarPath();
	path->AddCurve({
		Vector2(-40.0f, 720.0f),
		Vector2(-50.0f, 720.0f),
		Vector2(10.0f, 720.0f),
		Vector2(0.0f, 720.0f) }, 1);
	path->AddCurve({
		Vector2(0.0f, 720.0f),
		Vector2(200.0f, 720.0f),
		Vector2(temp, 500.0f),
		Vector2(temp, 400.0f) }, 15);
	path->AddCurve({
		Vector2(temp, 400.0f),
		Vector2(temp, 200.0f),
		Vector2(40.0f, 200.0f),
		Vector2(40.0f, 400.0f) }, 15);
	path->AddCurve({
		Vector2(40.0f, 400.0f),
		Vector2(40.0f, 500.0f),
		Vector2(temp - 120.0f, 600.0f),
		Vector2(temp - 40.0f, 440.0f) }, 15);

	sPaths.push_back(std::vector<Vector2>());
	path->sample(&sPaths[currentPath]);
	delete path;

	currentPath = 3;
	temp = screenMidPoint + 60.0f;
	float temp2 = fullScreen - 40.0f;

	path = new BeziarPath();
	path->AddCurve({
		Vector2(temp2 + 40.0f, 720.0f),
		Vector2(temp2 + 50.0f, 720.0f),
		Vector2(temp2 + 10.0f, 720.0f),
		Vector2(temp2, 720.0f) }, 1);
	path->AddCurve({
		Vector2(temp2, 720.0f),
		Vector2(temp2 - 200.0f, 720.0f),
		Vector2(temp, 500.0f),
		Vector2(temp, 400.0f) }, 15);
	path->AddCurve({
		Vector2(temp, 400.0f),
		Vector2(temp, 200.0f),
		Vector2(temp2 - 40.0f, 200.0f),
		Vector2(temp2 - 40.0f, 400.0f) }, 15);
	path->AddCurve({
		Vector2(temp2 - 40.0f, 400.0f),
		Vector2(temp2 - 40.0f, 500.0f),
		Vector2(temp + 120.0f, 600.0f),
		Vector2(temp + 40.0f, 440.0f) }, 15);

	sPaths.push_back(std::vector<Vector2>());
	path->sample(&sPaths[currentPath]);
	delete path;
}

void Enemy::SetFormation(Formation* formation) {
	sFormation = formation;
}


void Enemy::HandleFlyInState() { 
	if (mCurrentWaypoint < sPaths[mCurrentPath].size()) {
		Vector2 dist = sPaths[mCurrentPath][mCurrentWaypoint] - Position();
		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if ((sPaths[mCurrentPath][mCurrentWaypoint] - Position()).MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			//made it to be next waypoint
			mCurrentWaypoint++;
		}

		if (mCurrentWaypoint >= sPaths[mCurrentPath].size()) {
			//reached end of flyin path
			PathComplete();
		}
	}
	else {
		Vector2 dist = WorldFormationPosition() - Position();
		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			FlyInComplete();
		}
	}
}

void Enemy::HandleInFormationState() {
	Position(LocalFormationPosition());

}

void Enemy::HandleStates() {
	switch (mCurrentState) {
	case FlyIn:
		HandleFlyInState();
		break;
	case InFormation:
		HandleInFormationState();
		break;
	case Diving:
		HandleDiveState();
		break;
	case Dead:
		HandleDeadState();
		break;
	}
}

Enemy::Enemy(int path, int index, bool challenge) :
	mCurrentPath(path), mIndex(index), mChallengeStage(challenge) {
	mTimer = Timer::Instance();
	mCurrentState = FlyIn;

	mCurrentWaypoint = 1;
	Position(sPaths[mCurrentPath][0]);

	mTextures[0] = nullptr; 
	mTextures[1] = nullptr;
	mSpeed = 450.0f;
}

Enemy::~Enemy() {
	mTimer = nullptr;

	for (int i = 0; i < 2; i++) {
		delete mTextures[i];
		mTextures[i] = nullptr;
	}


}


 
Enemy::States Enemy::CurrentState() {
	return mCurrentState;
}


Vector2 Enemy::WorldFormationPosition() {
	return sFormation->Position() + LocalFormationPosition();
}

void Enemy::FlyInComplete() {
	if (mChallengeStage) {
		mCurrentState = Dead;
	}
	else {
		JoinFormation();
	}
}

void Enemy::PathComplete() {
	if (mChallengeStage) {
		mCurrentState = Dead;
	}
}

Enemy::Types Enemy::Type() {
	return mType;
}

int Enemy::Index() {
	return mIndex;
}

void Enemy::JoinFormation() {
	Position(WorldFormationPosition());
	Rotation(0);
	Parent(sFormation);
	mCurrentState = InFormation;
}

void Enemy::Dive(int type) {
	Parent(nullptr);
	mCurrentState = Diving;
	mDiveStartPosition = Position();
	mCurrentWaypoint = 1;
}


void Enemy::Update() {
	if (Active()) {
		HandleStates();
	}
}

void Enemy::Render() {
	if (Active()) {
		RenderStates();
	}
}

void Enemy::RenderFlyState() { 
		mTextures[0]->Render();

		for (int i = 0; i < sPaths[mCurrentPath].size() - 1; i++) {
			Graphics::Instance()->DrawLine(
				sPaths[mCurrentPath][i].x,
				sPaths[mCurrentPath][i].y,
				sPaths[mCurrentPath][i + 1].x,
				sPaths[mCurrentPath][i + 1].y
				);
		}
}

void Enemy::RenderInFormationState()
{ 
	mTextures[sFormation->GetTick() % 2]->Render();
	
	for (int i = 0; i < sPaths[mCurrentPath].size() - 1; i++) {
		Graphics::Instance()->DrawLine(
			sPaths[mCurrentPath][i].x,
			sPaths[mCurrentPath][i].y,
			sPaths[mCurrentPath][i + 1].x,
			sPaths[mCurrentPath][i + 1].y
		);
	}
}


void Enemy::RenderStates() {
	switch (mCurrentState) {
	case FlyIn:
		RenderFlyState();
		break;
	case InFormation:
		RenderInFormationState();
		break;
	case Diving:
		RenderDiveState();
		break;
	case Dead:
		RenderDeadState();
		break;
	}
}




