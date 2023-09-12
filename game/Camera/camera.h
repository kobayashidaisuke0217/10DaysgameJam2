#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
class camera
{
public:
	void Initialize();

	void Update();
	void Finalize();
	void SetTarget(const WorldTransform* target);
	const ViewProjection& GetViewProjection() { return viewprojection_; }
	void SetPlayer(const WorldTransform* player);
private:
	ViewProjection viewprojection_;
	const WorldTransform* target_ = nullptr;
	Input* input_ = nullptr;
	const WorldTransform* player = nullptr;
private:
	void Move();
	void Rotate();
};

