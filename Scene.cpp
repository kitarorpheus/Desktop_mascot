#include"DxLib.h"
#include"Scene.h"
#include"Config.h"
#include"Menu.h"
#include"Minimize.h"

static eScene mScene = eScene_Menu;
static eScene mNextScene = eScene_None;

static void SceneMgr_InitializeModule(eScene scene);
static void SceneMgr_FinalizeModule(eScene scene);

//initialize
void SceneMgr_Initialize() {
	SceneMgr_InitializeModule(mScene);
}

//finalize
void SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(mScene);
}

//update
void SceneMgr_Update() {
	if (mNextScene != eScene_None) {
		SceneMgr_FinalizeModule(mScene);
		mScene = mNextScene;
		mNextScene = eScene_None;
		SceneMgr_InitializeModule(mScene);
	}
	switch (mScene) {
	case eScene_Menu:
		Menu_Update();
		break;
	case eScene_Minimize:
		Minimize_Update();
		break;
	case eScene_Config:
		Config_Update();
		break;
	}
}

void SceneMgr_Draw() {
	switch (mScene) {
	case eScene_Menu:
		Menu_Draw();
		break;
	case eScene_Minimize:
		Minimize_Draw();
		break;
	case eScene_Config:
		Config_Draw();
		break;
	}
}

void SceneMgr_ChangeScene(eScene NextScene) {
	mNextScene = NextScene;
}

static void SceneMgr_InitializeModule(eScene scene) {
	switch (scene) {
	case eScene_Menu:
		Menu_Initialize();
		break;
	case eScene_Minimize:
		Minimize_Initialize();
		break;
	case eScene_Config:
		Config_Initialize();
		break;
	}
}

static void SceneMgr_FinalizeModule(eScene scene) {
	switch (scene)
	{
	case eScene_Menu:
		Menu_Finalize();
		break;
	case eScene_Minimize:
		Minimize_Finalize();
		break;
	case eScene_Config:
		Config_Finalize();
		break;
	}
}