#include "gameScene.h"


GameScene::~GameScene()
{
	
}

void GameScene::Initialize()
{
	engine_ = BlueMoon::GetInstance();

	directX_ = DirectXCommon::GetInstance();

	textureManager_ = Texturemanager::GetInstance();
	
    directionalLight_ = { {1.0f,1.0f,1.0f,1.0f},{0.0f,-1.0f,0.0f},1.0f };
	input_ = Input::GetInstance();
	viewProjection_.Initialize();
	ground_ = new Ground();
	ground_->Initialize();
	player_ = new Player();
	player_->Initialize();
	player_->SetTarget(&ground_->GetWorldTransform());
	camera_ = new camera();
	camera_->Initialize();
	camera_->SetTarget(&player_->GetWorldTransform());
	player_->SetViewProjection(&camera_->GetViewProjection());
}

void GameScene::Update()
{
	directionalLight_.direction = Normalise(directionalLight_.direction);
	ground_->Update();
	player_->Update();
	camera_->Update();
	viewProjection_.rotation_ = camera_->GetViewProjection().rotation_;
	viewProjection_.translation_ = camera_->GetViewProjection().translation_;
	viewProjection_.matView = camera_->GetViewProjection().matView;
	viewProjection_.matProjection = camera_->GetViewProjection().matProjection;
	viewProjection_.UpdateMatrix();
	//viewProjection_.TransferMatrix();
	
	
}


void GameScene::Draw()
{
	
	//3D描画準備
	engine_->ModelPreDraw();
	Draw3D();
	//2D描画準備
	engine_->SpritePreDraw();
	Draw2D();
}

void GameScene::Draw3D()
{
	ground_->Draw(viewProjection_, directionalLight_);

	player_->Draw(viewProjection_, directionalLight_);

	//ワイヤーフレーム描画準備
	//ワイヤーフレームで描画したいものはこれより下に描画処理を書く
	//これより下の3D描画は全てワイヤーフレームになるから注意してね
	engine_->ModelPreDrawWireFrame();
	


}

void GameScene::Draw2D() {

	

}
void GameScene::Finalize()
{
	camera_->Finalize();
	ground_->Finaleze();
	player_->Finalize();
	viewProjection_.constBuff_.ReleaseAndGetAddressOf();
	
}

