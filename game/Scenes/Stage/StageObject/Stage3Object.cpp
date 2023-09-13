#include "Stage3Object.h"

void Stage3Object::Initialize()
{
	skyDome_.Initialize();

	textureManager_ = Texturemanager::GetInstance();
	textureHandle_[0] = textureManager_->Load("Resource/uvChecker.png");
	textureHandle_[1] = textureManager_->Load("Resource/goal.png");
	textureHandle_[2] = textureManager_->Load("Resource/monsterBall.png");

	for (int i = 0; i < 9; i++)
	{
		sphere_[i] = new Sphere();
		sphere_[i]->Initialize();
	}

	for (int i = 0; i < 2; i++)
	{
		plane_[i] = new Plane();
		plane_[i]->Initialize();
	}

	SetGround(ground_);
	SetParent(&ground_->GetWorldTransform());

	//前
	worldTransformPlane_[0].translation_ = { 0.00986f,0.0030f,0.34f };
	worldTransformPlane_[0].scale_ = { 0.5f,0.5f,0.5f };

	//後ろ
	worldTransformPlane_[1].translation_ = { -0.00986f,0.0030f,-0.34f };
	worldTransformPlane_[1].scale_ = { 0.5f,0.5f,0.5f };

	//上
	worldTransformWall_[0].translation_ = { 0.0096f,-0.23f,0.0079f };
	worldTransformWall_[0].scale_ = { 0.5f,0.01f,0.5f };

	//下
	worldTransformWall_[1].translation_ = { 0.0096f,0.23f,0.0079f };
	worldTransformWall_[1].scale_ = { 0.5f,0.01f,0.5f };

	//横
	worldTransformWall_[2].translation_ = { 0.34f,0.0030f,-0.019f };
	worldTransformWall_[2].scale_ = { 0.03f,0.5f,0.5f };

	worldTransformWall_[3].translation_ = { -0.34f,0.0030f,-0.019f };
	worldTransformWall_[3].scale_ = { 0.03f,0.5f,0.5f };

	//敵
	worldTransformWall_[4].translation_ = { -0.212f,0.0030f,0.20f };
	worldTransformWall_[4].scale_ = {0.05f,0.05f,0.05f};

	worldTransformWall_[5].translation_ = { 0.212f,0.0030f,0.20f };
	worldTransformWall_[5].scale_ = { 0.05f,0.05f,0.05f };

	worldTransformWall_[6].translation_ = { 0.20f,0.0030f,-0.212f };
	worldTransformWall_[6].scale_ = { 0.05f,0.05f,0.05f };

	worldTransformWall_[7].translation_ = { -0.20f,0.0030f,-0.212f };
	worldTransformWall_[7].scale_ = { 0.05f,0.05f,0.05f };

	//ゴール
	worldTransformGoal_.translation_ = { 0.0096f,0.0030f,0.0079f };
	worldTransformGoal_.scale_ = { 0.05f,0.05f,0.05f };

	for (int i = 0; i < 2; i++)
	{
		worldTransformPlane_[i].Initialize();
	}

	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].Initialize();
		worldTransformGoal_.Initialize();
	}
}

void Stage3Object::Update()
{
	skyDome_.Update();

	for (int i = 0; i < 8; i++) {
		obb_[i].center = worldTransformWall_[i].GetWorldPos();

		GetOrientations(MakeRotateXYZMatrix(worldTransformWall_[i].rotation_), obb_[i].orientation);
		obb_[i].size = worldTransformWall_[i].scale_ * 100.0f;
	}
	obbGoal_.center = worldTransformGoal_.GetWorldPos();
	GetOrientations(MakeRotateXYZMatrix(worldTransformGoal_.rotation_), obbGoal_.orientation);
	obbGoal_.size = worldTransformGoal_.scale_ * 100.0f;
	for (int i = 0; i < 8; i++) { GetOrientations(MakeRotateXYZMatrix(ground_->GetWorldTransform().rotation_), obb_[i].orientation); }
	for (int i = 0; i < 2; i++)
	{
		worldTransformPlane_[i].UpdateMatrix();
	}

	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].UpdateMatrix();
		worldTransformGoal_.UpdateMatrix();
	}

	float inputFloat3[3] = { worldTransformWall_[6].translation_.x + 1, worldTransformWall_[6].translation_.y + 1, worldTransformWall_[6].translation_.z + 1 };

	ImGui::Begin("Goal");
	ImGui::SliderFloat3("GoalPos", inputFloat3, -3.0f, 3.0f);
	ImGui::End();

	worldTransformWall_[6].translation_.x = inputFloat3[0] - 1;
	worldTransformWall_[6].translation_.y = inputFloat3[1] - 1;
	worldTransformWall_[6].translation_.z = inputFloat3[2] - 1;
}

void Stage3Object::Draw(const ViewProjection& viewprojection, const DirectionalLight& light)
{
	skyDome_.Draw(viewprojection, light);

	for (int i = 0; i < 2; i++)
	{
		plane_[i]->Draw(worldTransformPlane_[i], viewprojection, { 1.0f,1.0f,1.0f,1.0f }, light,textureHandle_[0]);
	}

	for (int i = 0; i < 4; i++)
	{
		sphere_[i]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformWall_[i], textureHandle_[0], viewprojection, light);
	}

	for (int i = 4; i < 8; i++)
	{
		sphere_[i]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformWall_[i], textureHandle_[2], viewprojection, light);
	}

	sphere_[8]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformGoal_, textureHandle_[1], viewprojection, light);
}

void Stage3Object::Finalize()
{
	for (int i = 0; i < 2; i++)
	{
		delete plane_[i];
	}

	for (int i = 0; i < 9; i++)
	{
		delete sphere_[i];
	}

	for (int i = 0; i < 2; i++)
	{
		worldTransformPlane_[i].constBuff_.ReleaseAndGetAddressOf();
	}

	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].constBuff_.ReleaseAndGetAddressOf();
		worldTransformGoal_.constBuff_.ReleaseAndGetAddressOf();
	}
}

void Stage3Object::SetParent(const WorldTransform* parent)
{
	for (int i = 0; i < 2; i++)
	{
		worldTransformPlane_[i].parent_ = parent;
	}

	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].parent_ = parent;
		worldTransformGoal_.parent_ = parent;
	}
}
