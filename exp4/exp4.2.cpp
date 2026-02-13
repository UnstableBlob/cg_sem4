#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

void floodFill4(int x, int y, int new_color, int old_color) {
    if (getpixel(x, y) == old_color) {
        putpixel(x, y, new_color);
        floodFill4(x + 1, y, new_color, old_color);
        floodFill4(x - 1, y, new_color, old_color);
        floodFill4(x, y + 1, new_color, old_color);
        floodFill4(x, y - 1, new_color, old_color);
    }
}

void floodFill8(int x, int y, int new_color, int old_color) {
    if (getpixel(x, y) == old_color) {
        putpixel(x, y, new_color);
        floodFill8(x + 1, y, new_color, old_color);
        floodFill8(x - 1, y, new_color, old_color);
        floodFill8(x, y + 1, new_color, old_color);
        floodFill8(x, y - 1, new_color, old_color);
        floodFill8(x + 1, y + 1, new_color, old_color);
        floodFill8(x - 1, y - 1, new_color, old_color);
        floodFill8(x + 1, y - 1, new_color, old_color);
        floodFill8(x - 1, y + 1, new_color, old_color);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    clock_t start, end;
    double cpu_time_used;

    setcolor(RED);
    circle(150, 150, 50);

    setfillstyle(SOLID_FILL, RED);
    floodfill(150, 150, RED);

    
    start = clock();
    floodFill4(150, 150, WHITE, RED); 
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("floodFill4 took %f seconds\n", cpu_time_used);

    setcolor(RED);
    circle(350, 350, 50);
    setfillstyle(SOLID_FILL, RED);
    floodfill(350, 350, RED);
    
    start = clock();
    // Filling the interior (BLACK) with WHITE
    floodFill8(350, 350, WHITE, RED);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("floodFill8 took %f seconds\n", cpu_time_used);

    getch();
    closegraph();
    return 0;
}