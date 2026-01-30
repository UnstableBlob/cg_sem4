#include <graphics.h>
#include <stdio.h>
#include <conio.h>

void bresenham(int x1, int y1, int x2, int y2) {
    int dx, dy, x = x1, y = y1;
    int p;
    int i=0;

    dx = x2 - x1;
    dy = y2 - y1;


    p = 2 * dy - dx;

    while (x <= x2) {
        if((x % 10) < 5)
        {
            putpixel(x, y, WHITE);
        }

            if (p < 0) {
                p = p + 2 * dy;
            } 
            else {
                p = p + 2 * dy - 2 * dx;
                y++;
            }
        x++;
    }
}

int main() {
    int x1, y1, x2, y2;
    int gd = DETECT, gm;


    printf("Enter the coords of first point (x1 y1): ");
    scanf("%d %d", &x1, &y1);
    
    printf("Enter the coords of 2nd point (x2 y2): ");
    scanf("%d %d", &x2, &y2);

    initgraph(&gd, &gm, (char*)"");
    
    bresenham(x1, y1, x2, y2);
    
    getch();
    closegraph();
    return 0;
}