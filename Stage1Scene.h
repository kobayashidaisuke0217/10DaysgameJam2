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

class Stage1Scene : public Iscene
{
public:
	~Stage1Scene();
	void Initialize()override;
	void Update()override;

	void Draw()override;
	void Finalize()override;
private:

	BlueMoon* engine_;
	DirectXCommon* directX_;
	Texturemanager* textureManager_;
	WorldTransform worldTransform_[2];
	ViewProjection viewProjection_;
	Input* input_;
	Sphere* sphere_[2];
	Vector4 material_ = {1.0f,1.0f,1.0f,1.0f};
	DirectionalLight light_;
	uint32_t textureHandle_ = 0;

	void Draw2D();
	void Draw3D();
};

