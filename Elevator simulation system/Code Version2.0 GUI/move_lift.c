#include "egg.h"
#include "cmc.h"

extern HEGG main_egg;//主蛋的句柄
int action=0;//=0表示不在动画 =1表示在动画

void move_lift(int act)//实现电梯的动画上升(act=1 表示上升一层 act=-1表示下降1层 act=0停靠并切换图片 act=2表示关门准备出发 act=-2表示空闲)
{
	static HEGG egg1=NULL;//电梯蛋句柄，专用于电梯的动画
	int i;
	static int flag=0;//没空闲

	if (egg1==NULL)
	{
		while (bitmap==1);
		egg1=LayEgg();
		MovePen(11,114);
		DrawBitmap("bitmap//电梯1.bmp");
	}//电梯蛋的初始化

	switch (act)
	{
	case -11://降两层（宏福）
		if (flag==1)
		{
			while (bitmap==1);
			SetActiveEgg(egg1);
			action=1;
			MovePen(GetPenXPos()-265,GetPenYPos());
			DrawBitmap("bitmap//电梯1.bmp");
			action=0;
			flag=0;
			SetActiveEgg(main_egg);
		}
		for (i=1;i<=CUT;i++)
		{
			while (bitmap==1);
			action=1;
			SetActiveEgg(egg1);
			MoveEgg(GetEggXPos(),GetEggYPos()-6.35);
			action=0;
			WaitFor(delay/CUT);
		}
		break;	
	case 1://升一层
		if (flag==1)
		{
			while (bitmap==1);
			action=1;
			SetActiveEgg(egg1);
			MovePen(GetPenXPos()-265,GetPenYPos());
			DrawBitmap("bitmap//电梯1.bmp");
			action=0;
			SetActiveEgg(main_egg);
			flag=0;
		}
		for (i=1;i<=CUT;i++)
		{
			while (bitmap==1);
			action=1;
			SetActiveEgg(egg1);
			MoveEgg(GetEggXPos(),GetEggYPos()+3.175);
			action=0;
			WaitFor(delay/CUT);
		}
		break;
	case -1://降一层
		if (flag==1)
		{
			while (bitmap==1);
			SetActiveEgg(egg1);
			action=1;
			MovePen(GetPenXPos()-265,GetPenYPos());
			DrawBitmap("bitmap//电梯1.bmp");
			action=0;
			flag=0;
			SetActiveEgg(main_egg);
		}
		for (i=1;i<=CUT;i++)
		{
			while (bitmap==1);
			action=1;
			SetActiveEgg(egg1);
			MoveEgg(GetEggXPos(),GetEggYPos()-3.175);
			action=0;
			WaitFor(delay/CUT);
		}
		break;
	case 0://停靠
		while (bitmap==1);
		SetActiveEgg(egg1);
		MovePen(GetPenXPos()-265,GetPenYPos());
		DrawBitmap("bitmap//电梯2.bmp");

	{
		SetActiveEgg(main_egg);
	

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门1.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门2.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门3.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门4.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门5.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门6.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门7.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门8.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门9.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门10.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门11.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门12.bmp");
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门13.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门14.bmp");
		action=0;
		WaitFor(delay/CUT);

		
		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门15.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门16.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门17.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门18.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门19.bmp");
		action=0;
		WaitFor(delay/CUT);

		while (bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//电梯门20.bmp");
		action=0;
	
	}//一套电梯开门动画

	//	WaitFor(delay);
		break;
	case 2://关门出发
		while (bitmap==1);
		SetActiveEgg(egg1);
		MovePen(GetPenXPos()-265,GetPenYPos());
		DrawBitmap("bitmap//电梯1.bmp");
		{
			SetActiveEgg(main_egg);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门20.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门19.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门18.bmp");
			action=0;
			WaitFor(delay/CUT);

			
			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门17.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门16.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门15.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门14.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门13.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门12.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门11.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门10.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门9.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门8.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门7.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门6.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门5.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门4.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门3.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门2.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门1.bmp");
			action=0;
			WaitFor(delay/CUT);

			while (bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//电梯门.bmp");
			action=0;
		}

		//WaitFor(delay);
		break;
	case -2://空闲
		flag=1;//空闲了

		while (bitmap==1);
		SetActiveEgg(egg1);
		MovePen(GetPenXPos()-265,GetPenYPos());
		DrawBitmap("bitmap//电梯0.bmp");
		WaitFor(delay);
		break;
	default:
		break;
	}
	
	SetActiveEgg(main_egg);

	return;
}
