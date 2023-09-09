#include "Player.h"

void Player::Initialize()
{
	input_ = Input::GetInstance();
	sphere_ = new Sphere();
	sphere_->Initialize();
	textureManager_ = Texturemanager::GetInstance();
	texturehandle_ = textureManager_->Load("Resource/wi.png");
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 4.0f,4.0f,4.0f };
	 //offset =  25.3f;
	offset = 61.0f;
	 shadowPlane_ = new ShadowPlane();
	 shadowPlane_->Initialize();
	 shadowPlane_->SetPlayer(this);
	 cameraChangeFlag = false;
}

void Player::Update()
{
	if (input_->PressKey(DIK_RETURN)) {
		cameraChangeFlag = true;
	}
	else {
		cameraChangeFlag = false;
	}
	 Move();
	
	worldTransform_.UpdateMatrix();
	shadowPlane_->Update();
}

void Player::Draw(const ViewProjection& viewprojection, const DirectionalLight& light)
{
	sphere_->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransform_, texturehandle_, viewprojection, light);
	shadowPlane_->Draw(viewprojection, light);
}

void Player::Finalize()
{
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
		Vector3 VecOffset = { offset,offset,offset };
		

		Matrix4x4 rotateMatrix = MakeRotateMatrix(worldTransform_.rotation_);

		VecOffset = TransformNormal(VecOffset, rotateMatrix);
		worldTransform_.translation_ = Add(target_->translation_, VecOffset);
		ImGui::Begin("player");
		ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.1f);
		ImGui::DragFloat3("rot", &worldTransform_.rotation_.x, 0.1f);
		ImGui::End();
	}
}


void Player::Rotate()
{

	
}

Vector3 Player::GetWorldPos()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
