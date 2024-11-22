#include "inputmanager.h"
#include <string>
namespace SDLFramework {
	InputManager* InputManager::sInstance = nullptr;

	InputManager* InputManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new InputManager();
		}
		return sInstance;
	}
	void InputManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	bool InputManager::KeyDown(SDL_Scancode scancode) {
		return mKeyboardState[scancode];
	}
	bool InputManager::KeyPressed(SDL_Scancode scancode) {
		return !mPrevkeyboardState[scancode] && mKeyboardState[scancode];

	}
	bool InputManager::KeyReleased(SDL_Scancode scancode) {
		return mPrevkeyboardState[scancode] && !mKeyboardState[scancode];
	}
	bool InputManager::MouseButtonDown(MouseButton button) {
		Uint32 mask = 0;

		switch (button)
		{
		case Left:
			mask = SDL_BUTTON_LMASK;
			break;

		case Right:
			mask = SDL_BUTTON_RMASK;
			break;
		}
		
		return (mMouseState & mask) != 0;
	}
	bool InputManager::MouseButtonPressed(MouseButton button) {
		Uint32 mask = 0;

		switch (button)
		{
		case Left:
			mask = SDL_BUTTON_LMASK;
			break;

		case Right:
			mask = SDL_BUTTON_RMASK;
			break;
		}

		return !(mPrevMouseState & mask) && (mMouseState & mask);
	}
	bool InputManager::MouseButtonReleased(MouseButton button) {
		Uint32 mask = 0;

		switch (button)
		{
		case Left:
			mask = SDL_BUTTON_LMASK;
			break;

		case Right:
			mask = SDL_BUTTON_RMASK;
			break;
		}

		return (mPrevMouseState & mask) && !(mMouseState & mask);
	}

	Vector2 InputManager::MousePosition() {
		return Vector2((float)mMouseXpos, (float)mMouseYpos);
	}

	

	void InputManager::UpdatePrevInput() {
		memcpy(mPrevkeyboardState, mKeyboardState, mKeyLength);
		mPrevMouseState = mMouseState;
	}

	InputManager::InputManager() {
		mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
		mPrevkeyboardState = new Uint8[mKeyLength];
		memcpy(mPrevkeyboardState, mKeyboardState, mKeyLength);
	}
	
	InputManager::~InputManager() {
		delete[] mPrevkeyboardState;
		mPrevkeyboardState = nullptr;
	}
	void InputManager::Update() {
		mMouseState = SDL_GetMouseState(&mMouseXpos, &mMouseYpos);
		mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
}

}
