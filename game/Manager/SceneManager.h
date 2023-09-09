#pragma once
#include <game/Scenes/Iscene.h>
#include "BlueMoon.h"
#include<game/Scenes/gameScene.h>
#include <game/Scenes/TitleScene.h>
#include "Input.h"
#include "Texturemanager.h"
#include "Stage1Scene.h"
#include "Stage2Scene.h"

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
	std::unique_ptr<Iscene> sceneArr_[4];
	int sceneNum_;
	int preSceneNum_;

};

