#pragma once
#include "Model.h"
#include "Sphere.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Ground.h"
#include "Plane.h"
#include "Skydome.h"

class Stage4Object
{
public:
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewprojection, const DirectionalLight& light);
	void Finalize();
	void SetGround(Ground* ground) { ground_ = ground; }
	OBB GetObb(int num) { return obb_[num]; }
	OBB GetObbGoal() { return obbGoal_; }
	void ishit(int num) { ishit_[num] = true; }
	WorldTransform GetWorldTransform(int num) { return worldTransformWall_[num]; }
private:
	WorldTransform worldTransformWall_[8];
	WorldTransform worldTransformPlane_;
	WorldTransform worldTransformGoal_;
	Sphere* sphere_[9];
	Plane* plane_;
	uint32_t textureHandle_[3];
	Texturemanager* textureManager_;
	Ground* ground_;
	OBB obb_[8];
	OBB obbGoal_;
	bool ishit_[8];

	Skydome skyDome_;

private:
	void SetParent(const WorldTransform* parent);
};

