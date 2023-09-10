#include "FlytargetCamera.h"

void FlytargetCamera::Initialize()
{
	input_ = Input::GetInstance();
	viewProjection_.Initialize();
}

void FlytargetCamera::Update()
{
	/*viewProjection_.translation_ = player_->GetWorldTransform().translation_;
	viewProjection_.translation_.z = player_->GetWorldTransform().translation_.z - 5.0f;
	if (input_->PressKey(DIK_UP)) {
		const float kRotateSpeed = 0.01f;
		viewProjection_.rotation_.x += kRotateSpeed;
	}
	if (input_->PressKey(DIK_DOWN)) {
		const float kRotateSpeed = 0.01f;
		viewProjection_.rotation_.x -= kRotateSpeed;
	}
	if (input_->PressKey(DIK_LEFT)) {
		const float kRotateSpeed = 0.01f;
		viewProjection_.rotation_.z += kRotateSpeed;
	}
	if (input_->PressKey(DIK_RIGHT)) {
		const float kRotateSpeed = 0.01f;
		viewProjection_.rotation_.z -= kRotateSpeed;
	}*/if (input_->PressKey(DIK_UP)) {
		const float kRotateSpeed = 0.01f;
		viewProjection_.rotation_.x += kRotateSpeed;
	}
	if (input_->PressKey(DIK_DOWN)) {
		const float kRotateSpeed = 0.01f;
		viewProjection_.rotation_.x -= kRotateSpeed;
	}
	if (input_->PressKey(DIK_LEFT)) {
		const float kRotateSpeed = 0.01f;
		viewProjection_.rotation_.z += kRotateSpeed;
	}
	if (input_->PressKey(DIK_RIGHT)) {
		const float kRotateSpeed = 0.01f;
		viewProjection_.rotation_.z -= kRotateSpeed;
	}

	if (target_) {

		Vector3 offset = { 0.0f, 0.0f, -10.0f };

		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_.rotation_);

		offset = TransformNormal(offset, rotateMatrix);
		viewProjection_.translation_ = Add(target_->translation_, offset);
		viewProjection_.translation_.y += 0.5f;
	}
	viewProjection_.UpdateMatrix();
}

void FlytargetCamera::Finalize()
{
	viewProjection_.constBuff_.ReleaseAndGetAddressOf();
}
