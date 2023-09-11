#pragma once
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
#include "Stage5Object.h"
#include "FlytargetCamera.h"

class Stage5Scene : public Iscene
{
public:
	~Stage5Scene();
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
	Stage5Object* stage5Object_;

	Ground* ground_;
	Player* player_;
	void Draw2D();
	void Draw3D();


};


