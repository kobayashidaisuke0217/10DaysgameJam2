#include "SceneManager.h"
#include"ImGuiManger.h"
SceneManager::SceneManager()
{
	
	
	
}
SceneManager::~SceneManager()
{

}
void SceneManager::Run() {
	Init();

	while (true) {
		// メッセージ処理
		if (winApp_->Procesmessage()) {
			break;
		}

		
		Engine->BeginFrame();
		input->Update();
		preSceneNum_ = sceneNum_;
		sceneNum_ = sceneArr_[sceneNum_]->GetSceneNum();

		if (sceneNum_ != preSceneNum_) {
			sceneArr_[preSceneNum_]->Finalize();
			sceneArr_[sceneNum_]->Initialize();
			
		}
		sceneArr_[sceneNum_]->Update();

		
		sceneArr_[sceneNum_]->Draw();
		if (sceneNum_ != CLEAR_SCENE && sceneNum_ != TITLE_SCENE) {
			Engine->SpritePreDraw();
		if (input->PressKey(DIK_ESCAPE)) {
			spritetutrial_->Draw({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, texhandeletutrial_);
				
				
		}
		else {
           sprite_->Draw({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, texhandele_);
		}

		}
		
		

		Engine->Draw();
		Engine->EndFrame();
	}
	CoUninitialize();
	Engine->Finalize();
	sceneArr_[sceneNum_]->Finalize();
	delete sprite_;
	delete spritetutrial_;
}

void SceneManager::Init()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);
	Engine = BlueMoon::GetInstance();
	Engine->Initialize( 1280, 720);
	winApp_ = WinApp::GetInstance();
	input = Input::GetInstance();
	input->Initialize(winApp_);
	textureManager_ = Texturemanager::GetInstance();
	textureManager_->Initialize();

	sceneArr_[TITLE_SCENE] = std::make_unique <TitleScene>();
	sceneArr_[GAME_SCENE] = std::make_unique <GameScene>();
	sceneArr_[STAGE1_SCENE] = std::make_unique <Stage1Scene>();
	sceneArr_[STAGE2_SCENE] = std::make_unique <Stage2Scene>();

	sceneArr_[STAGE3_SCENE] = std::make_unique <Stage3Scene>();
	sceneArr_[STAGE4_SCENE] = std::make_unique <Stage4Scene>();
	sceneArr_[STAGE5_SCENE] = std::make_unique <Stage5Scene>();

	sceneArr_[CLEAR_SCENE] = std::make_unique <ClearScene>();
	sceneArr_[GAMEOVER_SCENE] = std::make_unique <GameOverScene>();

	sceneNum_ = TITLE_SCENE;
	sceneArr_[sceneNum_]->Initialize();
	sprite_ = new Sprite();
	sprite_->Initialize({ 1100.0f,600.0f,0.0f,0.0f }, { 1280.0f,720.0f,0.0f,0.0f });
	texhandele_ = textureManager_->Load("Resource/esc.png");
	spritetutrial_ = new Sprite();
	spritetutrial_->Initialize({ 0.0f,0.0f,0.0f,0.0f }, { 1280.0f,720.0f,0.0f,0.0f });
	texhandeletutrial_ = textureManager_->Load("Resource/tutorial.png");

}


