#include "Ground.h"


Ground::Ground() {

	}

Ground::~Ground()
{
}

void Ground::Initialize()
{
	sphere_ = new Sphere();
	sphere_->Initialize();
	worldTransform_.Initialize();
	textureManager_ = Texturemanager::GetInstance();
	texturehandle_ =textureManager_ ->Load("Resource/uvChecker.png");
	worldTransform_.scale_ = { 42.0f,42.0f,42.0f };
}

void Ground::Update()
{
	Scale = 1.0f;
	ImGui::Begin("Ground");
	ImGui::DragFloat3("Translate", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("Scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat("Scale", &Scale, 0.01f);
	ImGui::End();
	worldTransform_.scale_ = Multiply(Scale, worldTransform_.scale_);
	worldTransform_.UpdateMatrix();
}

void Ground::Draw(const ViewProjection& viewProjection,const DirectionalLight& light)
{
	sphere_->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransform_, texturehandle_,viewProjection ,light);
	
}

void Ground::Finaleze()
{
	delete sphere_;
	worldTransform_.constBuff_.ReleaseAndGetAddressOf();
}
