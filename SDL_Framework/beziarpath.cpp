#include "beziarpath.h"

BeziarPath::BeziarPath() { }

BeziarPath::~BeziarPath() { }

void BeziarPath::AddCurve(BezierCurve curve, int samples) {
	mcurves.push_back(curve); 
	mSamples.push_back(samples);
}

void BeziarPath::sample(std::vector<Vector2>* sampledpath) {
	for (int i = 0; i < mcurves.size(); i++) {
		for (float t = 0.0f; t <= 1.0f; t += (1.0f / mSamples[i])) {
			sampledpath->push_back(mcurves[i].CalculatePointAlongCurve(t));
		}
	}
}
