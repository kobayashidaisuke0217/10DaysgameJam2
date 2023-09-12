#pragma once
#include "Vector4.h"
#include "triangle.h"
#include "BlueMoon.h"

#include "Iscene.h"
#include "Sprite.h"
#include "Texturemanager.h"
#include "Input.h"

class GameScene:public Iscene
{
public:
	~GameScene();
	void Initialize()override;
	void Update()override;
	
	void Draw()override;
	void Finalize()override;
private:

	Texturemanager* textureManager_;
	Input* input_;
	BlueMoon* blueMoon_;
	Sprite* sprite_;
	DirectionalLight directionalLight_;
	uint32_t textureHandle_;

};

