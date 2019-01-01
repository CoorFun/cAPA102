#include "cAPA102.h"
#include <stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
    int bri = 0;
    int dir = 0;
    int time = 0;
    cAPA102_Init(12, 0, 0, 31);
    int i;
    for ( i = 0; i < 3; i++)
        cAPA102_Set_Pixel_4byte(i, 0xFF0000);
        //cAPA102_Set_Pixel_RGB(i, 255, 0, 0);

    for ( i = 3; i < 6; i++)
        cAPA102_Set_Pixel_4byte(i, 0x00FF00);
        //cAPA102_Set_Pixel_RGB(i, 0, 255, 0);

    for ( i = 6; i < 9; i++)
        cAPA102_Set_Pixel_4byte(i, 0x0000FF);
        //cAPA102_Set_Pixel_RGB(i, 0, 0, 255);

    for ( i = 9; i < 12; i++)
        cAPA102_Set_Pixel_4byte(i, 0x00FFFF);
        //cAPA102_Set_Pixel_RGB(i, 255, 255, 0);

    cAPA102_Refresh();

    while( time < 1000 ){
        if (!dir)
            bri++;
        if (dir)
            bri--;
        if (bri == 31)
            dir = 1;
        if (bri == 0)
            dir = 0;

        cAPA102_Change_Brightness(bri);
        usleep(5000);
        time++;
    }

    cAPA102_Clear_All();
    return 0;
}