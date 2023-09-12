#pragma once
#include "Model.h"
#include "Sphere.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Ground.h"
#include "Plane.h"
#include "Skydome.h"

class Stage5Object
{
public:
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewprojection, const DirectionalLight& light);
	void Finalize();
	void SetGround(Ground* ground) { ground_ = ground; }
	OBB GetObb(int num) { return obb_[num]; }
	OBB GetObbGoal() { return obbGoal_; }
	WorldTransform GetWorldTransform(int num) { return worldTransformWall_[num]; }
private:
	WorldTransform worldTransformWall_[8];
	WorldTransform worldTransformPlane_[2];
	WorldTransform worldTransformGoal_;
	Sphere* sphere_[9];
	Plane* plane_[2];
	uint32_t textureHandle_[3];
	Texturemanager* textureManager_;
	Ground* ground_;
	OBB obb_[8];
	OBB obbGoal_;

	Skydome skyDome_;

private:
	void SetParent(const WorldTransform* parent);
};

