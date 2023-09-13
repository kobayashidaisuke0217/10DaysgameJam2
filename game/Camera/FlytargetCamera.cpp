#include "FlytargetCamera.h"

void FlytargetCamera::Initialize()
{
	input_ = Input::GetInstance();
	viewProjection_.Initialize();
	viewProjection_.rotation_ = { -6.52f,0.0f,-12.56f };
	viewProjection_.translation_ = { 18.286f,35.763f,-105.097f };
}

void FlytargetCamera::Update()
{
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
	}

	if (target_) {

		Vector3 offset = { 0.0f, 0.0f, -10.0f };

		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_.rotation_);

		offset = TransformNormal(offset, rotateMatrix);
		viewProjection_.translation_ = Add(target_->translation_, offset);
		viewProjection_.translation_.y += 0.5f;
	}
	ImGui::Begin("camera");
	ImGui::DragFloat3("rot", &viewProjection_.rotation_.x, 0.1f);
	ImGui::DragFloat3("rot", &viewProjection_.translation_.x, 0.1f);
	ImGui::End();
	viewProjection_.UpdateMatrix();
}

void FlytargetCamera::Finalize()
{
	viewProjection_.constBuff_.ReleaseAndGetAddressOf();
}
