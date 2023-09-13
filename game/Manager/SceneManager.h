#pragma once
#include "Iscene.h"
#include "BlueMoon.h"
#include "gameScene.h"
#include "TitleScene.h"
#include "Input.h"
#include "Sprite.h"
#include "Texturemanager.h"
#include "Stage1Scene.h"
#include "Stage2Scene.h"
#include "Stage3Scene.h"
#include "Stage4Scene.h"
#include "stage5Scene.h"
#include "ClearScene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	
	void Run();
	void Init();
private:
	BlueMoon* Engine;
	WinApp* winApp_ = nullptr;
	Input* input ;
	Sprite* sprite_;
	Sprite* spritetutrial_;
	Texturemanager* textureManager_;
	int texhandele_;
	int texhandeletutrial_;
	std::unique_ptr<Iscene> sceneArr_[8];



	int sceneNum_;
	int preSceneNum_;

};

