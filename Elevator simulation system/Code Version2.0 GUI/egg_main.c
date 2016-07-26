#include <conio.h>
#include "egg.h"
#include "cmc.h"

//void egg_main()
int main()
{
	HEGG egg1;

	EggStart(1200,700);
	DrawBitmap("bitmap//背景.bmp");

//	ShowConsoleWindow(0);

	Sleep(1000);
	egg1=LayEgg();
	MovePen(317,105);
	DrawBitmap("bitmap//外部上行.bmp");

	MovePen(317,169);
	DrawBitmap("bitmap//外部上行.bmp");

	MovePen(317,232);
	DrawBitmap("bitmap//外部上行.bmp");

	MovePen(317,298);
	DrawBitmap("bitmap//外部上行.bmp");

	MovePen(317,363);
	DrawBitmap("bitmap//外部上行.bmp");

	MovePen(317,425);
	DrawBitmap("bitmap//外部上行.bmp");

	MovePen(317,492);
	DrawBitmap("bitmap//外部上行.bmp");

	MovePen(317,557);
	DrawBitmap("bitmap//外部上行.bmp");


	MovePen(317,141);
	DrawBitmap("bitmap//外部下行.bmp");

	MovePen(317,204);
	DrawBitmap("bitmap//外部下行.bmp");

	MovePen(317,270);
	DrawBitmap("bitmap//外部下行.bmp");

	MovePen(317,335);
	DrawBitmap("bitmap//外部下行.bmp");

	MovePen(317,397);
	DrawBitmap("bitmap//外部下行.bmp");

	MovePen(317,464);
	DrawBitmap("bitmap//外部下行.bmp");

	MovePen(317,529);
	DrawBitmap("bitmap//外部下行.bmp");

	MovePen(317,594);
	DrawBitmap("bitmap//外部下行.bmp");

	MovePen(1122,157);
	DrawBitmap("bitmap//内部1-1.bmp");

	MovePen(1122,219);
	DrawBitmap("bitmap//内部2-1.bmp");

	MovePen(1122,273);
	DrawBitmap("bitmap//内部3-1.bmp");

	MovePen(1122,328);
	DrawBitmap("bitmap//内部4-1.bmp");

	MovePen(1044,155);
	DrawBitmap("bitmap//内部5-1.bmp");

	MovePen(1044,218);
	DrawBitmap("bitmap//内部6-1.bmp");

	MovePen(1044,274);
	DrawBitmap("bitmap//内部7-1.bmp");

	MovePen(1044,329);
	DrawBitmap("bitmap//内部8-1.bmp");

	MovePen(1044,388);
	DrawBitmap("bitmap//内部9-1.bmp");

	MovePen(1116,460);
	DrawBitmap("bitmap//GO2.bmp");

	MovePen(1047,457);
	DrawBitmap("bitmap//不GO2.bmp");

	Sleep(15000);
	EatEgg();
	

	getch();
	return 0;
}