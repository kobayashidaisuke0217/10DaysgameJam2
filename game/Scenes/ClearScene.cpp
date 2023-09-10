#include "ClearScene.h"

void ClearScene::Initialize()
{
	blueMoon_ = BlueMoon::GetInstance();
	textureManager_ = Texturemanager::GetInstance();
	input = Input::GetInstance();
	Texhandle_=textureManager_->Load("Resource/uvChecker.png");
	sprite_ = new Sprite();
      	sprite_->Initialize({ 0.0f,0.0f,0.0f,1.0f }, { 1280.0f,720.0f,0.0f,1.0f }, { {1.0f,1.0f,1.0f,1.0f},{0.0f,-1.0f,0.0f},1.0f });
}

void ClearScene::Update()
{
	if (input->PushKey(DIK_0)) {
		sceneNum = TITLE_SCENE;
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
