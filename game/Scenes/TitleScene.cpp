#include "TitleScene.h"
#include "ImGuiManger.h"
TitleScene::~TitleScene()
{
}
void TitleScene::Initialize()
{	
	input = Input::GetInstance();
}

void TitleScene::Update()
{
	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::Text("Push To Space");
	ImGui::End();

	if (input->PushKey(DIK_SPACE))
	{
		sceneNum = GAME_SCENE;
	}
}

void TitleScene::Draw()
{
}

void TitleScene::Finalize()
{
}
