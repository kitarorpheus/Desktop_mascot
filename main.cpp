#include"DxLib.h"
#include"Scene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	SceneMgr_Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		SceneMgr_Update();
		SceneMgr_Draw();
		
	}

	SceneMgr_Finalize();

	DxLib_End();
	return 0;
}