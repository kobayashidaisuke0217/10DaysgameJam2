#include "Player.h"

void Player::Initialize()
{
	input_ = Input::GetInstance();
	sphere_ = new Sphere();
	sphere_->Initialize();
	textureManager_ = Texturemanager::GetInstance();
	texturehandle_ = textureManager_->Load("Resource/Black.png");
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 2.0f,2.0f,2.0f };
	 offset =  25.3f;
	
}

void Player::Update()
{
	 Move();
	
	worldTransform_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewprojection, const DirectionalLight& light)
{
	sphere_->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransform_, texturehandle_, viewprojection, light);
}

void Player::Finalize()
{
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

	/*if (input_->PressKey(DIK_A)) {
		const float kRotateSpeed = 0.01f;
		worldTransform_.rotation_.y +=  kRotateSpeed;
	}
	if (input_->PressKey(DIK_D)) {
		const float kRotateSpeed = 0.01f;
		worldTransform_.rotation_.y -= kRotateSpeed;
	}
	if (input_->PressKey(DIK_S)) {
		const float kRotateSpeed = 0.01f;
		worldTransform_.rotation_.x += kRotateSpeed;
	}
	if (input_->PressKey(DIK_W)) {
		const float kRotateSpeed = 0.01f;
		worldTransform_.rotation_.x -= kRotateSpeed;
	}*/
}
