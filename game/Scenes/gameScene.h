#pragma once
#include "Vector4.h"
#include "triangle.h"
#include "BlueMoon.h"

#include "Iscene.h"
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
#include "ObjectBale.h"
#include "Plane.h"
#include "FlytargetCamera.h"
class GameScene:public Iscene
{
public:
	~GameScene();
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
	ObjectBale* Ball_;
	Plane* plane_;
	WorldTransform worldtransformPlane_;
	Ground* ground_;
	Player* player_;
	uint32_t textureHandle_;
	bool cameraChangeFlag;
	void Draw2D();
	void Draw3D();
 
};

