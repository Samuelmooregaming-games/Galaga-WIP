#pragma once
#include "enemy.h"

class Boss : public Enemy {
public:
	Boss(int path, int index, bool challenge);
	~Boss();
	
	static void CreateDivePaths();

	void Dive(int type = 0) override;

	
	

private:
	
	static std::vector<std::vector<Vector2>> sDivePaths;

	bool mCaptureDive;
		
	Vector2 LocalFormationPosition() override;

	void HandleDiveState() override;
	void HandleDeadState() override;

	void RenderDiveState() override;
	void RenderDeadState() override;

};