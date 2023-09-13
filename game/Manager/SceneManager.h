#pragma once
#include "Iscene.h"
#include "BlueMoon.h"
#include "gameScene.h"
#include "TitleScene.h"
#include "Input.h"
#include "Texturemanager.h"
#include "Stage1Scene.h"
#include "Stage2Scene.h"
#include "Stage3Scene.h"
#include "Stage4Scene.h"
#include "stage5Scene.h"
#include "ClearScene.h"
#include "GameOverScene.h"

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
	
	Texturemanager* textureManager_;

	std::unique_ptr<Iscene> sceneArr_[9];



	int sceneNum_;
	int preSceneNum_;

};

