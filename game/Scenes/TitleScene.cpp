#include "TitleScene.h"
//#include "ImGuiManger.h"
TitleScene::~TitleScene()
{
}
void TitleScene::Initialize()
{	
	blueMoon_ = BlueMoon::GetInstance();
	textureManager_ = Texturemanager::GetInstance();
	input = Input::GetInstance();
	Texhandle_ = textureManager_->Load("Resource/title.png");
	sprite_ = new Sprite();
	sprite_->Initialize({ 0.0f,0.0f,0.0f,1.0f }, { 1280.0f,720.0f,0.0f,1.0f });
}

void TitleScene::Update()
{
	//ImGui::Begin("SceneManager");
	//ImGui::InputInt("SceneNum", &sceneNum);
	//ImGui::Text("Push To Space");
	//ImGui::End();

	if (input->PushKey(DIK_SPACE))
	{
		sceneNum = GAME_SCENE;
	}
}

void TitleScene::Draw()
{
	blueMoon_->SpritePreDraw();
	sprite_->Draw({ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} }, { {1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}, }, { 1.0f,1.0f,1.0f,1.0f }, Texhandle_);
}

void TitleScene::Finalize()
{
	delete sprite_;
}
