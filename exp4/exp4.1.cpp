#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

// 4-connected Flood Fill Algorithm
void floodFill4(int x, int y, int new_color, int old_color) {
    int current_color = getpixel(x, y);

    if (current_color == old_color) {
        putpixel(x, y, new_color);
        
        floodFill4(x + 1, y, new_color, old_color);  // Right
        floodFill4(x - 1, y, new_color, old_color);  // Left
        floodFill4(x, y + 1, new_color, old_color);  // Down
        floodFill4(x, y - 1, new_color, old_color);  // Up
    }
}

// 8-connected Flood Fill Algorithm
void floodFill8(int x, int y, int new_color, int old_color) {
    int current_color = getpixel(x, y);

    if (current_color == old_color) {
        putpixel(x, y, new_color);

        // 4-connected neighbors
        floodFill8(x + 1, y, new_color, old_color);      // Right
        floodFill8(x - 1, y, new_color, old_color);      // Left
        floodFill8(x, y + 1, new_color, old_color);      // Down
        floodFill8(x, y - 1, new_color, old_color);      // Up

        // Diagonal neighbors
        floodFill8(x + 1, y + 1, new_color, old_color);  // Bottom-right
        floodFill8(x - 1, y - 1, new_color, old_color);  // Top-left
        floodFill8(x + 1, y - 1, new_color, old_color);  // Top-right
        floodFill8(x - 1, y + 1, new_color, old_color);  // Bottom-left
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    clock_t start, end;
    double cpu_time_used;

    setlinestyle(SOLID_LINE, 0, 3); 
    setcolor(WHITE);
    circle(150, 150, 50);
    
    int old_color = getpixel(150, 150);  // Get the color to be replaced
    
    start = clock();
    floodFill4(150, 150, RED, old_color);
    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("floodFill4 took %f seconds to execute\n", cpu_time_used);

    setlinestyle(SOLID_LINE, 0, 3); 
    setcolor(WHITE);
    circle(350, 350, 50);
    
    old_color = getpixel(350, 350);  // Get the color to be replaced
    
    start = clock();
    floodFill8(350, 350, YELLOW, old_color);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("floodFill8 took %f seconds to execute\n", cpu_time_used);

    getch();
    closegraph();
    return 0;
}