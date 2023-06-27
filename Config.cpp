#include"Config.h"
#include"Scene.h"
#include"DxLib.h"

static int mImageHandle;
int charaNum;
extern int mx, my;
int back[2];
int mode;
int inputcount2 = 0;
int mouseinput2;
extern int TM;
extern void ProgressSave();
extern void ProgressLoad();
int white = GetColor(255, 255, 255);
int green = GetColor(0, 255, 0);
int color[5];
int prv[18];
int star;
double size = 50;

extern bool Mouset2(int mouse) {
	if (((mouseinput2 & mouse) != (inputcount2 & mouse)) && ((mouseinput2 & mouse) != 0))return true;
	return false;
}

void Config_Initialize() {
	mImageHandle = LoadGraph("image/BG1.png");
	back[0] = LoadGraph("image/back1.png");
	back[1] = LoadGraph("image/back2.png");
	star = LoadGraph("image/Star.png");
}

void Config_Finalize() {
	DeleteGraph(mImageHandle);
	DeleteGraph(back[0]);
	DeleteGraph(back[1]);
	DeleteGraph(star);
}

void Config_Update() {
	mouseinput2 = GetMouseInput();
	GetMousePoint(&mx, &my);

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { SceneMgr_ChangeScene(eScene_Menu); }
	if (GetMouseInput() & MOUSE_INPUT_LEFT && Mouset2(MOUSE_INPUT_LEFT) && 20 <= mx && mx <= 80 && 60 <= my && my <= 80) { mx = 0; my = 0; charaNum = 1; }
	if (GetMouseInput() & MOUSE_INPUT_LEFT && Mouset2(MOUSE_INPUT_LEFT) && 20 <= mx && mx <= 120 && 80 <= my && my <= 100) { mx = 0; my = 0; charaNum = 2; }
	if (GetMouseInput() & MOUSE_INPUT_LEFT && Mouset2(MOUSE_INPUT_LEFT) && 20 <= mx && mx <= 100 && 100 <= my && my <= 120) { mx = 0; my = 0; charaNum = 3; }
	if (TM>8640)
	{
		if (GetMouseInput() & MOUSE_INPUT_LEFT && Mouset2(MOUSE_INPUT_LEFT) && 20 <= mx && mx <= 80 && 120 <= my && my <= 140) { mx = 0; my = 0; charaNum = 4; }
	}
	if (GetMouseInput() & MOUSE_INPUT_LEFT && Mouset2(MOUSE_INPUT_LEFT) && 20 <= mx && mx <= 100 && 140 <= my && my <= 160) { mx = 0; my = 0; charaNum = 5; }

	if (GetMouseInput() & MOUSE_INPUT_LEFT && Mouset2(MOUSE_INPUT_LEFT) && 505 <= mx && mx <= 595 && 355 <= my && my <= 445) { mode = 1; Config_Draw(); SceneMgr_ChangeScene(eScene_Menu); }
	else { mode = 0; }

	inputcount2 = mouseinput2;
}

void Config_Draw() {
	DrawGraph(0, 60, mImageHandle, TRUE);
	DrawString(0, 0, "Config", GetColor(255, 255, 255));
	DrawString(0, 40, "Select charactor", GetColor(255, 255, 255));
	DrawString(250, 30, "Size", GetColor(255, 0, 0));
	DrawLine(300, 40, 400, 40, GetColor(255, 0, 0));
	DrawRotaGraph(300 + size, 40, 0.25, 0, star, TRUE, FALSE);
	DrawFormatString(0, 400, GetColor(255, 255, 255), "稼働時間:%d秒", TM*10);
	
	if (GetMouseInput() & MOUSE_INPUT_LEFT && 300 <= mx && mx <= 400 && 30 <= my && my <= 50)
	{
		size = mx - 300;
	}
	
	switch (mode)
	{
	case 1:
		DrawRotaGraph(550, 400, 1.0, 0, back[1], TRUE);
		break;
	default:
		DrawRotaGraph(550, 400, 1.0, 0, back[0], TRUE);
		break;
	}

	for (int i = 0; i < 5; i++)
	{
		color[i] = white;
	}

	switch (charaNum)
	{
	case 2:
		color[1] = green;
		LoadDivGraph("image/chic1.png", 18, 6, 3, 32, 32, prv);
		break;
	case 3:
		color[2] = green;
		LoadDivGraph("image/chic2.png", 18, 6, 3, 32, 32, prv);
		break;
	case 4:
		color[3] = green;
		LoadDivGraph("image/chic3.png", 18, 6, 3, 32, 32, prv);
		break;
	case 5:
		color[4] = green;
		LoadDivGraph("image/chic4.png", 18, 6, 3, 32, 32, prv);
		break;
	default:
		color[0] = green;
		LoadDivGraph("image/chic0.png", 18, 6, 3, 32, 32, prv);
		break;
	}

	DrawRotaGraph(320, 240, 1+size/10, 0, prv[5], TRUE, FALSE);
	DrawString(20, 60, "ひよこ", color[0]);
	DrawString(20, 80, "ひよこレディ", color[1]);
	DrawString(20, 100, "ワルひよこ", color[2]);
	if (TM>8640)
	{
		DrawString(20, 120, "ニワとり", color[3]);
	}
	DrawString(20, 140, "メカひよこ", color[4]);

}