#include "Stage2Scene.h"

Stage2Scene::~Stage2Scene()
{

}

void Stage2Scene::Initialize()
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
	FlytargetCamera_ = new FlytargetCamera();
	FlytargetCamera_->Initialize();
	FlytargetCamera_->SetTarget(&player_->GetWorldTransform());
	player_->SetCamera(FlytargetCamera_);
	camera_ = new camera();
	camera_->Initialize();
	camera_->SetTarget(&player_->GetWorldTransform());
	
	stage2Object_ = new Stage2Object();
	stage2Object_->SetGround(ground_);
	stage2Object_->Initialize();
	DrawFlag = true;
}

void Stage2Scene::Update()
{
	int hitCount = 0;
	for (int i = 0; i < 6; i++) {
		if (IsCollision(stage2Object_->GetObb(i), player_->GetStructSphere())) {
			hitCount++;
		}

	}
	if (hitCount != 0) {
		DrawFlag = false;
	}
	else {
		DrawFlag = true;
	}
	directionalLight_.direction = Normalise(directionalLight_.direction);
	ground_->Update();
	player_->Update();

	if (player_->GetCameraFlag() == false) {
		camera_->Update();
		viewProjection_.rotation_ = camera_->GetViewProjection().rotation_;
		viewProjection_.translation_ = camera_->GetViewProjection().translation_;
		viewProjection_.matView = camera_->GetViewProjection().matView;
		viewProjection_.matProjection = camera_->GetViewProjection().matProjection;
	}
	else {
		FlytargetCamera_->Update();
		viewProjection_.rotation_ = FlytargetCamera_->GetViewProjection().rotation_;
		viewProjection_.translation_ = FlytargetCamera_->GetViewProjection().translation_;
		viewProjection_.matView = FlytargetCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = FlytargetCamera_->GetViewProjection().matProjection;
	}
	ground_->SetPlayerMoveFlag(player_->GetCameraFlag());
	viewProjection_.UpdateMatrix();
	stage2Object_->Update();
	//viewProjection_.TransferMatrix();

	ImGui::Begin("Scene");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::End();
}


void Stage2Scene::Draw()
{

	//3D描画準備
	engine_->ModelPreDraw();
	Draw3D();
	//2D描画準備
	engine_->SpritePreDraw();
	Draw2D();
}

void Stage2Scene::Draw3D()
{
	/*if (!input_->PressKey(DIK_SPACE)) {
		ground_->Draw(viewProjection_, directionalLight_);
	}
	*/
	if (player_->GetCameraFlag() == false) {
		player_->Draw(viewProjection_, directionalLight_);
	}
	if (DrawFlag == true) {
		stage2Object_->Draw(viewProjection_, directionalLight_);
	}
	//ワイヤーフレーム描画準備
	//ワイヤーフレームで描画したいものはこれより下に描画処理を書く
	//これより下の3D描画は全てワイヤーフレームになるから注意してね
	engine_->ModelPreDrawWireFrame();
	if (input_->PressKey(DIK_SPACE)) {
		ground_->Draw(viewProjection_, directionalLight_);
	}


}

void Stage2Scene::Draw2D() {



}
void Stage2Scene::Finalize()
{
	camera_->Finalize();
	ground_->Finaleze();
	player_->Finalize();
	stage2Object_->Finalize();
	FlytargetCamera_->Finalize();
	viewProjection_.constBuff_.ReleaseAndGetAddressOf();

}
