#pragma once
enum  Scene {
	TITLE_SCENE,
	GAME_SCENE,
	STAGE1_SCENE,
	STAGE2_SCENE,

	STAGE3_SCENE,
	STAGE4_SCENE,

	CLEAR_SCENE

};
class Iscene
{
public:
	virtual ~Iscene() {};
	virtual void Initialize()=0;

	virtual void Update()=0;

	virtual void Draw()=0;

	virtual void Finalize() = 0;
	 int GetSceneNum() { return sceneNum; }

protected:

	static int sceneNum;
};

