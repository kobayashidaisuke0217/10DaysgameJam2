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

private:
	ViewProjection viewprojection_;
	const WorldTransform* target_ = nullptr;
	Input* input_ = nullptr;

private:
	void Move();
	void Rotate();
};

