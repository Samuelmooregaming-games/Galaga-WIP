#pragma once
#include "StartScreen.h"
#include "backgrounstars.h"
#include "InputManager.h"
#include "playscreen.h"

class ScreenManager {
public:
	static ScreenManager* Instance();
	static void Release();
	void Update();
	void Render();
private:
	static ScreenManager* sInstance;
	ScreenManager();
	~ScreenManager();
	
	InputManager* mInput;
	BackgroundStars* mBackgroundStars;
	StartScreen* mStartScreen;
	PlayScreen* mPlayscreen;
	


	enum Screens {Start, Play, Loose};
	Screens mCurrentScreen;
};