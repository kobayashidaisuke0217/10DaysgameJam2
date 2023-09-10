#pragma once
#include "Iscene.h"
#include "BlueMoon.h"
#include "gameScene.h"
#include "TitleScene.h"
#include "Input.h"
#include "Texturemanager.h"
#include "Stage1Scene.h"
#include "Stage2Scene.h"
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
	
	Texturemanager* textureManager_;
	std::unique_ptr<Iscene> sceneArr_[5];
	int sceneNum_;
	int preSceneNum_;

};

