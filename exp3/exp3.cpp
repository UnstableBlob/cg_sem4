#include <graphics.h>
#include <stdio.h>
#include <conio.h>

void midcircle(int xc, int yc, int r) {
    int dx, dy, x = 0, y = r;
    int p=(5/4)-r;
    int i=0;

    putpixel(xc,yc,WHITE);


    while(x <= y)
    {
        //plot points

        //1st
        delay(10);
        putpixel(xc+x,yc-y,BLUE); 

        //2nd
        delay(10);
        putpixel(xc+y,yc-x,MAGENTA);

        //3rd
        delay(10);
        putpixel(xc+y,yc+x,CYAN);

        //4th
        delay(10);
        putpixel(xc+x,yc+y,RED);

        //5th
        delay(10);
        putpixel(xc-x,yc+y,GREEN);

        //6th
        delay(10);
        putpixel(xc-y,yc+x,BROWN);

        //7th
        delay(10);
        putpixel(xc-y,yc-x,LIGHTRED);

        //8th
        delay(10);
        putpixel(xc-x,yc-y,YELLOW);








        if(p<0)
        {
            p=p + 2*x + 3; 
        }
        else
        {
            p=p + 2*x - 2*y + 5;
            //decrement y
            y--;
        }
        //increment x
        x++;
    } 


}

int main() {
    int xc, yc,r;
    int gd = DETECT, gm;


    printf("Enter the coords of first point (xc yc) and radius : ");
    scanf("%d %d %d", &xc, &yc, &r);

    

    initgraph(&gd, &gm, (char*)"");
    
    midcircle(xc, yc, r);
    
    getch();
    closegraph();
    return 0;
}