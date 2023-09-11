#include "Stage1Scene.h"

Stage1Scene::~Stage1Scene()
{

}

void Stage1Scene::Initialize()
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
	camera_->SetTarget(&ground_->GetWorldTransform());

	stage1Object_ = new Stage1Object();
	stage1Object_->SetGround(ground_);
	stage1Object_->Initialize();
	DrawFlag = true;
	count = 0;
}

void Stage1Scene::Update()
{
	int hitCount = 0;
	count++;
	
	
	directionalLight_.direction = Normalise(directionalLight_.direction);
	ground_->Update();
	player_->Update();
	stage1Object_->Update();
	
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
	if (count >= 10) {
		if (IsCollision(stage1Object_->GetObbGoal(), player_->GetStructSphere())) {
			sceneNum = CLEAR_SCENE;
		}
		for (int i = 0; i < 6; i++) {

			if (IsCollision(stage1Object_->GetObb(i), player_->GetStructSphere())) {
				//hitCount++;
				
				if (isCount == false) {
					isCount = true;

					player_->SetFlag(true);

					Vector3 v1 = Add(stage1Object_->GetWorldTransform(i).translation_, ground_->GetWorldTransform().rotation_);
					v1 = Multiply(100.0f, v1);
					Vector3 v2 = Add(stage1Object_->GetWorldTransform(i).translation_, ground_->GetWorldTransform().rotation_);
					v2 = Multiply(-100.0f, v2);

   					v1 = Normalise(v1);
					v2 = Normalise(v2);

					const Vector3 cross = Cross(v1, v2);

					player_->SetRotate(cross);
				}
			}
		}

		if (isCount == true) {
			testCount++;
		}

		if (testCount == 10) {
			isCount = false;
			testCount = 0;
		}
	}
	
	if (hitCount != 0) {
		sceneNum = TITLE_SCENE;
	}
	else {
		DrawFlag = true;
	}
	
	viewProjection_.UpdateMatrix();
	
	//viewProjection_.TransferMatrix();

	ImGui::Begin("Scene");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::InputInt("count", &testCount);
	ImGui::End();
}


void Stage1Scene::Draw()
{

	//3D描画準備
	engine_->ModelPreDraw();
	Draw3D();
	//2D描画準備
	engine_->SpritePreDraw();
	Draw2D();
}

void Stage1Scene::Draw3D()
{
	if (!input_->PressKey(DIK_SPACE)) {
		ground_->Draw(viewProjection_, directionalLight_);
	}

	
	player_->Draw(viewProjection_, directionalLight_);

	if (DrawFlag == true) {
		stage1Object_->Draw(viewProjection_, directionalLight_);
	}
	//ワイヤーフレーム描画準備
	//ワイヤーフレームで描画したいものはこれより下に描画処理を書く
	//これより下の3D描画は全てワイヤーフレームになるから注意してね
	engine_->ModelPreDrawWireFrame();
	if (input_->PressKey(DIK_SPACE)) {
		ground_->Draw(viewProjection_, directionalLight_);
	}


}

void Stage1Scene::Draw2D() {



}
void Stage1Scene::Finalize()
{
	camera_->Finalize();
	ground_->Finaleze();
	player_->Finalize();
	stage1Object_->Finalize();
	FlytargetCamera_->Finalize();
	viewProjection_.constBuff_.ReleaseAndGetAddressOf();

}



