#include "camera.h"
void camera::Initialize() {
	viewprojection_.Initialize();
	input_ = Input::GetInstance();

}

void camera::Update() {

	Move();
	Rotate();
	viewprojection_.UpdateViewMatrix();
	//viewprojection_.TransferMatrix();
}

void camera::Finalize()
{
	viewprojection_.constBuff_.ReleaseAndGetAddressOf();
}

void camera::SetTarget(const WorldTransform* target) {

	target_ = target;
}

void camera::Move() {
	if (target_) {

		Vector3 offset = { 30.0f, 30.0f, 30.0f };

		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewprojection_.rotation_);

		offset = TransformNormal(offset, rotateMatrix);
		viewprojection_.translation_ = Add(target_->translation_, offset);
		
	}
	ImGui::Begin("camera");
	ImGui::DragFloat3("pos", &viewprojection_.translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &viewprojection_.rotation_.x, 0.1f);
	ImGui::End();
}

void camera::Rotate() {
	if (input_->PressKey(DIK_UP)) {
		const float kRotateSpeed = 0.1f;
		viewprojection_.rotation_.y += kRotateSpeed;
	}
	if (input_->PressKey(DIK_DOWN)) {
		const float kRotateSpeed = 0.1f;
		viewprojection_.rotation_.y -= kRotateSpeed;
	}
	if (input_->PressKey(DIK_LEFT)) {
		const float kRotateSpeed = 0.1f;
		viewprojection_.rotation_.x += kRotateSpeed;
	}
	if (input_->PressKey(DIK_RIGHT)) {
		const float kRotateSpeed = 0.1f;
		viewprojection_.rotation_.x -= kRotateSpeed;
	}
	
	


}