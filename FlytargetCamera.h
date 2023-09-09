#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "Player.h"
#pragma once

class FlytargetCamera
{
public:
	void Initialize();
	void Update();
	//void Draw();
	void Setplayer( Player* player) { player_ = player; }
	const ViewProjection& GetViewProjection() { return viewProjection_; }
private:
	Input* input_;
	ViewProjection viewProjection_;
	Player* player_;
};

