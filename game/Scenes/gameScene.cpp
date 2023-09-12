#include "gameScene.h"
#include "ImGuiManger.h"

GameScene::~GameScene()
{
	
}

void GameScene::Initialize()
{
	blueMoon_ = BlueMoon::GetInstance();
	textureManager_ = Texturemanager::GetInstance();
	input_ = Input::GetInstance();
}
	

void GameScene::Update()
{
	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::Text("Stage Select");
	ImGui::End();
	
	if (input_->PushKey(DIK_1))
	{
		sceneNum = STAGE1_SCENE;
	}

	if (input_->PushKey(DIK_2))
	{
		sceneNum = STAGE2_SCENE;
	}

	if (input_->PushKey(DIK_3))
	{
		sceneNum = STAGE3_SCENE;
	}

	if (input_->PushKey(DIK_4))
	{
		sceneNum = STAGE4_SCENE;
	}

	if (input_->PushKey(DIK_5))
	{
		sceneNum = STAGE5_SCENE;
	}
}


void GameScene::Draw()
{
	
}


void GameScene::Finalize()
{
	
}

