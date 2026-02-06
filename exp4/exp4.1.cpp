#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include<time.h>

void boundaryFill4(int x, int y, int fill_color, int boundary_color) {
    int current_color = getpixel(x, y);


    if (current_color != boundary_color && current_color != fill_color) {
        
        putpixel(x, y, fill_color);
        boundaryFill4(x + 1, y, fill_color, boundary_color);
        boundaryFill4(x - 1, y, fill_color, boundary_color); 
        boundaryFill4(x, y + 1, fill_color, boundary_color); 
        boundaryFill4(x, y - 1, fill_color, boundary_color); 
    }
}

void boundaryFill8(int x, int y, int fill_color, int boundary_color) {
    int current_color = getpixel(x, y);

    if (current_color != boundary_color && current_color != fill_color) {
        
        putpixel(x, y, fill_color);

        boundaryFill8(x + 1, y, fill_color, boundary_color); 
        boundaryFill8(x - 1, y, fill_color, boundary_color); 
        boundaryFill8(x, y + 1, fill_color, boundary_color); 
        boundaryFill8(x, y - 1, fill_color, boundary_color); 

        boundaryFill8(x + 1, y + 1, fill_color, boundary_color); 
        boundaryFill8(x - 1, y - 1, fill_color, boundary_color); 
        boundaryFill8(x + 1, y - 1, fill_color, boundary_color); 
        boundaryFill8(x - 1, y + 1, fill_color, boundary_color); 
    }
}


int main() {
    int x1, y1, x2, y2;
    x1 = 100;
    x2 = 200;
    y1=100;
    y2 = 200;
    int gd = DETECT, gm;


    initgraph(&gd, &gm, (char*)"");


    clock_t start, end;
    double cpu_time_used;


    setcolor(WHITE);
    setlinestyle(SOLID_LINE, 0, 3); 
    circle(150,150,50);
    
    start = clock();
    boundaryFill4(150, 150, RED, WHITE);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("boundaryFill4 took %f seconds to execute \n", cpu_time_used);

    x1 = 300;
    x2 = 400;
    y1  = 300;
    y2 = 400;

    setcolor(WHITE);
    circle(350,350,50);
    
    start = clock();
    boundaryFill8(350, 350, RED, WHITE);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("boundaryFill8 took %f seconds to execute \n", cpu_time_used);



    // x1 = 300;
    // x2 = 400;
    // y1  = 300;
    // y2 = 400;

    // setlinestyle(SOLID_LINE, 0, 3); 
    // circle(350, 350, 100);  

    // boundaryFill8(300,300,GREEN,WHITE);


    // int arr[] = {320, 150, 400, 250, 250, 350, 320, 150};
    // drawpoly(4, arr);

    // boundaryFill8(350,200,RED,WHITE);

    // int star[] = {
    // 350, 150,  // Top point
    // 380, 240,  // Inner upper-right
    // 470, 240,  // Right point
    // 400, 300,  // Inner lower-right
    // 430, 390,  // Bottom-right point
    // 350, 330,  // Inner bottom
    // 270, 390,  // Bottom-left point
    // 300, 300,  // Inner lower-left
    // 230, 240,  // Left point
    // 320, 240,  // Inner upper-left
    // 350, 150   // Back to Top (to close)
    // };

    // setcolor(WHITE);
    // drawpoly(11, star);

    // boundaryFill4(350,200,RED,WHITE);


    
    getch();
    closegraph();
    return 0;
}