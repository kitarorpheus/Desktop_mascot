#include"Minimize.h"
#include"Scene.h"
#include"DxLib.h"
#include<math.h>

#define PI 3.14159265359

/*60fpsのモニタだと考える*/

//グローバル変数
int model[18];
int image;
int time = 0;
int pattern = 0;
int e;
double f;
RECT rc;
DxLib::VECTOR charaPos;
extern int charaNum;
extern double size;
extern int mx, my;
extern int TM;
extern void ProgressSave();
extern void ProgressLoad();

void Minimize_Initialize() { ; }
void Minimize_Finalize() { ; }
void Minimize_Update() { 
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //うまくいかず、MinimizeからMenuに戻れない
		SetAlwaysRunFlag(FALSE);
		HWND HwND = GetMainWindowHandle();
		SetWindowPos(HwND, HWND_NOTOPMOST, 632, 256, 656, 519, SWP_ASYNCWINDOWPOS);
		SetUseBackBufferTransColorFlag(FALSE);
		SetWindowStyleMode(0);
		SetGraphMode(656, 519, 32);
		
		SceneMgr_ChangeScene(eScene_Menu);
	}
}

//前処理
void preInitialize() {
	//Display resolution
	GetWindowRect(GetDesktopWindow(), &rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	charaPos.x = width / 2;
	charaPos.y = height / 2;

	//set resolution, windowmode
	DxLib::ChangeWindowMode(TRUE);
	DxLib::SetGraphMode(width, height, 32);
	DxLib::SetWindowStyleMode(2);
	DxLib::SetUseBackBufferTransColorFlag(TRUE);
}

void afterInitialize() {
	SetFontSize(32);

	//make window in the flont
	HWND hWnd = GetMainWindowHandle();
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	DxLib::SetAlwaysRunFlag(TRUE);//always active even if no-active
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	switch (charaNum)
	{
	case 1:
		LoadDivGraph("image/chic0.png", 18, 6, 3, 32, 32, model);
		break;
	case 2:
		LoadDivGraph("image/chic1.png", 18, 6, 3, 32, 32, model);
		break;
	case 3:
		LoadDivGraph("image/chic2.png", 18, 6, 3, 32, 32, model);
		break;
	case 4:
		LoadDivGraph("image/chic3.png", 18, 6, 3, 32, 32, model);
		break;
	case 5:
		LoadDivGraph("image/chic4.png", 18, 6, 3, 32, 32, model);
		break;
	default:
		LoadDivGraph("image/chic0.png", 18, 6, 3, 32, 32, model);
		break;
	}
	
}

void mainProcess() {
	while (DxLib::ProcessMessage() == 0) {
		DxLib::ClearDrawScreen();

		const float speed = 12;
		int Vx = charaPos.x, Vy = charaPos.y;
		int dx = charaPos.x, dy = charaPos.y;

		if (time % 20 == 0) {
			pattern = GetRand(10);
			e = 0;
		}

		switch (pattern)
		{
		case 1:
			Vx += speed;
			f = 16 + sin((PI * e + PI) / 2);
			image = model[(int)f];
			break;
		case 2:
			Vx -= speed;
			f = 13 + sin((PI * e + PI) / 2);
			image = model[(int)f];
			break;
		case 3:
			Vy += speed;
			f = 7 + sin((PI * e + PI) / 2);
			image = model[(int)f];
			break;
		case 4:
			Vy -= speed;
			f = 10 + sin((PI * e + PI) / 2);
			image = model[(int)f];
			break;
		case 9:
			break;
		default:
			f = e % 2;
			image = model[(int)f];
			break;
		}

		if (DxLib::CheckHitKey(KEY_INPUT_RIGHT))Vx += speed;
		if (DxLib::CheckHitKey(KEY_INPUT_LEFT))Vx -= speed;
		if (DxLib::CheckHitKey(KEY_INPUT_UP))Vy -= speed;
		if (DxLib::CheckHitKey(KEY_INPUT_DOWN))Vy += speed;

		if (!((Vx <= rc.right - 96) && (Vx >= rc.left + 96) && (Vy <= rc.bottom - 96) && (Vy >= rc.top + 96))) {
			Vx = charaPos.x;
			Vy = charaPos.y;
			pattern = 0;
			continue;
		}//壁面調整

		dx = charaPos.x;
		dy = charaPos.y;
		charaPos.x = Vx;
		charaPos.y = Vy;


		if (GetMouseInput()&MOUSE_INPUT_LEFT)
		{
			pattern = 9;
			GetMousePoint(&Vx, &Vy);
			if (!((Vx <= rc.right - 96) && (Vx >= rc.left + 96) && (Vy <= rc.bottom - 96) && (Vy >= rc.top + 96))) {
				Vx = charaPos.x;
				Vy = charaPos.y;
				continue;
			}//壁面調整
			charaPos.x = Vx;
			charaPos.y = Vy;
			f = 3 + e % 2;
			image = model[(int)f];
		}
		else if (pattern == 9)
		{
			while (time%20 < 19)
			{
				time++;
			}
		}

		DxLib::DrawRotaGraph(charaPos.x, charaPos.y, 1 + size / 10, 0, image, FALSE, FALSE);

		time++;
		e++;

		if (time%600==0)
		{/*10sごとに記録*/
			TM++;
			ProgressSave();
		}

		DxLib::ScreenFlip();

		if (GetMouseInput() & MOUSE_INPUT_MIDDLE)
		{
			PostQuitMessage(1);
		}
	}
}

void Minimize_Draw() {
	preInitialize();
	afterInitialize();
	mainProcess();
}