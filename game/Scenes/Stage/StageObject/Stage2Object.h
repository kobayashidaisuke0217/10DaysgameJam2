#pragma once
#include "Model.h"
#include "Sphere.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Ground.h"

class Stage2Object
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
	WorldTransform worldTransformWall_[6];
	WorldTransform worldTransformGoal_;
	Sphere* sphere_[7];
	uint32_t textureHandle_[2];
	Texturemanager* textureManager_;
	Ground* ground_;
	int moveCount_[4];
	OBB obb_[6];
	OBB obbGoal_;
private:
	void SetParent(const WorldTransform* parent);


};

