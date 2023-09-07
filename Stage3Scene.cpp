#include "Stage3Scene.h"

Stage3Scene::~Stage3Scene()
{

}

void Stage3Scene::Initialize()
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

	//ゴール
	worldTransformGoal_.scale_ = { 2.0f,2.0f,2.0f };

	textureHandle_[0] = textureManager_->Load("Resource/uvChecker.png");
	textureHandle_[1] = textureManager_->Load("Resource/CheckerBoard.png");

	light_ = { {1.0f,1.0f,1.0f,1.0f},{0.0f,-1.0f,0.0f},1.0f };
}

void Stage3Scene::Update()
{
	light_.direction = Normalise(light_.direction);

	ImGui::Begin("Stage1Scene");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::Text("Stage3");

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


void Stage3Scene::Draw()
{

	//3D描画準備
	engine_->ModelPreDraw();
	Draw3D();
	//2D描画準備
	engine_->SpritePreDraw();
	Draw2D();
}

void Stage3Scene::Draw3D()
{
	sphere_[6]->Draw(material_, worldTransformGoal_, textureHandle_[1], viewProjection_, light_);

	//ワイヤーフレーム描画準備
	//ワイヤーフレームで描画したいものはこれより下に描画処理を書く
	//これより下の3D描画は全てワイヤーフレームになるから注意してね
	engine_->ModelPreDrawWireFrame();



}

void Stage3Scene::Draw2D() {



}
void Stage3Scene::Finalize()
{
	viewProjection_.constBuff_.ReleaseAndGetAddressOf();
}

