#include "physicsentity.h"
#include "physicsmanager.h"
#include "physicshelper.h"

namespace SDLFramework {
	void PhysicsEntity::AddCollider(Collider* collider, Vector2 localpos) {
		collider->Parent(this);
		collider->Position(localpos);
		mColliders.push_back(collider);


		if (mColliders.size() > 1 || mColliders[0]->GetType() != Collider::ColliderType::Circle) {
			float furthestdistance = mColliders[0]->GetFurthestPoint().Magnitude();
			float dist = 0.0f;

			for (int i = 1; i < mColliders.size(); i++) {
				dist = mColliders[i]->GetFurthestPoint().Magnitude();

				if (dist > furthestdistance) {
					furthestdistance = dist;
				}
			}
		
			delete mBrodPhaseCollider;
			mBrodPhaseCollider = new CircleCollider(furthestdistance, true);
			mBrodPhaseCollider->Parent(this);
			mBrodPhaseCollider->Position(Vec2_Zero);
		}

	}

	PhysicsEntity::PhysicsEntity() {
		mBrodPhaseCollider = nullptr;
		mID = 0;
	}

	PhysicsEntity::~PhysicsEntity() {
		for (auto colliders : mColliders) {
			delete colliders;
			colliders = nullptr;
		}
		mColliders.clear();

		delete mBrodPhaseCollider;
		mBrodPhaseCollider = nullptr;

		if (mID != 0) {
			PhysicsManager::Instance()->UnregisterEntity(mID);
		}

	}

	unsigned long PhysicsEntity::GetId() {
		return mID;
	}
	bool PhysicsEntity::IgnoreCollisions() {
		return false;
	}

	void PhysicsEntity::Render() {
		for (auto colliders : mColliders) {
			colliders->Render();
		}
		if (mBrodPhaseCollider) {
			mBrodPhaseCollider->Render();
		}
	}

	bool PhysicsEntity::CheckCollision(PhysicsEntity* other) {
		if (IgnoreCollisions() || other->IgnoreCollisions()) {
			return false;
		}

		bool narrowPhaseCheck = false;
		if (mBrodPhaseCollider && other->mBrodPhaseCollider) {
			narrowPhaseCheck = ColliderVsColliderCheck(mBrodPhaseCollider, other->mBrodPhaseCollider);
		}

		if (narrowPhaseCheck) {
			for (int i = 0; i < mColliders.size(); i++) {
				for (int j = 0; j < other->mColliders.size(); j++) {
					if (ColliderVsColliderCheck(mColliders[i], other->mColliders[j])) {
						return true;
					}
				}
			}
		}
		
		return false;
	}

}
