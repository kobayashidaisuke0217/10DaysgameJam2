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

void camera::SetPlayer(const WorldTransform* player)
{
	this->player = player;
}

void camera::Move() {
	if (target_) {

		Vector3 offset = { 0.0f, 2.0f, -280.0f };
		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewprojection_.rotation_);

		offset = TransformNormal(offset, rotateMatrix);
		viewprojection_.translation_ = Add(target_->translation_, offset);
		
	}
	

}

void camera::Rotate() {
	if (input_->PressKey(DIK_UP)) {
		const float kRotateSpeed = 0.01f;
		viewprojection_.rotation_.x += kRotateSpeed;
	}
	 if (input_->PressKey(DIK_DOWN)) {
		const float kRotateSpeed = 0.01f;
		viewprojection_.rotation_.x -= kRotateSpeed;
	}
	 if (input_->PressKey(DIK_LEFT)) {
		const float kRotateSpeed = 0.01f;
		viewprojection_.rotation_.z += kRotateSpeed;
	}
	 if (input_->PressKey(DIK_RIGHT)) {
		const float kRotateSpeed = 0.01f;
		viewprojection_.rotation_.z -= kRotateSpeed;
	}
	
	
	

}