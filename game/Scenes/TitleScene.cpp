#include "TitleScene.h"
#include "ImGuiManger.h"
TitleScene::~TitleScene()
{
}
void TitleScene::Initialize()
{	
	input = Input::GetInstance();
	count = 0;

}

void TitleScene::Update()
{
	
	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::Text("count %d",count);
	ImGui::End();
	if (input->PushKey(DIK_SPACE)) {
		sceneNum = GAME_SCENE;
		count++;
	}

	if (input->PushKey(DIK_1))
	{
		sceneNum = STAGE1_SCENE;
	}

	if (input->PushKey(DIK_2))
	{
		sceneNum = STAGE2_SCENE;
	}

	if (input->PushKey(DIK_3))
	{
		sceneNum = STAGE3_SCENE;
	}

	if (sceneNum < 0) {
		sceneNum = 0;
		
	}
	/*if (count >= 60) {
		sceneNum=GAME_SCENE;
	}*/
}

void TitleScene::Draw()
{
}

void TitleScene::Finalize()
{
}
