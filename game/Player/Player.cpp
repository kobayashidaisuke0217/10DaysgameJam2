#include "Player.h"

void Player::Initialize()
{
	input_ = Input::GetInstance();
	sphere_ = new Sphere();
	sphere_->Initialize();
	targetSphere_ = new Sphere();
	targetSphere_->Initialize();
	textureManager_ = Texturemanager::GetInstance();
	texturehandle_ = textureManager_->Load("Resource/wi.png");
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 5.0f,5.0f,5.0f };
	worldTransform_.translation_ = { 1.0f,1.0f,1.0f };
	offset = 61.0f;
	shadowPlane_ = new ShadowPlane();
	shadowPlane_->Initialize();
	shadowPlane_->SetPlayer(this);
	cameraChangeFlag = false;
	behaviorRequest_ = Behavior::kMove;
	velocity = { 0.0f,0.0f,0.0f };
	flayFlag = false;
	targetWorldTransform_.Initialize();
	targetWorldTransform_.scale_ = { 4.0f,4.0f,4.0f };
	// BehaviorMoveInitialize();
	playerModel_ = Model::CreateModelFromObj("Resource", "Player.obj");
	GameOverFlag = false;
}

void Player::Update()
{
	structSphere_.center = worldTransform_.GetWorldPos();
	structSphere_.radius = 3.0f;

	float length = Length(Distance(worldTransform_.GetWorldPos(), { target_->matWorld_.m[3][0],target_->matWorld_.m[3][1],target_->matWorld_.m[3][2] }));
	if (length >= 15000.0f && behavior_ == Behavior::kFly) {
		GameOverFlag = true;
	}
	ImGui::Begin("player");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat("distance", &length, 0.1f);
	ImGui::End();
	if (behaviorRequest_) {
		behavior_ = behaviorRequest_.value();

		switch (behavior_) {
		case Behavior::kMove:
		default:
			BehaviorMoveInitialize();
			break;

		case Behavior::kFly:
			BehaviorFlyInitialize();
			break;
		}
		behaviorRequest_ = std::nullopt;
	}
	switch (behavior_) {
	case Behavior::kMove:
	default:
		BehaviorMoveUpdate();
		break;
	case Behavior::kFly:
		BehaviorFlyUpdate();
		break;
	}

	targetWorldTransform_.UpdateMatrix();
	worldTransform_.UpdateMatrix();
	shadowPlane_->Update();
}

void Player::Draw(const ViewProjection& viewprojection, const DirectionalLight& light)
{
	if (cameraChangeFlag == false) {
		sphere_->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransform_, texturehandle_, viewprojection, light);
		playerModel_->Draw(worldTransform_, viewprojection, light);
	}
	else {
		targetSphere_->Draw({ 1.0f,1.0f,1.0f,1.0f }, targetWorldTransform_, texturehandle_, viewprojection, light);
	}

	switch (behavior_) {
	case Behavior::kMove:
		shadowPlane_->Draw(viewprojection, light);
		break;
	case Behavior::kFly:

		break;
	}
}

void Player::Finalize()
{
	delete playerModel_;
	delete targetSphere_;
	targetWorldTransform_.constBuff_.ReleaseAndGetAddressOf();
	shadowPlane_->Finalize();
	delete sphere_;
	worldTransform_.constBuff_.ReleaseAndGetAddressOf();
}

void Player::SetTarget(const WorldTransform* target)
{
	target_ = target;
}

void Player::Move()
{

	if (target_) {
		/*	worldTransform_.rotation_ = Subtract({ target_->matWorld_.m[3][0],target_->matWorld_.m[3][1],target_->matWorld_.m[3][2] }, worldTransform_.GetWorldPos());
			worldTransform_.rotation_ = Normalise(worldTransform_.rotation_);*/


	}
}


void Player::Fly()
{
	const float KBulletSped = 1.0f;
	velocity = { 0.0f, 0.0f, KBulletSped };

	velocity = Subtract(GetWorldPos(),
		camera_->GetViewProjection().translation_);
	velocity = Multiply(KBulletSped, Normalise(velocity));
	flayFlag = true;
	cameraChangeFlag = false;
}

void Player::BehaviorMoveInitialize()
{
	cameraChangeFlag = false;
	Vector3 VecOffset = { offset,offset,offset };
	worldTransform_.rotation_ = { 0.5f,2.6f,-0.5f };

	Matrix4x4 rotateMatrix = MakeRotateMatrix(worldTransform_.rotation_);

	VecOffset = TransformNormal(VecOffset, rotateMatrix);
	worldTransform_.translation_ = Add(target_->translation_, VecOffset);

}

void Player::BehaviorMoveUpdate()
{
	if (input_->PushKey(DIK_RETURN)) { behaviorRequest_ = Behavior::kFly; }
	Move();
}

void Player::BehaviorFlyInitialize()
{
	cameraChangeFlag = true;
}

void Player::BehaviorFlyUpdate()
{
	if (flayFlag == false) {
		if (input_->PushKey(DIK_RETURN)) { behaviorRequest_ = Behavior::kMove; }
	}
	if (input_->PushKey(DIK_R)) {
		Fly();
	}
	if (flayFlag == true) {
		if (isHit_ == true) {
			const float KBulletSped = 1.0f;
			//velocity = Multiply(-1.0f, velocity);
			velocity = Reflect(velocity, ReflectRotate_);
			velocity = Normalise(velocity);
			velocity = velocity * 1.0f;
			isHit_ = false;
		}
		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);

	}

	const float KBulletSped = 50.0f;
	Vector3  velocitytarget = { 0.0f, 0.0f, KBulletSped };

	velocitytarget = Subtract(GetWorldPos(),
		camera_->GetViewProjection().translation_);
	velocitytarget = Multiply(KBulletSped, Normalise(velocitytarget));


	targetWorldTransform_.translation_ = Add(worldTransform_.translation_, velocitytarget);
	ImGui::Begin("ret");
	ImGui::DragFloat3("", &targetWorldTransform_.translation_.x);
	ImGui::End();
}

Vector3 Player::GetWorldPos()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
