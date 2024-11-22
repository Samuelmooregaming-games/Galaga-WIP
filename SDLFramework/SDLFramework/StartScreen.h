#pragma once
#include "animatedtexture.h"
#include "inputmanager.h"

using namespace SDLFramework;

	class StartScreen : public GameEntity {
	public:
		StartScreen();
		~StartScreen();

		void Update() override;
		void Render() override;

	private:
		Timer* mtimer;
		InputManager* minputmanager;
		 
		//top bar
		GameEntity* mTopbar;
		texture* mPlayerone;
		texture* mPlayertwo;
		texture* mHighScore;
		
		//logo
		texture* mLogo;
		AnimatedTexture* mAnimatedLogo;
	};