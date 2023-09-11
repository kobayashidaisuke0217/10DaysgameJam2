#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"

#pragma once

class FlytargetCamera
{
public:
	void Initialize();
	void Update();
	//void Draw();
	void Finalize();
	
	inline void SetTarget(const WorldTransform* target) {

		target_ = target;
	}
	const ViewProjection& GetViewProjection() { return viewProjection_; }
private:
	Input* input_;
	ViewProjection viewProjection_;
	
	const WorldTransform* target_ = nullptr;
};

