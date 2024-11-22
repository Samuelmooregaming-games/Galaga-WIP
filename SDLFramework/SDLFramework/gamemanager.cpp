#include "gamemanager.h"

namespace SDLFramework {
    GameManager* GameManager::sInstance = nullptr;

    GameManager* GameManager::Instance() {
        if (sInstance == nullptr) {
            sInstance = new GameManager();
        }

        return sInstance;
    }

    void GameManager::Release() {
        delete sInstance;
        sInstance = nullptr;
    }

    void GameManager::Run() {
        //Main Game Loop
        while (!mQuit) {
            mTimer->Update();
            //Event Polling Loop
            //While there are events inside of our events varaible...
            while (SDL_PollEvent(&mevents)) {
                //Handle each and every event we want to look for
                switch (mevents.type) {
                case SDL_QUIT:
                    mQuit = true;
                    break;
                }
            }

            if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
                mTimer->Reset();
                Update();
                LateUpdate();
                Render();
            }
        }
    }

    void GameManager::Update() {
        mInputManager->Update();
 
        if (mInputManager->KeyDown(SDL_SCANCODE_I)) {
           
            
            
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_K)) {
         
        }  
        if (mInputManager->KeyDown(SDL_SCANCODE_J)) {
          
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_L)) {
            
        } if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
           
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_S)) {
           
        }
        if (mInputManager->KeyDown(SDL_SCANCODE_A)) {
           
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_D)) {
           
        }
        if (mInputManager->KeyDown(SDL_SCANCODE_Q)) {
       
        } 
        else if (mInputManager->KeyDown(SDL_SCANCODE_E)) {
           
        }
        if (mInputManager->KeyDown(SDL_SCANCODE_Z)) {
           
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_C)) {
           
        }
        if (mInputManager->KeyPressed(SDL_SCANCODE_SPACE)) {
           
        }
       
        
       
        
        //std::cout << "Delta Time: " << mTimer->DeltaTime() << std::endl;
    }

    void GameManager::LateUpdate() {
        mPhysicsManager->Update();
        mInputManager->UpdatePrevInput();
    }

    void GameManager::Render() {
        mGraphics->ClearBackBuffer();
       
       
    
       
        mGraphics->Render();
      
    }

    GameManager::GameManager() : mQuit(false) {
        //calling to our Graphics Singleton
        mGraphics = Graphics::Instance();


        if (!Graphics::Initialized()) {
            mQuit = true;
        }
        mTimer = Timer::Instance();
        mAssetManager = AssetManager::Instance();
        mInputManager = InputManager::Instance();
        mAudiomanager = AudioManager::Instance();
        mPhysicsManager = PhysicsManager::Instance();

        //physics layers
        mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Freindly,
            PhysicsManager::CollisionFlags::Hostile |
            PhysicsManager::CollisionFlags::HostileProjectile);

        mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile,
            PhysicsManager::CollisionFlags::Friendly |
            PhysicsManager::CollisionFlags::FriendlyProjectile);

        mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FreindlyProjectile,
            PhysicsManager::CollisionFlags::Friendly |
            PhysicsManager::CollisionFlags::Hostile);

        mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectile,
            PhysicsManager::CollisionFlags::Hostile |
            PhysicsManager::CollisionFlags::Friendly);


        //challenges 2 -> finnish setting up collision layers (friendly projectiles, hostile projectiles)

        //Initialize all other modules
        mTimer = Timer::Instance();
       

       


       
    }

    GameManager::~GameManager() {
       

        //Release Modules
        Graphics::Release();
        mGraphics = nullptr;

        Timer::Release();
        mTimer = nullptr;

        AssetManager::Release();
        mAssetManager = nullptr;
        InputManager::Release();
        mInputManager = nullptr;
        AudioManager::Release();
        mAudiomanager = nullptr;
        PhysicsManager::Release();
        mPhysicsManager = nullptr;
        //Quit SDl Subsystems
        SDL_Quit();
    }
    //Namespace bracket is below
    }