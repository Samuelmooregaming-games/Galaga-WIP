#include"collider.h"


namespace SDLFramework {
	Collider::Collider(ColliderType type) : mType(type) {
		mDEbugTexture = nullptr;
	}

	Collider::~Collider() {
		delete mDEbugTexture;
		mDEbugTexture = nullptr;
	}

	void Collider::Render() {
		if (DEBUG_COLLIDERS /*== true*/) {
			mDEbugTexture->Render();
		}
	}

	Collider::ColliderType Collider::GetType() {
		return mType;
	}

	void Collider::SetDebugTexture(texture* tex) {
		delete mDEbugTexture;
		mDEbugTexture = tex;
		mDEbugTexture->Parent(this);
	}
}