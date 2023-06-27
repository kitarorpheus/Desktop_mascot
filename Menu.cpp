#pragma warning(disable: 4996)/*これ書かないとfopenが使えないらしい*/
#include"Menu.h"
#include"Scene.h"
#include"DxLib.h"

#define PI 3.141592654

static int mImageHandle;

int TM;
int TKG = 0;
int t1 = 0;
int t2 = 0;
int mx, my;
int imageC;
int imageP;
int egg[15];
double Angle[2];
int inputcount = 0;
int mouseinput;

void ProgressSave(void) {
	FILE* fp;

	fp = fopen("savedata.dat", "wb");

	if (fp == NULL)return;

	fwrite(&TM, sizeof(TM), 1, fp);

	fclose(fp);
}

void ProgressLoad(void) {
	FILE* fp;

	fp = fopen("savedata.dat", "rb");

	if (fp == NULL)
	{
		TM = 0;
	}
	else
	{
		fread(&TM, sizeof(TM), 1, fp);

		fclose(fp);
	}
}

bool Mouset(int mouse) {
	if (((mouseinput & mouse) != (inputcount & mouse)) && ((mouseinput & mouse) != 0))return true;
	return false;
}

void Menu_Initialize() {
	ProgressLoad();
	imageC = LoadGraph("image/CapD.png");
	imageP = LoadGraph("image/Star.png");
	LoadDivGraph("image/egg.png", 15, 5, 3, 32, 32, egg);
	mImageHandle = LoadGraph("image/BG0.jpg");
}

void Menu_Finalize() {
	DeleteGraph(mImageHandle);
	DeleteGraph(imageC);
	DeleteGraph(imageP);
}

void Menu_Update() {
	mouseinput = GetMouseInput();
	GetMousePoint(&mx, &my);
	
	if (CheckHitKey(KEY_INPUT_1) != 0) { SceneMgr_ChangeScene(eScene_Minimize); }
	if (CheckHitKey(KEY_INPUT_2) != 0) { SceneMgr_ChangeScene(eScene_Config); }

	if (GetMouseInput() & MOUSE_INPUT_LEFT && Mouset(MOUSE_INPUT_LEFT) && 505 <= mx && mx <= 595 && 255 <= my && my <= 345) { Angle[1] = PI / 2; Menu_Draw(); SceneMgr_ChangeScene(eScene_Minimize); }
	if (GetMouseInput() & MOUSE_INPUT_LEFT && Mouset(MOUSE_INPUT_LEFT) && 505 <= mx && mx <= 595 && 355 <= my && my <= 445) { Angle[0] = PI / 2; Menu_Draw(); SceneMgr_ChangeScene(eScene_Config); }
	
	if (505 <= mx && mx <= 595 && 355 <= my && my <= 445) { Angle[0] = PI / 4; }
	else { Angle[0] = 0; }
	if (505 <= mx && mx <= 595 && 255 <= my && my <= 345) { Angle[1] = PI / 4; }
	else { Angle[1] = 0; }

	inputcount = mouseinput;
}

void Menu_Draw() {
	if (TM!=0)
	{
		DrawString(0, 0, "Main Menu", GetColor(255, 255, 255));
		DrawGraph(0, 60, mImageHandle, FALSE);
		DrawString(400, 300, "面倒を見る！", GetColor(0, 0, 0));
		DrawString(420, 400, "せってい", GetColor(0, 0, 0));
		DrawRotaGraph(550, 400, 1.0, Angle[0], imageC, TRUE);
		DrawRotaGraph(550, 300, 1.0, Angle[1], imageP, TRUE);
	}
	else
	{
		if (t1<180)
		{
			DrawFormatString(50, 50, GetColor(255, 255, 255), "おや？");
			DrawRotaGraph(320, 240, 6.0, 0, egg[TKG], FALSE, FALSE);
			if (t1%5 == 0)
			{
				TKG = t2 % 5;
				t2++;
			}
			t1++;
		}
		else if (t1 == 180)
		{
			TKG = 0;
			t1++;
		}
		else if (t1 < 290)
		{
			DrawRotaGraph(320, 240, 6.0, 0, egg[TKG], FALSE, FALSE);
			if (t1 % 10 == 0)
			{
				TKG++;
			}
			t1++;
		}
		else if (t1<530)
		{
			DrawFormatString(50, 50, GetColor(255, 255, 255), "やさぐれたひよこが生まれた！");
			if (t1 % 5 == 0)
			{
				TKG = 10 + t1 % 2;
			}
			DrawRotaGraph(320, 240, 6.0, 0, egg[TKG], FALSE, FALSE);
			t1++;
		}
		else if (t1<770)
		{
			DrawFormatString(50, 50, GetColor(255, 255, 255), "面倒をみてあげよう！");
			if (t1 % 5 == 0)
			{
				TKG = 10 + t1 % 2;
			}
			DrawRotaGraph(320, 240, 6.0, 0, egg[TKG], FALSE, FALSE);
			t1++;
		}
		if (t1 == 770)
		{
			TM++;
			ProgressSave();
		}
	}

}