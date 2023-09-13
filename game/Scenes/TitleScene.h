#pragma once
#include "Iscene.h"
#include "Input.h"
#include "Texturemanager.h"
#include "BlueMoon.h"
#include "Sprite.h"

class TitleScene:public Iscene
{
public:
	~TitleScene()override;
	 void Initialize() override;

	 void Update() override;

	 void Draw() override;
	 void Finalize()override;
private:
	Input* input=nullptr;
	Texturemanager* textureManager_;
	BlueMoon* blueMoon_;
	Sprite* sprite_;
	DirectionalLight directionalLight_;
	int Texhandle_;
};

