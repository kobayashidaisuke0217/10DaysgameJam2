#include "Skydome.h"
#include <cassert>

void Skydome::Initialize() {
	model_ = Model::CreateModelFromObj("Resource", "skydome.obj");
	assert(model_);

	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
	worldTransform_.scale_ = { 500.0f,500.0f,500.0f };
}

void Skydome::Update() {
	worldTransform_.UpdateMatrix();
}

void Skydome::Draw(const ViewProjection& viewProjection, const DirectionalLight& directionalLight) {
	model_->Draw(worldTransform_, viewProjection, directionalLight);
}