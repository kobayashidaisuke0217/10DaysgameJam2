#include "Stage1Object.h"

void Stage1Object::Initialize()
{

	textureManager_ = Texturemanager::GetInstance();
	textureHandle_[0] = textureManager_->Load("Resource/uvChecker.png");
	textureHandle_[1] = textureManager_->Load("Resource/checkerBoard.png");
	for (int i = 0; i < 7; i++)
	{
		sphere_[i] = new Sphere();
		sphere_[i]->Initialize();
	}
	SetGround(ground_);
	SetParent(&ground_->GetWorldTransform());

	//横
	worldTransformWall_[0].translation_ = { 0.18f,0.0030f,-0.18f };
	worldTransformWall_[0].scale_ = { 0.03f,0.3f,0.03f };

	worldTransformWall_[1].translation_ = { -0.18f,0.0030f,0.18f };
	worldTransformWall_[1].scale_ = { 0.03f,0.3f,0.03f };

	worldTransformWall_[2].translation_ = { 0.18f,0.0030f,0.18f };
	worldTransformWall_[2].scale_ = { 0.03f,0.3f,0.03f };

	worldTransformWall_[3].translation_ = { -0.18f,0.0030f,-0.18f };
	worldTransformWall_[3].scale_ = { 0.03f,0.3f,0.03f };

	//上
	worldTransformWall_[4].translation_ = { 0.0096f,-0.23f,0.0079f };
	worldTransformWall_[4].scale_ = { 0.3f,0.01f,0.3f };

	//下
	worldTransformWall_[5].translation_ = { 0.0096f,0.23f,0.0079f };
	worldTransformWall_[5].scale_ = { 0.3f,0.01f,0.3f };

	//ゴール
	worldTransformGoal_.translation_ = { 0.0096f,0.0030f,0.0079f };
	worldTransformGoal_.scale_ = { 0.05f,0.05f,0.05f };

	for (int i = 0; i < 6; i++)
	{
		worldTransformWall_[i].Initialize();
		worldTransformGoal_.Initialize();
	}
	
}

void Stage1Object::Update()
{
	for (int i = 0; i < 6; i++) {
		obb_[i].center = worldTransformWall_[i].GetWorldPos();

		GetOrientations(MakeRotateXYZMatrix(worldTransformWall_[i].rotation_), obb_[i].orientation);
		obb_[i].size = worldTransformWall_[i].scale_ * 100.0f;
	}
	obbGoal_.center = worldTransformGoal_.GetWorldPos();
	GetOrientations(MakeRotateXYZMatrix(worldTransformGoal_.rotation_), obbGoal_.orientation);
	obbGoal_.size = worldTransformGoal_.scale_ * 100.0f;
	for (int i = 0; i < 6; i++) { GetOrientations(MakeRotateXYZMatrix(ground_->GetWorldTransform().rotation_), obb_[i].orientation); }
	for (int i = 0; i < 6; i++)
	{
		worldTransformWall_[i].UpdateMatrix();
		worldTransformGoal_.UpdateMatrix();
	}

	float inputFloat3[3] = { worldTransformWall_[5].translation_.x + 1, worldTransformWall_[5].translation_.y + 1, worldTransformWall_[5].translation_.z + 1 };

	ImGui::Begin("Goal");
	ImGui::SliderFloat3("obbrotate", &worldTransformWall_[0].rotation_.x, -3.0f, 3.0f);
	//ImGui::SliderFloat3("rotate", &ground_->GetWorldTransform().rotation_.x, -3.0f, 3.0f);
	ImGui::End();

	worldTransformWall_[5].translation_.x = inputFloat3[0] - 1;
	worldTransformWall_[5].translation_.y = inputFloat3[1] - 1;
	worldTransformWall_[5].translation_.z = inputFloat3[2] - 1;
}

void Stage1Object::Draw(const ViewProjection& viewprojection, const DirectionalLight& light)
{
	for (int i = 0; i < 6; i++)
	{
		sphere_[i]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformWall_[i], textureHandle_[0], viewprojection, light);
	}

	sphere_[6]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformGoal_, textureHandle_[1], viewprojection, light);
}

void Stage1Object::Finalize()
{
	for (int i = 0; i < 7; i++)
	{
		delete sphere_[i];
	}

	for (int i = 0; i < 6; i++)
	{
		worldTransformWall_[i].constBuff_.ReleaseAndGetAddressOf();
		worldTransformGoal_.constBuff_.ReleaseAndGetAddressOf();
	}
}

void Stage1Object::SetParent(const WorldTransform* parent)
{
	for (int i = 0; i < 6; i++)
	{
		worldTransformWall_[i].parent_ = parent;
		worldTransformGoal_.parent_ = parent;
	}
}

