#include "texture.h"

namespace SDLFramework {
	texture::texture(std::string filename, bool managed) {
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetTexture(filename, managed);
		mRedShip = AssetManager::Instance()->GetTexture(filename, managed);
		SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);
		SDL_QueryTexture(mRedShip, nullptr, nullptr, &mWidth, &mHeight);
		mClipped = false;
		mDestinationRect.w = mWidth;
		mDestinationRect.h = mHeight;
	}

	texture::texture(std::string filename, int x, int y, int width, int height, bool managed) {
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetTexture(filename, managed);
		mRedShip = AssetManager::Instance()->GetTexture(filename, managed);
		mWidth = width;
		mHeight = height;

		mClipped = true;

		mDestinationRect.x = mWidth;
		mDestinationRect.y = mHeight;

		mSourceRect.x = x;
		mSourceRect.y = y;
		mSourceRect.w = width;
		mSourceRect.h = height;
	}
	texture::texture(std::string text, std::string fontpath, int size, SDL_Color color, bool managed){ 
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetText(text, fontpath, size, color, managed);

		mClipped = false;

		SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);

		mDestinationRect.w = mWidth;
		mDestinationRect.h = mHeight;
	}

	texture::~texture() {
		AssetManager::Instance()->DestroyTexture(mTex);
		mTex = nullptr;
		mRedShip = nullptr;
		mGraphics = nullptr;
		
	
}

	Vector2 texture::ScaledDimentions() {
		Vector2 ScaledDimentions = Scale();
		ScaledDimentions.x *= mWidth;
		ScaledDimentions.y *= mHeight;

		return ScaledDimentions;
	}

	void texture::SetSourceRect(SDL_Rect* sourcerect) {
		mSourceRect = *sourcerect;
	}

	void texture::Render() {
		Vector2 pos = Position(World);
		Vector2 scale = Scale(World);

		mDestinationRect.x = (int)(pos.x - mWidth * 0.5f);
		mDestinationRect.y = (int)(pos.y - mHeight * 0.5f);
		mDestinationRect.w = (int)(mWidth * scale.x);
		mDestinationRect.h = (int)(mHeight * scale.y);

		mGraphics->DrawTexture(mTex, mClipped ? &mSourceRect : nullptr, &mDestinationRect, Rotation(World));
		mGraphics->DrawTexture(mRedShip, mClipped ? &mSourceRect : nullptr, &mDestinationRect, Rotation(World));
	}
}