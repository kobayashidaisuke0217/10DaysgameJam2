#pragma once
#include "Vector4.h"
#include "triangle.h"
#include "BlueMoon.h"

#include "game/Scenes/Iscene.h"
#include "Sprite.h"
#include "Sphere.h"
#include "model.h"
#include "worldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Input.h"

class Stage2Scene : public Iscene
{
public:
	~Stage2Scene();
	void Initialize()override;
	void Update()override;

	void Draw()override;
	void Finalize()override;
private:

	BlueMoon* engine_;
	DirectXCommon* directX_;
	Texturemanager* textureManager_;
	WorldTransform worldTransformWall_[6];
	WorldTransform worldTransformGoal_;
	ViewProjection viewProjection_;
	Input* input_;
	Sphere* sphere_[7];
	Vector4 material_ = { 1.0f,1.0f,1.0f,1.0f };
	DirectionalLight light_;
	uint32_t textureHandle_[2];
	int moveCount_[6];

	void Draw2D();
	void Draw3D();
};

