#pragma once
#include "Model.h"
#include "Sphere.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Input.h"
class Ground
{
public:
	Ground();
	~Ground();

	void Initialize();
	void Update();
	void Draw(const ViewProjection&  viewProjection,  const DirectionalLight& light);
	void Finaleze();
	 
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
private:
	Sphere* sphere_;
	WorldTransform worldTransform_;
	uint32_t texturehandle_;
	Texturemanager* textureManager_;
	Input* input_;
	float Scale = 1.0f;
};

