#pragma once
#include "mathHelper.h"
#include <vector>

using namespace SDLFramework;

class BeziarPath {
public:
	BeziarPath();
	~BeziarPath();

	void AddCurve(BezierCurve curve, int samples);
	void sample(std::vector<Vector2>* sampledpath);


private:
	std::vector<BezierCurve> mcurves;
	std::vector<int> mSamples;
};