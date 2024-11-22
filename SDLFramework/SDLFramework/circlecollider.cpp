#include "circlecollider.h"

namespace SDLFramework {
	CircleCollider::CircleCollider(float radius, bool brodphase) : Collider(ColliderType::Circle) {
		mRadius = radius;

		if (DEBUG_COLLIDERS) {
			if (brodphase) {
				SetDebugTexture(new texture("BroadPhaseCollider.png"));

			}
			else {
				SetDebugTexture(new texture("CircleCollider.png"));
			}
			mDEbugTexture->Scale(Vec2_One * (radius * 2 / 50.0f));
		}
	}

	CircleCollider::~CircleCollider() {}

	Vector2 CircleCollider::GetFurthestPoint() {
		return Vec2_Right * (mRadius + Position(GameEntity::Local)).Magnitude();
	}

	float CircleCollider::GetRadius() {
		return mRadius;
	}
}