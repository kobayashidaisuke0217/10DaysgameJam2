#pragma once
#include "Vector4.h"
#include "triangle.h"
#include "BlueMoon.h"

#include "game/Scenes/Iscene.h"
#include "Sprite.h"
#include "Sphere.h"
#include "model.h"
#include "worldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "Input.h"
#include "Ground.h"
#include "Player.h"
#include "camera.h"
#include "Stage4Object.h"
#include "FlytargetCamera.h"

class Stage4Scene : public Iscene
{
public:
	~Stage4Scene();
	void Initialize()override;
	void Update()override;

	void Draw()override;
	void Finalize()override;

private:

	BlueMoon* engine_;
	DirectXCommon* directX_;
	Texturemanager* textureManager_;
	ViewProjection viewProjection_;
	Input* input_;
	DirectionalLight directionalLight_;
	camera* camera_;
	FlytargetCamera* FlytargetCamera_;
	Stage4Object* stage4Object_;

	Ground* ground_;
	Player* player_;
	int count = 0;
	bool DrawFlag = true;
	bool cameraChangeFlag;
	int playerHitCount;

	bool isPlayerHit[8];
	void Draw2D();
	void Draw3D();


};

