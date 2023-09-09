#pragma once
#include "Model.h"
#include "Sphere.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Ground.h"
class ObjectBale
{
public:
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewprojection,  const DirectionalLight& light);
	void Finalize();
	void SetGround( Ground* ground) { ground_ = ground; }
private:
	WorldTransform worldtransform_;
	Sphere* sphere_;
	uint32_t texturehandle_;
	Texturemanager* textureManager_;
	Ground* ground_;
private:
	void SetParent(const WorldTransform* parent);
};

