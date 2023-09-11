#include "Stage4Object.h"

void Stage4Object::Initialize()
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

	
	plane_ = new Plane();
	plane_->Initialize();
	

	SetGround(ground_);
	SetParent(&ground_->GetWorldTransform());

	//地面のすり抜ける壁
	worldTransformPlane_.translation_ = { -0.20f,-0.12f,0.25f };
	worldTransformPlane_.rotation_.x = 171.2f;
	worldTransformPlane_.rotation_.y = 30.73f;
	worldTransformPlane_.scale_ = { 0.5f,0.45f,0.7f };

	//上
	worldTransformWall_[0].translation_ = { 0.0096f,0.14f,0.0079f };
	worldTransformWall_[0].scale_ = { 0.4f,0.01f,0.4f };

	//下
	worldTransformWall_[1].translation_ = { 0.18f,-0.08f,-0.24f };
	worldTransformWall_[1].scale_ = { 0.4f,0.01f,0.4f };

	//横
	worldTransformWall_[2].translation_ = { 0.3f,0.0030f,0.08f };
	worldTransformWall_[2].scale_ = { 0.03f,0.05f,0.4f };

	worldTransformWall_[3].translation_ = { -0.1f,0.0030f,-0.27f };
	worldTransformWall_[3].scale_ = { 0.4f,0.05f,0.03f };
	/*worldTransformWall_[3].rotation_.y = 30.0f;*/

	//反射する壁
	worldTransformWall_[4].translation_ = { -0.35f,0.0030f,0.40f };
	worldTransformWall_[4].scale_ = { 0.01f,0.8f,0.65f };
	//worldTransformWall_[4].rotation_.y = 7.2f;

	//敵
	worldTransformWall_[5].translation_ = { 0.12f,0.0030f,0.20f };
	worldTransformWall_[5].scale_ = { 0.05f,0.05f,0.05f };

	worldTransformWall_[6].translation_ = { 0.20f,0.0030f,-0.212f };
	worldTransformWall_[6].scale_ = { 0.05f,0.05f,0.05f };

	worldTransformWall_[7].translation_ = { -0.20f,0.0030f,-0.07f };
	worldTransformWall_[7].scale_ = { 0.05f,0.05f,0.05f };

	//ゴール
	worldTransformGoal_.translation_ = { 0.0096f,0.0033f,0.0079f };
	worldTransformGoal_.scale_ = { 0.05f,0.05f,0.05f };

	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].Initialize();
		worldTransformPlane_.Initialize();
		worldTransformGoal_.Initialize();
	}
}

void Stage4Object::Update()
{
	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].UpdateMatrix();
		worldTransformPlane_.UpdateMatrix();
		worldTransformGoal_.UpdateMatrix();
	}

	float inputFloat3[3] = { worldTransformWall_[1].translation_.x + 1, worldTransformWall_[1].translation_.y + 1, worldTransformWall_[1].translation_.z + 1 };

	ImGui::Begin("Goal");
	ImGui::SliderFloat3("GoalPos", inputFloat3, -10.0f, 10.0f);
	ImGui::End();

	worldTransformWall_[1].translation_.x = inputFloat3[0] - 1;
	worldTransformWall_[1].translation_.y = inputFloat3[1] - 1;
	worldTransformWall_[1].translation_.z = inputFloat3[2] - 1;
}

void Stage4Object::Draw(const ViewProjection& viewprojection, const DirectionalLight& light)
{
	
	plane_->Draw(worldTransformPlane_, viewprojection, { 1.0f,1.0f,1.0f,1.0f }, light, textureHandle_[0]);

	for (int i = 0; i < 5; i++)
	{
		sphere_[i]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformWall_[i], textureHandle_[0], viewprojection, light);
	}

	for (int i = 5; i < 8; i++)
	{
		sphere_[i]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformWall_[i], textureHandle_[2], viewprojection, light);
	}

	sphere_[8]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformGoal_, textureHandle_[1], viewprojection, light);
}

void Stage4Object::Finalize()
{
	delete plane_;

	for (int i = 0; i < 9; i++)
	{
		delete sphere_[i];
	}

	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].constBuff_.ReleaseAndGetAddressOf();
		worldTransformPlane_.constBuff_.ReleaseAndGetAddressOf();
		worldTransformGoal_.constBuff_.ReleaseAndGetAddressOf();
	}
}

void Stage4Object::SetParent(const WorldTransform* parent)
{
	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].parent_ = parent;
		worldTransformPlane_.parent_ = parent;
		worldTransformGoal_.parent_ = parent;
	}
}