#include "ClearScene.h"
#include "ImGuiManger.h"

void ClearScene::Initialize()
{
	blueMoon_ = BlueMoon::GetInstance();
	textureManager_ = Texturemanager::GetInstance();
	input = Input::GetInstance();
	Texhandle_=textureManager_->Load("Resource/clear.png");
	sprite_ = new Sprite();
    sprite_->Initialize({ 0.0f,0.0f,0.0f,1.0f }, { 1280.0f,720.0f,0.0f,1.0f });
}

void ClearScene::Update()
{
	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::Text("Stage Select");
	ImGui::End();

	if (input->PushKey(DIK_SPACE)) 
	{
		sceneNum = GAME_SCENE;
	}
}

void ClearScene::Draw()
{
	blueMoon_->SpritePreDraw();
	sprite_->Draw({ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} }, { {1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}, }, { 1.0f,1.0f,1.0f,1.0f }, Texhandle_);
}

void ClearScene::Finalize()
{
	delete sprite_;
}
