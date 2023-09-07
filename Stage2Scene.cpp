#include "Stage2Scene.h"

Stage2Scene::~Stage2Scene()
{

}

void Stage2Scene::Initialize()
{
	engine_ = BlueMoon::GetInstance();

	directX_ = DirectXCommon::GetInstance();

	textureManager_ = Texturemanager::GetInstance();

	input_ = Input::GetInstance();

	viewProjection_.Initialize();

	for (int i = 0; i < 7; i++)
	{
		sphere_[i] = new Sphere();
		sphere_[i]->Initialize();
	}

	for (int i = 0; i < 6; i++)
	{
		worldTransformWall_[i].Initialize();
		worldTransformGoal_.Initialize();
	}

	//左の壁
	worldTransformWall_[0].translation_.x = -11.0f;
	worldTransformWall_[0].scale_.y = 8.0f;
	worldTransformWall_[0].scale_.z = 8.0f;

	//前の壁
	worldTransformWall_[1].translation_.z = -11.0f;
	worldTransformWall_[1].scale_.x = 8.0f;
	worldTransformWall_[1].scale_.y = 8.0f;

	//後ろの壁
	worldTransformWall_[2].translation_.z = 11.0f;
	worldTransformWall_[2].scale_.x = 8.0f;
	worldTransformWall_[2].scale_.y = 8.0f;

	//右の壁
	worldTransformWall_[3].translation_.x = 11.0f;
	worldTransformWall_[3].scale_.y = 8.0f;
	worldTransformWall_[3].scale_.z = 8.0f;

	//上
	worldTransformWall_[4].translation_.y = 8.0f;
	worldTransformWall_[4].scale_.x = 15.0f;
	worldTransformWall_[4].scale_.z = 10.0f;

	//下
	worldTransformWall_[5].translation_.y = -8.0f;
	worldTransformWall_[5].scale_.x = 15.0f;
	worldTransformWall_[5].scale_.z = 10.0f;

	//ゴール
	worldTransformGoal_.scale_ = { 2.0f,2.0f,2.0f };

	textureHandle_[0] = textureManager_->Load("Resource/uvChecker.png");
	textureHandle_[1] = textureManager_->Load("Resource/CheckerBoard.png");

	light_ = { {1.0f,1.0f,1.0f,1.0f},{0.0f,-1.0f,0.0f},1.0f };
}

void Stage2Scene::Update()
{
	light_.direction = Normalise(light_.direction);

	ImGui::Begin("Stage1Scene");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::Text("worldTransform_.translation_.x %f", worldTransformWall_[1].translation_.x);
	ImGui::Text("worldTransform_.translation_.y %f", worldTransformWall_[4].translation_.y);

	/*if (sceneNum > 1) {
		sceneNum = 1;
	}*/
	ImGui::End();

	//左の壁の移動処理
	if (moveCount_[0] == 0)
	{
		worldTransformWall_[0].translation_.z -= 0.3f;
		if (worldTransformWall_[0].translation_.z <= -18)
		{
			moveCount_[0] = 1;
		}
	}

	if (moveCount_[0] == 1)
	{
		worldTransformWall_[0].translation_.z += 0.3f;
		if (worldTransformWall_[0].translation_.z >= 18)
		{
			moveCount_[0] = 0;
		}
	}

	//前の壁の移動処理
	if (moveCount_[1] == 0)
	{
		worldTransformWall_[1].translation_.x += 0.3f;
		if (worldTransformWall_[1].translation_.x >= 18)
		{
			moveCount_[1] = 1;
		}
	}

	if (moveCount_[1] == 1)
	{
		worldTransformWall_[1].translation_.x -= 0.3f;
		if (worldTransformWall_[1].translation_.x <= -18)
		{
			moveCount_[1] = 0;
		}
	}

	//後ろの壁の移動処理
	if (moveCount_[2] == 0)
	{
		worldTransformWall_[2].translation_.x -= 0.3f;
		if (worldTransformWall_[2].translation_.x <= -18)
		{
			moveCount_[2] = 1;
		}
	}

	if (moveCount_[2] == 1)
	{
		worldTransformWall_[2].translation_.x += 0.3f;
		if (worldTransformWall_[2].translation_.x >= 18)
		{
			moveCount_[2] = 0;
		}
	}

	//右の壁の移動処理
	if (moveCount_[3] == 0)
	{
		worldTransformWall_[3].translation_.z += 0.3f;
		if (worldTransformWall_[3].translation_.z >= 18)
		{
			moveCount_[3] = 1;
		}
	}

	if (moveCount_[3] == 1)
	{
		worldTransformWall_[3].translation_.z -= 0.3f;
		if (worldTransformWall_[3].translation_.z <= -18)
		{
			moveCount_[3] = 0;
		}
	}


	for (int i = 0; i < 6; i++)
	{
		worldTransformWall_[i].UpdateMatrix();
		worldTransformGoal_.UpdateMatrix();
	}
}


void Stage2Scene::Draw()
{

	//3D描画準備
	engine_->ModelPreDraw();
	Draw3D();
	//2D描画準備
	engine_->SpritePreDraw();
	Draw2D();
}

void Stage2Scene::Draw3D()
{
	for (int i = 0; i < 6; i++)
	{
		sphere_[i]->Draw(material_, worldTransformWall_[i], textureHandle_[0], viewProjection_, light_);
	}

	sphere_[6]->Draw(material_, worldTransformGoal_, textureHandle_[1], viewProjection_, light_);

	//ワイヤーフレーム描画準備
	//ワイヤーフレームで描画したいものはこれより下に描画処理を書く
	//これより下の3D描画は全てワイヤーフレームになるから注意してね
	engine_->ModelPreDrawWireFrame();



}

void Stage2Scene::Draw2D() {



}
void Stage2Scene::Finalize()
{
	for (int i = 0; i < 7; i++)
	{
		sphere_[i]->Finalize();
	}

	viewProjection_.constBuff_.ReleaseAndGetAddressOf();
}
