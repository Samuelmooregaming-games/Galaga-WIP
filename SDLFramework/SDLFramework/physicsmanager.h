#pragma once
#include<bitset>
#include"physicsentity.h"

namespace SDLFramework {
	
	class PhysicsManager {
	public:
		
		enum class CollisionLayers {
			Freindly,
			FreindlyProjectile,
			Hostile,
			HostileProjectile,
			MaxLayers
		};

		enum class CollisionFlags {
			None = 0x00,
			Friendly = 0x01,
			FriendlyProjectile = 0x02,
			Hostile = 0x04,
			HostileProjectile = 0x08
		};
		
		static PhysicsManager* Instance();
		static void Release();
		
		unsigned long RegisterEntity(PhysicsEntity* entity, CollisionLayers layer);
		void UnregisterEntity(unsigned long id);

		void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

		void Update();

	private:
		PhysicsManager();
		~PhysicsManager();

		static PhysicsManager* sInstance;
		std::vector<PhysicsEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
		std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

		unsigned long mLastID;
	};

	inline PhysicsManager::CollisionFlags operator|(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
		return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
	}
	
	inline PhysicsManager::CollisionFlags operator&(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
		return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
	}
	
}