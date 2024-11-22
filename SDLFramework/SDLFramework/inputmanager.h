#pragma once
#include<SDL.h>
#include"MathHelper.h"
namespace SDLFramework {
	class InputManager 
	{
	private:
		static InputManager* sInstance;
		
		const Uint8* mKeyboardState;
		
		Uint8* mPrevkeyboardState;
		int mKeyLength;
		
		Uint32 mPrevMouseState;
		Uint32 mMouseState;
		
		
		

		int mMouseXpos;
		int mMouseYpos;
		InputManager();
		~InputManager();

	public:
		enum MouseButton {Left = 0, Right};
		bool MouseButtonDown(MouseButton button);
		bool MouseButtonPressed(MouseButton button);
		bool MouseButtonReleased(MouseButton button);
static InputManager* Instance();
		Vector2 MousePosition();
		

		static void Release();
		bool KeyDown(SDL_Scancode scancode);
		bool KeyPressed(SDL_Scancode scancode);
		bool KeyReleased(SDL_Scancode scancode);

		
		void Update();
		void UpdatePrevInput();
		
		
	

		
	};
}
