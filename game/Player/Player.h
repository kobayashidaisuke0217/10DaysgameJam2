#pragma once
#include "Model.h"
#include "Sphere.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Input.h"
#include "ShadowPlane.h"
#include <optional>
#include "FlytargetCamera.h"
class Player
{
public:
	void Initialize();

	void Update();
	void Draw(const ViewProjection& viewprojection, const DirectionalLight& light);
	void Finalize();

	void SetTarget(const WorldTransform* target);
	
	//const ViewProjection& GetViewProjection() { return viewprojection_; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	Vector3 GetWorldPos();
	bool GetCameraFlag() { return cameraChangeFlag; }
	StructSphere GetStructSphere() { return structSphere_; }
	void  SetCamera(FlytargetCamera* camera) { camera_ = camera; }
	void isHit() { isHit_ = true; }
	void SetReflectRotate(Vector3 rotate) { ReflectRotate_ = rotate; };
	bool GetGameOver() { return GameOverFlag; }
private:
	enum class Behavior {
		kMove,
		kFly
	};
	WorldTransform worldTransform_;
	//const ViewProjection* viewProjection_ = nullptr;
	const WorldTransform* target_ = nullptr;
	Input* input_ = nullptr;
	Model* playerModel_;

	Sphere* sphere_;
	Sphere* targetSphere_;
	Texturemanager* textureManager_;
	uint32_t texturehandle_;
	float offset;
	ShadowPlane* shadowPlane_;
	bool cameraChangeFlag;
	StructSphere structSphere_;
	Behavior behavior_ = Behavior::kMove;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
	FlytargetCamera* camera_;
	Vector3 velocity;
	bool flayFlag;
	WorldTransform targetWorldTransform_;
	bool isHit_;
	Vector3 ReflectRotate_;
	bool GameOverFlag = false;
private:
	void Move();
	void Fly();
	void BehaviorMoveInitialize();
	void BehaviorMoveUpdate();
	void BehaviorFlyInitialize();
	void BehaviorFlyUpdate();
	
};

