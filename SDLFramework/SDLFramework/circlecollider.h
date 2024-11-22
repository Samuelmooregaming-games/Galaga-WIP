#pragma once
#include"collider.h"

namespace SDLFramework {
	class CircleCollider : public Collider {
	public:
		CircleCollider(float radius, bool brodphase = false);
		~CircleCollider();

		Vector2 GetFurthestPoint() override;

		float GetRadius();

	private:
		float mRadius;
	};
}