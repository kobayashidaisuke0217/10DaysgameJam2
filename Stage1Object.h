#pragma once
#include "Model.h"
#include "Sphere.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Ground.h"

class Stage1Object
{
public:
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewprojection, const DirectionalLight& light);
	void Finalize();
	void SetGround(Ground* ground) { ground_ = ground; }
private:
	WorldTransform worldTransformWall_[6];
	WorldTransform worldTransformGoal_;
	Sphere* sphere_[7];
	uint32_t textureHandle_[2];
	Texturemanager* textureManager_;
	Ground* ground_;
private:
	void SetParent(const WorldTransform* parent);
};
