#include <iostream>
#include <graphics.h>
#include <conio.h>

using namespace std;

// Structure to hold 2D coordinates
struct Point {
    int x, y;
};

// Global variables for the center of the screen
int midX, midY;

// Helper functions to convert Cartesian coordinates to Screen coordinates
int sX(int x) { return midX + x; }
int sY(int y) { return midY - y; } // Subtracted because screen Y grows downwards

// Function to draw X and Y axes
void drawAxes() {
    setcolor(WHITE);
    line(0, midY, midX * 2, midY); // X-axis
    line(midX, 0, midX, midY * 2); // Y-axis
    outtextxy(midX * 2 - 20, midY + 5, (char*)"X");
    outtextxy(midX + 5, 5, (char*)"Y");
}

// Function to draw a triangle given an array of 3 points
void drawTriangle(Point p[], int color) {
    setcolor(color);
    line(sX(p[0].x), sY(p[0].y), sX(p[1].x), sY(p[1].y));
    line(sX(p[1].x), sY(p[1].y), sX(p[2].x), sY(p[2].y));
    line(sX(p[2].x), sY(p[2].y), sX(p[0].x), sY(p[0].y));
}

int main() {
    int gd = DETECT, gm;
    // Note: Change the BGI path if your compiler is installed elsewhere (e.g., "C:\\TC\\BGI")
    initgraph(&gd, &gm, (char*)"");

    // Find the center of the screen to set as our (0,0) origin
    midX = getmaxx() / 2;
    midY = getmaxy() / 2;

    // Define the original object (a triangle in the top-right quadrant)
    Point p[3] = {{40, 40}, {140, 40}, {90, 100}}; 
    Point ref[3]; // Array to hold the transformed points

    // ---------------------------------------------------------
    // PART 1: REFLECTIONS
    // ---------------------------------------------------------
    drawAxes();
    drawTriangle(p, YELLOW);
    outtextxy(10, 10, (char*)"Original (Yellow). Press key for X-Axis Reflection.");
    getch();

    // 1. Reflection about X-axis: x' = x, y' = -y
    for(int i = 0; i < 3; i++) { 
        ref[i].x = p[i].x; 
        ref[i].y = -p[i].y; 
    }
    drawTriangle(ref, LIGHTRED);
    outtextxy(10, 25, (char*)"X-Axis Ref (Light Red). Press key for Y-Axis Reflection.");
    getch();

    // 2. Reflection about Y-axis: x' = -x, y' = y
    for(int i = 0; i < 3; i++) { 
        ref[i].x = -p[i].x; 
        ref[i].y = p[i].y; 
    }
    drawTriangle(ref, LIGHTBLUE);
    outtextxy(10, 40, (char*)"Y-Axis Ref (Light Blue). Press key for Origin Reflection.");
    getch();

    // 3. Reflection about Origin: x' = -x, y' = -y
    for(int i = 0; i < 3; i++) { 
        ref[i].x = -p[i].x; 
        ref[i].y = -p[i].y; 
    }
    drawTriangle(ref, LIGHTGREEN);
    outtextxy(10, 55, (char*)"Origin Ref (Light Green). Press key for SHEAR Operations.");
    getch();

    // ---------------------------------------------------------
    // PART 2: SHEAR OPERATIONS
    // ---------------------------------------------------------
    cleardevice(); // Clear the screen for shear operations
    drawAxes();
    drawTriangle(p, YELLOW);
    
    // 1. X-Shear: x' = x + (shx * y), y' = y
    float shx = 1.5; 
    outtextxy(10, 10, (char*)"Original (Yellow). Press key for X-Shear (shx = 1.5).");
    getch();
    for(int i = 0; i < 3; i++) { 
        ref[i].x = p[i].x + (shx * p[i].y); 
        ref[i].y = p[i].y; 
    }
    drawTriangle(ref, LIGHTMAGENTA);
    outtextxy(10, 25, (char*)"X-Shear (Light Magenta). Press key for Y-Shear.");
    getch();

    // Clear and reset for Y-Shear to avoid visual clutter
    cleardevice(); 
    drawAxes();
    drawTriangle(p, YELLOW);

    // 2. Y-Shear: x' = x, y' = y + (shy * x)
    float shy = 1.5;
    outtextxy(10, 10, (char*)"Original (Yellow). Press key for Y-Shear (shy = 1.5).");
    getch();
    for(int i = 0; i < 3; i++) { 
        ref[i].x = p[i].x; 
        ref[i].y = p[i].y + (shy * p[i].x); 
    }
    drawTriangle(ref, LIGHTCYAN);
    outtextxy(10, 25, (char*)"Y-Shear (Light Cyan). Press any key to exit.");
    getch();

    closegraph();
    return 0;
}