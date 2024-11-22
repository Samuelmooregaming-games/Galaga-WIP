#include "assetmanager.h"

namespace SDLFramework {
	AssetManager* AssetManager::sInstance = nullptr;

	AssetManager* AssetManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new AssetManager();
		}
		return sInstance;
	}
	void AssetManager::Release() {
		delete sInstance;
	sInstance = nullptr;
		}

	AssetManager::AssetManager() {

	}
	
	AssetManager::~AssetManager() {
		for (auto tex : mTextures) {
			if (tex.second != nullptr) {
				SDL_DestroyTexture(tex.second);
			}
		}

		mTextures.clear();
	}
	SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color, bool managed) {
		std::stringstream ss;

		ss << size << (int)color.r << (int)color.g << (int)color.b;
		std::string key = text + filename + ss.str();

		if (mTextures[key] == nullptr) {
			TTF_Font* font = GetFont(filename, size);
			mTextures[key] = Graphics::Instance()->Create_Text_Texture(font, text, color);
		}

		if (mTextures[key] != nullptr && managed) {
			mTextureRefCount[mTextures[key]] += 1;
		}
		return mTextures[key];
	}



	SDL_Texture* AssetManager::GetTexture(std::string fileName, bool managed) {
		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Assets/" + fileName);

		if (mTextures[fullpath] == nullptr) {
			mTextures[fullpath] = Graphics::Instance()->LoadTexture(fullpath);
		}

		if (mTextures[fullpath] != nullptr && managed) {
			mTextureRefCount[mTextures[fullpath]] += 1;
		}

		return mTextures[fullpath];
	}
	TTF_Font* AssetManager::GetFont(std::string filename, int size) {
		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Assets/" + filename);

		std::stringstream ss;
		ss << size;
		std::string key = fullpath + ss.str();

		if (mFonts[key] == nullptr) {
			mFonts[key] = TTF_OpenFont(fullpath.c_str(), size);
			if (mFonts[key] == nullptr) {
				std::cerr << " unable to load font " << filename << "ttf_error: " << TTF_GetError() << std::endl;
				return nullptr;
			}
			return mFonts[key];
		}
	}

	Mix_Music* AssetManager::GetMusic(std::string filename, bool managed)
	{
		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Assets/Audio" + filename);

		if (mMusic[fullpath] == nullptr) {
			mMusic[fullpath] = Mix_LoadMUS(fullpath.c_str());
		}

		if (mMusic[fullpath] == nullptr) {
			std::cerr << "unable to load music " << "! mix error" << Mix_GetError() << std::endl;
		}
		else if (managed) {
			mMusicRefCount[mMusic[fullpath]] += 1;
		}
		return mMusic[fullpath];
	}
	Mix_Chunk* AssetManager::GetSFX(std::string filename, bool managed)
	{
		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Assets/Audio/SFX/" + filename);

		if (mSFX[fullpath] == nullptr) {
			mSFX[fullpath] = Mix_LoadWAV(fullpath.c_str());
		}

		if (mSFX[fullpath] == nullptr) {
			std::cerr << "unable to load sfx " << "! mix error" << Mix_GetError() << std::endl;
			return nullptr;
		}
		else if (managed) {
			mSFXRefCount[mSFX[fullpath]] += 1;
		}
		return mSFX[fullpath];
	}

	void AssetManager::DestroyMusic(Mix_Music* music) {
		std::map<Mix_Music*, unsigned>::iterator it = mMusicRefCount.find(music);
		if (it != mMusicRefCount.end()) {
			it->second -= 1;
	}
		if (it->second == 0) {
			UnloadMusic(it->first);
			mMusicRefCount.erase(it->first);
		}
		else {
			UnloadMusic(music);
		}
	}

	void AssetManager::DestroySFX(Mix_Chunk* sfx) {
		std::map<Mix_Chunk*, unsigned>::iterator it = mSFXRefCount.find(sfx);
		if (it != mSFXRefCount.end()) {
			it->second -= 1;
		}
		
		if (it->second == 0) {
			UnloadSFX(it->first);
			mSFXRefCount.erase(it->first);
		}
		else {
			UnloadSFX(sfx);
		}
	}

	void AssetManager::UnloadMusic(Mix_Music* music)
	{
		bool found = false;
		std::string key;
		std::map<std::string, Mix_Music*>::iterator it;

		for (it = mMusic.begin(); it != mMusic.end() && !found; it++);
		if ((found = it->second == music)) {
			Mix_FreeMusic(it->second);
			key = it->first;
			
			if (found) {
			mMusic.erase(key);
		}
		
		}
	}
	void AssetManager::UnloadSFX(Mix_Chunk* sfx)
	{
		bool found = false;
		std::string key;
		std::map<std::string, Mix_Chunk*>::iterator it;

		for (it = mSFX.begin(); it != mSFX.end() && !found; it++);
		if ((found = it->second == sfx)) {
			Mix_FreeChunk(it->second);
			key = it->first;

			if (found) {
				mSFX.erase(key);
			}
	}

	}

	void AssetManager::DestroyTexture(SDL_Texture* texture) {
		std::map<SDL_Texture*, unsigned>::iterator it = mTextureRefCount.find(texture);
	
		if (it != mTextureRefCount.end()) {
			it->second -= 1;
			if (it->second == 0) {
				UnloadTexture(it->first);
				mTextureRefCount.erase(it->first);
			}
		}
		else {
			UnloadTexture(texture);
		}
	}

	void AssetManager::UnloadTexture(SDL_Texture* texture) {
		bool found = false;
		std::string key;
		std::map<std::string, SDL_Texture*>::iterator it;
	
		for (it = mTextures.begin(); it != mTextures.end() && !found; it++) {
			if ((found = it->second == texture)) {
				SDL_DestroyTexture(it->second);
				key = it->first;
			}
		}
		if (found) {
			mTextures.erase(key);
		}
	}
	
}