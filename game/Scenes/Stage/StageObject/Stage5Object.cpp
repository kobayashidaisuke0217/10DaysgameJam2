#include "Stage5Object.h"

void Stage5Object::Initialize()
{

	textureManager_ = Texturemanager::GetInstance();
	textureHandle_[0] = textureManager_->Load("Resource/uvChecker.png");
	textureHandle_[1] = textureManager_->Load("Resource/checkerBoard.png");
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

	//地面のすり抜ける壁
	worldTransformPlane_[0].translation_ = { 0.0f,-0.16f,0.44f };
	worldTransformPlane_[0].rotation_.x = 171.2f;
	worldTransformPlane_[0].scale_ = { 0.5f,0.45f,0.7f };

	//前のすり抜ける壁
	worldTransformPlane_[1].translation_ = { 0.0f,0.0f,-0.34f };
	worldTransformPlane_[1].scale_ = { 0.2f,0.25f,0.0f };

	//上
	worldTransformWall_[0].translation_ = { 0.0f,0.15f,-0.1f };
	worldTransformWall_[0].scale_ = { 0.2f,0.01f,0.4f };

	//下
	worldTransformWall_[1].translation_ = { 0.0f,-0.15f,-0.1f };
	worldTransformWall_[1].scale_ = { 0.2f,0.01f,0.4f };

	//横
	worldTransformWall_[2].translation_ = { -0.15f,0.0030f,-0.1f };
	worldTransformWall_[2].scale_ = { 0.03f,0.1f,0.4f };

	worldTransformWall_[3].translation_ = { 0.15f,0.0030f,-0.1f };
	worldTransformWall_[3].scale_ = { 0.03f,0.1f,0.4f };

	//反射する壁
	worldTransformWall_[4].translation_ = { 0.0f,0.11f,0.44f };
	worldTransformWall_[4].scale_ = { 0.3f,0.4f,0.01f };

	//下の反射する壁
	worldTransformWall_[5].translation_ = { 0.0f,-0.51f,0.44f };
	worldTransformWall_[5].scale_ = { 0.2f,0.01f,0.2f };

	//敵
	worldTransformWall_[6].translation_ = { 0.0096f,0.0031f,-0.215f };
	worldTransformWall_[6].scale_ = { 0.05f,0.05f,0.05f };

	worldTransformWall_[7].translation_ = { 0.0096f,0.082f,0.05f };
	worldTransformWall_[7].scale_ = { 0.05f,0.05f,0.05f };

	//ゴール
	worldTransformGoal_.translation_ = { 0.0096f,0.0031f,-0.08f };
	worldTransformGoal_.scale_ = { 0.05f,0.05f,0.05f };

	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].Initialize();
		worldTransformGoal_.Initialize();
	}

	for (int i = 0; i < 2; i++)
	{
		worldTransformPlane_[i].Initialize();
	}
}

void Stage5Object::Update()
{
	for (int i = 0; i < 8; i++) {
		obb_[i].center = worldTransformWall_[i].GetWorldPos();

		GetOrientations(MakeRotateXYZMatrix(worldTransformWall_[i].rotation_), obb_[i].orientation);
		obb_[i].size = worldTransformWall_[i].scale_ * 100.0f;
	}
	obbGoal_.center = worldTransformGoal_.GetWorldPos();
	GetOrientations(MakeRotateXYZMatrix(worldTransformGoal_.rotation_), obbGoal_.orientation);
	obbGoal_.size = worldTransformGoal_.scale_ * 100.0f;
	for (int i = 0; i < 8; i++) { GetOrientations(MakeRotateXYZMatrix(ground_->GetWorldTransform().rotation_), obb_[i].orientation); }
	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].UpdateMatrix();
		worldTransformGoal_.UpdateMatrix();
	}

	for (int i = 0; i < 2; i++)
	{
		worldTransformPlane_[i].UpdateMatrix();
	}

	float inputFloat3[3] = { worldTransformWall_[5].translation_.x + 1, worldTransformWall_[5].translation_.y + 1, worldTransformWall_[5].translation_.z + 1 };

	ImGui::Begin("Goal");
	ImGui::SliderFloat3("GoalPos", inputFloat3, -10.0f, 10.0f);
	ImGui::End();

	worldTransformWall_[5].translation_.x = inputFloat3[0] - 1;
	worldTransformWall_[5].translation_.y = inputFloat3[1] - 1;
	worldTransformWall_[5].translation_.z = inputFloat3[2] - 1;
}

void Stage5Object::Draw(const ViewProjection& viewprojection, const DirectionalLight& light)
{
	for (int i = 0; i < 2; i++)
	{
		plane_[i]->Draw(worldTransformPlane_[i], viewprojection, {1.0f,1.0f,1.0f,1.0f}, light, textureHandle_[0]);
	}

	for (int i = 0; i < 6; i++)
	{
		sphere_[i]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformWall_[i], textureHandle_[0], viewprojection, light);
	}

	for (int i = 6; i < 8; i++)
	{
		sphere_[i]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformWall_[i], textureHandle_[2], viewprojection, light);
	}

	sphere_[8]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformGoal_, textureHandle_[1], viewprojection, light);
}

void Stage5Object::Finalize()
{
	for (int i = 0; i < 2; i++)
	{
		delete plane_[i];
	}

	for (int i = 0; i < 9; i++)
	{
		delete sphere_[i];
	}

	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].constBuff_.ReleaseAndGetAddressOf();
		worldTransformGoal_.constBuff_.ReleaseAndGetAddressOf();
	}

	for (int i = 0; i < 2; i++)
	{
		worldTransformPlane_[i].constBuff_.ReleaseAndGetAddressOf();
	}
}

void Stage5Object::SetParent(const WorldTransform* parent)
{
	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].parent_ = parent;
		worldTransformGoal_.parent_ = parent;
	}

	for (int i = 0; i < 2; i++)
	{
		worldTransformPlane_[i].parent_ = parent;
	}
}
