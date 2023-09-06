#pragma once
#include "Model.h"
#include "Sphere.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Input.h"

class Player
{
public:
	void Initialize();

	void Update();
	void Draw(const ViewProjection& viewprojection, const DirectionalLight& light);
	void Finalize();

	void SetTarget(const WorldTransform* target);
	//const ViewProjection& GetViewProjection() { return viewprojection_; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
private:
	WorldTransform worldTransform_;
	const WorldTransform* target_ = nullptr;
	Input* input_ = nullptr;
	Sphere* sphere_;
	Texturemanager* textureManager_;
	uint32_t texturehandle_;
	float offset;
private:
	void Move();
	void Rotate();
};

