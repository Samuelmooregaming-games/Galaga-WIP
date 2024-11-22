#pragma once
#include "collider.h"
#include<vector>

namespace SDLFramework{
	class PhysicsEntity : public GameEntity {
	
	public:
		PhysicsEntity();
		virtual ~PhysicsEntity();

		unsigned long GetId();

		bool CheckCollision(PhysicsEntity* other);
		
		virtual void Hit(PhysicsEntity* other) { std::cout << "a collision has happened" << std::endl; }

		virtual void Render() override;

	protected:
		

		std::vector<Collider*> mColliders;

		Collider* mBrodPhaseCollider;

		virtual bool IgnoreCollisions();
	
		unsigned long /*int*/ mID;
		void AddCollider(Collider* collider, Vector2 localpos = Vec2_Zero);
	};

}