#pragma once
#include "AnimatedTexture.h"

using namespace SDLFramework;

class CaptureBeam : public AnimatedTexture {
private:
float mTotalCaptureTime;
float mCaptureTimer;

	void RunAnimation() override;
	


public:
	CaptureBeam();
	~CaptureBeam();

	void ResetAnimation() override;
	void Render() override;
};