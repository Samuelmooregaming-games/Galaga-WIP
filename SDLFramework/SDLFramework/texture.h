#pragma once
#include "GameEntity.h"
#include "assetmanager.h"

namespace SDLFramework {
	class texture : public GameEntity {
	public:
		texture(std::string filename, bool managed = false);
		texture(std::string filename, int x, int y, int width, int height, bool managed = false);
		texture(std::string text, std::string fontpath, int size, SDL_Color color, bool managed = false);
		~texture();
		
		Vector2 ScaledDimentions();

		void SetSourceRect(SDL_Rect* SourceRect);
		
		void Render() override;

	protected:
		SDL_Texture* mTex;
		Graphics* mGraphics;
		SDL_Texture* mRedShip;
		int mWidth;
		int mHeight;

		bool mClipped;
		SDL_Rect mSourceRect;
		SDL_Rect mDestinationRect;
	};
}