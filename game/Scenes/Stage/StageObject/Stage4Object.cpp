#include "Stage4Object.h"

void Stage4Object::Initialize()
{
	skyDome_.Initialize();

	textureManager_ = Texturemanager::GetInstance();
	textureHandle_[0] = textureManager_->Load("Resource/wall.png");
	textureHandle_[1] = textureManager_->Load("Resource/goal.png");
	textureHandle_[2] = textureManager_->Load("Resource/enemy.png");

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
	worldTransformPlane_.translation_ = { 0.0f,-0.12f,0.25f };
	worldTransformPlane_.rotation_.x = 171.2f;
	worldTransformPlane_.scale_ = { 0.5f,0.45f,0.7f };

	//上
	worldTransformWall_[0].translation_ = { 0.0f,0.19f,-0.32f };
	worldTransformWall_[0].scale_ = { 0.4f,0.01f,0.4f };

	//下
	worldTransformWall_[1].translation_ = { 0.0f,-0.08f,-0.35f };
	worldTransformWall_[1].scale_ = { 0.4f,0.01f,0.5f };

	//横
	worldTransformWall_[2].translation_ = { 0.15f,0.08f,0.03f };
	worldTransformWall_[2].scale_ = { 0.03f,0.1f,0.3f };

	worldTransformWall_[3].translation_ = { -0.15f,0.08f,0.03f };
	worldTransformWall_[3].scale_ = { 0.03f,0.1f,0.3f };

	//反射する壁
	worldTransformWall_[4].translation_ = { 0.0f,0.0030f,0.40f };
	worldTransformWall_[4].scale_ = { 0.65f,0.6f,0.01f };

	//敵
	worldTransformWall_[5].translation_ = { 0.0f,0.05f,-0.20f };
	worldTransformWall_[5].scale_ = { 0.08f,0.08f,0.08f };

	worldTransformWall_[6].translation_ = { 0.20f,-0.03f,0.14f };
	worldTransformWall_[6].scale_ = { 0.05f,0.05f,0.05f };

	worldTransformWall_[7].translation_ = { -0.20f,-0.03f,0.14f };
	worldTransformWall_[7].scale_ = { 0.05f,0.05f,0.05f };

	//ゴール
	worldTransformGoal_.translation_ = { 0.0096f,0.1f,0.0089f };
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
	skyDome_.Update();

	for (int i = 0; i < 8; i++)
	{
		worldTransformWall_[i].UpdateMatrix();
		worldTransformPlane_.UpdateMatrix();
		worldTransformGoal_.UpdateMatrix();
	}
	for (int i = 0; i < 8; i++) {
		obb_[i].center = worldTransformWall_[i].GetWorldPos();

		GetOrientations(MakeRotateXYZMatrix(worldTransformWall_[i].rotation_), obb_[i].orientation);
		obb_[i].size = worldTransformWall_[i].scale_ * 100.0f;
	}
	obbGoal_.center = worldTransformGoal_.GetWorldPos();
	GetOrientations(MakeRotateXYZMatrix(worldTransformGoal_.rotation_), obbGoal_.orientation);
	obbGoal_.size = worldTransformGoal_.scale_ * 100.0f;
	Vector3 ObjRotate[8]{};
	
	for (int i = 0; i < 8; i++)
	{ 
		/*ObjRotate[i] = Multiply(worldTransformWall_[i].rotation_ , ground_->GetWorldTransform().rotation_);
		GetOrientations(MakeRotateXYZMatrix(ObjRotate[i]), obb_[i].orientation); */
	     
		GetOrientations(MakeRotateXYZMatrix(ground_->GetWorldTransform().rotation_), obb_[i].orientation);
	}
	

	float inputFloat3[3] = { worldTransformWall_[6].translation_.x + 1, worldTransformWall_[6].translation_.y + 1, worldTransformWall_[6].translation_.z + 1 };

	ImGui::Begin("Goal");
	ImGui::SliderFloat3("obbrotate", &obb_[2].orientation[0].x, -3.0f, 3.0f);
	ImGui::SliderFloat3("obbrotate", &obb_[2].orientation[1].x, -3.0f, 3.0f);
	ImGui::SliderFloat3("obbrotate", &obb_[2].orientation[2].x, -3.0f, 3.0f);
	//ImGui::SliderFloat3("rotate", &ground_->GetWorldTransform().rotation_.x, -3.0f, 3.0f);
	ImGui::SliderFloat3("GoalPos", inputFloat3, -10.0f, 10.0f);
	ImGui::End();

	worldTransformWall_[6].translation_.x = inputFloat3[0] - 1;
	worldTransformWall_[6].translation_.y = inputFloat3[1] - 1;
	worldTransformWall_[6].translation_.z = inputFloat3[2] - 1;
}

void Stage4Object::Draw(const ViewProjection& viewprojection, const DirectionalLight& light)
{
	skyDome_.Draw(viewprojection, light);

	plane_->Draw(worldTransformPlane_, viewprojection, { 1.0f,1.0f,1.0f,1.0f }, light, textureHandle_[0]);

	for (int i = 0; i < 5; i++)
	{
		if (!ishit_[i]) {
		sphere_[i]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformWall_[i], textureHandle_[0], viewprojection, light);
		}
	}

	for (int i = 5; i < 8; i++)
	{
		if (!ishit_[i]) {
			sphere_[i]->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransformWall_[i], textureHandle_[2], viewprojection, light);
		}
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
		
	}worldTransformGoal_.constBuff_.ReleaseAndGetAddressOf();
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