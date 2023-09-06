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

	for (int i = 0; i < 2; i++)
	{
		sphere_[i] = new Sphere();
		sphere_[i]->Initialize();

		worldTransform_[i].Initialize();
	}

	worldTransform_[0].translation_.x = 10.0f; 
	worldTransform_[1].translation_.x = -10.0f;

	textureHandle_ = textureManager_->Load("Resource/uvChecker.png");

	light_ = { {1.0f,1.0f,1.0f,1.0f},{0.0f,-1.0f,0.0f},1.0f };
}

void Stage1Scene::Update()
{
	light_.direction = Normalise(light_.direction);

	ImGui::Begin("Stage1Scene");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::Text("worldTransform_.translation_.x %f",worldTransform_[0].translation_.x);
	ImGui::Text("worldTransform_.translation_.y %f", worldTransform_[0].translation_.y);

	/*if (sceneNum > 1) {
		sceneNum = 1;
	}*/
	ImGui::End();

	for (int i = 0; i < 2; i++)
	{
		worldTransform_[i].UpdateMatrix();
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
	for (int i = 0; i < 2; i++)
	{
		sphere_[i]->Draw(material_, worldTransform_[i], textureHandle_, viewProjection_, light_);
	}

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


