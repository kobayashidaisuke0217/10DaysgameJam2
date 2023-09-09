#pragma once
#include "Model.h"
#include "Sphere.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Input.h"
#include "ShadowPlane.h"
#include <optional>
class Player
{
public:
	void Initialize();

	void Update();
	void Draw(const ViewProjection& viewprojection, const DirectionalLight& light);
	void Finalize();

	void SetTarget(const WorldTransform* target);
	void SetViewProjection(const ViewProjection* view) { viewProjection_ = view; }
	//const ViewProjection& GetViewProjection() { return viewprojection_; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	Vector3 GetWorldPos();
	bool GetCameraFlag() { return cameraChangeFlag; }

	void BehaviorRootInitialize();
	void BehaviorRootUpdate();

private:
	enum class Behavior {
		kMove,
		kFly
	};

	Behavior behavior_ = Behavior::kMove;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	WorldTransform worldTransform_;
	const ViewProjection* viewProjection_ = nullptr;
	const WorldTransform* target_ = nullptr;
	Input* input_ = nullptr;
	Sphere* sphere_;
	Texturemanager* textureManager_;
	uint32_t texturehandle_;
	float offset;
	ShadowPlane* shadowPlane_;
	bool cameraChangeFlag;
private:
	void Move();
	void Rotate();
	
};

