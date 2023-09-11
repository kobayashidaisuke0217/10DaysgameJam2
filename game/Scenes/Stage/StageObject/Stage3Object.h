#pragma once
#include "Model.h"
#include "Sphere.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Ground.h"
#include "Plane.h"

class Stage3Object
{
public:
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewprojection, const DirectionalLight& light);
	void Finalize();
	void SetGround(Ground* ground) { ground_ = ground; }
	OBB GetObb(int num) { return obb_[num]; }
	OBB GetObbGoal() { return obbGoal_; }
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
private:
	void SetParent(const WorldTransform* parent);
};

