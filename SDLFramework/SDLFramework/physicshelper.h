#pragma once
#include"box collider.h"
#include"circlecollider.h"
#include "MathHelper.h"
namespace SDLFramework{
	inline bool CircleVsCircleCollision(CircleCollider* circle1, CircleCollider* circle2) {
		return (circle1->Position() - circle2->Position()).Magnitude() < (circle1->GetRadius() + circle2->GetRadius());
			}

	inline bool BoxVsCircleCollision(BoxCollider* box, CircleCollider* circle) {
		Vector2 circlepos = circle->Position();
		float radius = circle->GetRadius();

		Vector2 quad[4];
		quad[0] = box->GetVertexPos(0);
		quad[1] = box->GetVertexPos(1);
		quad[2] = box->GetVertexPos(2);
		quad[3] = box->GetVertexPos(3);

		for (int i = 0; i < 4; i++) {
			if ((quad[i] - circlepos).Magnitude() < radius) {
				return true;
			}
		}

		if (PointToLineDistance(quad[0], quad[1], circlepos) < radius||
			PointToLineDistance(quad[0], quad[2], circlepos) < radius ||
			PointToLineDistance(quad[2], quad[3], circlepos) < radius ||
			PointToLineDistance(quad[3], quad[1], circlepos) < radius
			) {
			return true;
		} 
		
		if (PointInPolygon(quad, 4, circlepos)) {
			return true;
		}

		return false;
	}

	inline bool BoxVsBoxCollision(BoxCollider* box1, BoxCollider* box2) {
		Vector2 projaxes[4];
		projaxes[0] = (box1->GetVertexPos(0) - box1->GetVertexPos(1)).Normalized();
		projaxes[1] = (box1->GetVertexPos(0) - box1->GetVertexPos(2)).Normalized();
		projaxes[2] = (box2->GetVertexPos(0) - box2->GetVertexPos(1)).Normalized();
		projaxes[3] = (box2->GetVertexPos(0) - box2->GetVertexPos(2)).Normalized();

		float box1min = 0.0f;
		float box1max = 0.0f;
		float box2min = 0.0f;
		float box2max = 0.0f;
		float proj1 = 0.0f;
		float proj2 = 0.0f;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				proj1 = Dot(box1->GetVertexPos(j), projaxes[i]);
				proj2 = Dot(box2->GetVertexPos(j), projaxes[i]);


				if (j == 0) {
					box1min = box2max = proj1;
				} else {
					if (proj1 < box1min) {
						box1min = proj1;
					}
					if (proj1 > box1max) {
						box1max = proj1;
					}
					if (proj2 < box2min) {
						box2min = proj2;
					}
					if (proj2 > box2max) {
						box2max = proj2;
					}
				}

			}

			float halfDist1 = (box1max - box1min) * 0.5f;
			float midpoint1 = box1min + halfDist1;
			
			float halfDist2 = (box2max - box2min) * 0.5f;
			float midpoint2 = box2min + halfDist2;

			if (abs(midpoint1 - midpoint2) > (halfDist1 + halfDist2)) {
				return false;
			}
		}

		//implicitly returns true
	}

	inline bool ColliderVsColliderCheck(Collider* collider1, Collider* collider2) {
		if (collider1->GetType() == Collider::ColliderType::Circle &&
			collider2->GetType() == Collider::ColliderType::Circle) {
			return CircleVsCircleCollision(static_cast<CircleCollider*>(collider1), static_cast<CircleCollider*>(collider2));
		}
		else if (collider1->GetType() == Collider::ColliderType::Box &&
			collider2->GetType() == Collider::ColliderType::Circle) {
			return BoxVsCircleCollision(static_cast<BoxCollider*>(collider1), static_cast<CircleCollider*>(collider2));
		}
		else if (collider1->GetType() == Collider::ColliderType::Circle &&
			collider2->GetType() == Collider::ColliderType::Box) {
			return BoxVsCircleCollision(static_cast<BoxCollider*>(collider2), static_cast<CircleCollider*>(collider1));
		}

		else if (collider1->GetType() == Collider::ColliderType::Box &&
			collider2->GetType() == Collider::ColliderType::Box) {
			return BoxVsBoxCollision(static_cast<BoxCollider*>(collider1), static_cast<BoxCollider*>(collider2));
		}
		else {
			return false;
		}

	}


}
