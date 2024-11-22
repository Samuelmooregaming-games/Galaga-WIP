#include"box collider.h"

namespace SDLFramework {

	BoxCollider::BoxCollider(Vector2 size) : Collider(ColliderType::Box) {
		AddVert(0, Vector2(-0.5f * size.x, -0.5f * size.y));
		AddVert(1, Vector2(0.5f * size.x, -0.5f * size.y));
		AddVert(2, Vector2(-0.5f * size.x, 0.5f * size.y));
		AddVert(3, Vector2(0.5f * size.x, 0.5f * size.y));
		
		if (DEBUG_COLLIDERS) {
			SetDebugTexture(new texture("boxcollider.png"));
			mDEbugTexture->Scale(size);
		}

	}

	BoxCollider::~BoxCollider() {
		for(auto vert: mVerts){
			delete vert;
			vert = nullptr;
		}

	}

	Vector2 BoxCollider::GetFurthestPoint() {
		Vector2 localpos = Position(GameEntity::Local);
		int furthestindex = 0;
		float dist = (localpos + mVerts[0]->Position(GameEntity::Local)).Magnitude();
		float otherdist = 0.0f;

		for (int i = 0; i < MAX_VERTS; i++) {
			otherdist = (localpos + mVerts[i]->Position(GameEntity::Local)).Magnitude();
		
			if (otherdist > dist) {
				furthestindex = i;
				dist = otherdist;
		}
	}

		return localpos + mVerts[furthestindex]->Position(GameEntity::Local);
}

	Vector2 BoxCollider::GetVertexPos(int index) {
		return mVerts[index]->Position();
	}

	void BoxCollider::AddVert(int index, Vector2 pos) {
		mVerts[index] = new GameEntity(pos);
		mVerts[index]->Parent(this);
	}

	
}