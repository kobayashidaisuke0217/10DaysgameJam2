#pragma once
#include "Model.h"
#include "Plane.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Input.h"
class Player;
class ShadowPlane
{
public:
	void Initialize();

	void Update();
	void Draw(const ViewProjection& viewprojection, const DirectionalLight& light);
	void Finalize();

	void SetPlayer( Player* player);
	void SetViewProjection(const ViewProjection* view) { viewProjection_ = view; }
private:
	WorldTransform worldTransform_;
	const ViewProjection* viewProjection_ = nullptr;
	const WorldTransform* target_ = nullptr;
	Input* input_ = nullptr;
	Plane* plane_;
	Texturemanager* textureManager_;
	uint32_t texturehandle_;
	float offset;
	Player* player_;
private:
	void Move();
	void Rotate();
	Vector3 GetWorldPos();
};

