#include "ShadowPlane.h"
#include "Player.h"
void ShadowPlane::Initialize()
{
	input_ = Input::GetInstance();
	plane_ = new Plane();
	plane_->Initialize();
	textureManager_ = Texturemanager::GetInstance();
	texturehandle_ = textureManager_->Load("Resource/castShadow.png");
	//offset = 42.1f;
	offset = 101.0f;
	//offset = 2.0f;
	worldTransform_.scale_ = { 10.0f,6.0f,0.0f };
	worldTransform_.rotation_ = { -0.1f,4.0f,1.2f, };
	//worldTransform_.translation_ = { 24.4f,23.9f,24.7f };
	
worldTransform_.Initialize();
}

void ShadowPlane::Update()
{
	
	Move();
	ImGui::Begin("plane");
	ImGui::DragFloat3("tra", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotate", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::End();
	worldTransform_.UpdateMatrix();
}

void ShadowPlane::Draw(const ViewProjection& viewprojection, const DirectionalLight& light)
{
	plane_->Draw( worldTransform_, viewprojection, { 1.0f,1.0f,1.0f,1.0f }, light, texturehandle_);
}

void ShadowPlane::Finalize()
{
	delete plane_;
	worldTransform_.constBuff_.ReleaseAndGetAddressOf();
}

void ShadowPlane::SetPlayer( Player* player)
{
	player_ =player;
}

void ShadowPlane::Move()
{

	
		Vector3 velocity = Subtract(  player_->GetWorldPos(), {0.0f,0.0f,0.0f});
	
		velocity = Normalise(velocity);
		worldTransform_.translation_ = Multiply(offset, velocity);
		
}


void ShadowPlane::Rotate()
{

	worldTransform_.rotation_ = Cross(player_->GetWorldPos(), {0.0f,0.0f,0.0f});
}

Vector3 ShadowPlane::GetWorldPos()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}