#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "cmc.h"
#include "egg.h"
#define NUMBER_OF_EGG 6
HEGG hEggs[NUMBER_OF_EGG];
extern HEGG main_egg;

void egg_celue()
{
	SetActiveEgg(main_egg);
    switch(strategy)
	{
  	case 1:	
			while (bitmap==1);
			ng=1;
			hEggs[1]=LayEgg();
			SetActiveEgg(main_egg);
  		    MovePen(479,700);
  		    DrawBitmap("bitmap//celue1-2.bmp");
  		    MovePen(394,431);
  		    DrawBitmap("bitmap//strategy1-1.bmp");
			ng=0;
  		    break;
        case 2:
			while (bitmap==1);
			ng=1;
            hEggs[2]=LayEgg();
			SetActiveEgg(main_egg);
  		    MovePen(479,700);
  		    DrawBitmap("bitmap//celue2-2.bmp");
  		    MovePen(394,431);
  		    DrawBitmap("bitmap//strategy2-1.bmp");
			ng=0;
  		    break;
        case 3:
			while (bitmap==1);
			ng=1;

            hEggs[3]=LayEgg();
			SetActiveEgg(main_egg);
  		    MovePen(479,700);
  		    DrawBitmap("bitmap//celue3-2.bmp");
  		    MovePen(394,431);
  		    DrawBitmap("bitmap//strategy3-1.bmp");
			ng=0;
  		    break;
        case 4:
			while (bitmap==1);
			ng=1;
            hEggs[4]=LayEgg();
			SetActiveEgg(main_egg);
  		    MovePen(479,700);
  		    DrawBitmap("bitmap//celue4-2.bmp");
  		    MovePen(394,431);
  		    DrawBitmap("bitmap//strategy4-1.bmp");
			ng=0;
  		    break;
        case 5:
			while (bitmap==1);
			ng=1;
            hEggs[5]=LayEgg();
			SetActiveEgg(main_egg);
  		    MovePen(479,700);
  		    DrawBitmap("bitmap//celue5-2.bmp");
  		    MovePen(394,431);
  		    DrawBitmap("bitmap//strategy5-1.bmp");
			ng=0;
  		    break;
        default:
            break;
      }	
}
