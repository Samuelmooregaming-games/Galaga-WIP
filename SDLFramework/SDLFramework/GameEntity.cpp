#include "GameEntity.h"

namespace SDLFramework {
	GameEntity::GameEntity(float x, float y) : mPosition(x, y), mRotation(0.0f),
		mScale(Vec2_One), mActive(true), mParent(nullptr) {

	}

	GameEntity::GameEntity(const Vector2& position) : mPosition(position), mRotation(0.0f),
		mScale(Vec2_One), mActive(true), mParent(nullptr) {
			
	}
	
	GameEntity::~GameEntity() {
		mParent = nullptr;
	}

	void GameEntity::Position(float x, float y) {
		mPosition = Vector2(x, y);
	}
	void GameEntity::Position(const Vector2& pos) {
		mPosition = pos;
	}

	Vector2 GameEntity::Position(Space space) {
		if (space == Local || mParent == nullptr) {
			return mPosition;
		}
		Vector2 parentscale = mParent->Scale(World);
	Vector2 rotposition = RotateVector(mPosition, mParent->Rotation(Local));
	return mParent->Position(World) + Vector2(rotposition.x * parentscale.x, rotposition.y * parentscale.y);
	}
	void GameEntity::Rotation(float rot) {
		mRotation = rot;
		while (mRotation > 360.0f) {
			mRotation -= 360.0f;
		}
		while (mRotation < 0.0f) {
			mRotation += 360.0f;
		}
	}
float GameEntity::Rotation(Space space) {
	if (space == Local || mParent == nullptr) {
		return mRotation;
	}
	return mParent->Rotation(World) + mRotation;
}
void GameEntity::Scale(Vector2 scale) {
	mScale = scale;
}
Vector2 GameEntity::Scale(Space space) {
	if (space == Local || mParent == nullptr) {
		return mScale;
	}
	Vector2 scale = mParent->Scale(Local);
	scale.x += mScale.x;
	scale.y += mScale.y;
	return scale;
}

void GameEntity::Active(bool active) {
	mActive = active;
}

bool GameEntity::Active() const {
	return mActive;
}
void GameEntity::Parent(GameEntity* parent) {
	if (parent == nullptr) {
		mPosition = Position(World);
		mRotation = Rotation(World);
		mScale = Scale(Local);
	}
	else {
		if (mParent != nullptr) {
			Parent(nullptr);
		}

		Vector2 parentscale = parent->Scale(World);

		mPosition = RotateVector(Position(World) - parent->Position(World), -parent->Rotation(World));
		mPosition.x /= parentscale.x;
		mPosition.y /= parentscale.y;

		mRotation -= parent->Rotation(World);
		mScale = Vector2(mScale.x / parentscale.x, mScale.y / parentscale.y);
	}
	mParent = parent;
}

GameEntity* GameEntity::Parent() {
	return mParent;
}
void GameEntity::Translate(Vector2 vec, Space space) {
	if(space == World) {
		mPosition += vec;
	}
	else {
		mPosition += RotateVector(vec, Rotation());
	}

}

void GameEntity::Rotate(float amount) {
	mRotation += amount;
}

}


