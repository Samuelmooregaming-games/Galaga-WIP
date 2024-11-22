#pragma once
#include "Graphics.h"
#include "audiomanager.h"
#include"physicsmanager.h"
#include "StartScreen.h"
namespace SDLFramework {
	class GameManager {
	public:
		static GameManager* Instance();
		
		static void Release();

		GameManager();
		~GameManager();

		void Update();
		void LateUpdate();

		void Render();

		void Run();

	private:
		const int FRAME_RATE = 60;
		//How we are creating this as a Singleton
		static GameManager* sInstance;
		//Loop Control
		bool mQuit;

		//Modules
		Graphics* mGraphics;
		Timer* mTimer;
		AssetManager* mAssetManager;
		InputManager* mInputManager;
		AudioManager* mAudiomanager;
		PhysicsManager* mPhysicsManager;
		
		//startscreen
		StartScreen* mStartScreen;
		
		SDL_Event mevents;
	};
}