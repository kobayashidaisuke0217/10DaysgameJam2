#include "stage1Scene.h"

Stage1Scene::~Stage1Scene()
{

}

void Stage1Scene::Initialize()
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

	worldTransformWall_[0].translation_.x = -10.0f; 
	worldTransformWall_[0].translation_.z = 5.0f;
	worldTransformWall_[0].scale_.y = 8.0f;

	worldTransformWall_[1].translation_.x = -5.0f;
	worldTransformWall_[1].translation_.z = -5.0f;
	worldTransformWall_[1].scale_.y = 8.0f;

	worldTransformWall_[2].translation_.x = 5.0f;
	worldTransformWall_[2].translation_.z = 5.0f;
	worldTransformWall_[2].scale_.y = 8.0f;

	worldTransformWall_[3].translation_.x = 10.0f;
	worldTransformWall_[3].translation_.z = -5.0f;
	worldTransformWall_[3].scale_.y = 8.0f;

	worldTransformWall_[4].translation_.y = 8.0f;
	worldTransformWall_[4].scale_.x = 15.0f; 
	worldTransformWall_[4].scale_.z = 10.0f;

	worldTransformWall_[5].translation_.y = -8.0f;
	worldTransformWall_[5].scale_.x = 15.0f;
	worldTransformWall_[5].scale_.z = 10.0f;

	worldTransformGoal_.scale_ = { 2.0f,2.0f,2.0f };

	textureHandle_[0] = textureManager_->Load("Resource/uvChecker.png");
	textureHandle_[1] = textureManager_->Load("Resource/CheckerBoard.png");

	light_ = { {1.0f,1.0f,1.0f,1.0f},{0.0f,-1.0f,0.0f},1.0f };
}

void Stage1Scene::Update()
{
	light_.direction = Normalise(light_.direction);

	ImGui::Begin("Stage1Scene");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::Text("worldTransform_.translation_.x %f", worldTransformWall_[4].translation_.x);
	ImGui::Text("worldTransform_.translation_.y %f", worldTransformWall_[4].translation_.y);

	/*if (sceneNum > 1) {
		sceneNum = 1;
	}*/
	ImGui::End();

	for (int i = 0; i < 6; i++)
	{
		worldTransformWall_[i].UpdateMatrix();
		worldTransformGoal_.UpdateMatrix();
	}
}


void Stage1Scene::Draw()
{

	//3D描画準備
	engine_->ModelPreDraw();
	Draw3D();
	//2D描画準備
	engine_->SpritePreDraw();
	Draw2D();
}

void Stage1Scene::Draw3D()
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

void Stage1Scene::Draw2D() {



}
void Stage1Scene::Finalize()
{
	viewProjection_.constBuff_.ReleaseAndGetAddressOf();
}


