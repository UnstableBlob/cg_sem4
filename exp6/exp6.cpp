#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

// Function to draw a triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

// Translation
void translate(int &x, int &y, int tx, int ty) {
    x = x + tx;
    y = y + ty;
}

// Scaling
void scale(int &x, int &y, int refX, int refY, float sx, float sy) {
    x = refX + (x - refX) * sx;
    y = refY + (y - refY) * sy;
}

// Rotation
void rotate(int &x, int &y, int refX, int refY, float angle) {
    float rad = angle * 3.14159 / 180.0;
    int newX = refX + (x - refX) * cos(rad) - (y - refY) * sin(rad);
    int newY = refY + (x - refX) * sin(rad) + (y - refY) * cos(rad);
    x = newX;
    y = newY;
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");


    // Original triangle coordinates (made bigger)
    int x1 = 80, y1 = 350;
    int x2 = 180, y2 = 150;
    int x3 = 280, y3 = 350;

    // Draw original triangle
    setcolor(WHITE);
    outtextxy(10, 10, (char*)"Original Triangle (WHITE)");
    drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);

    int cx1 = x1, cy1 = y1, cx2 = x2, cy2 = y2, cx3 = x3, cy3 = y3;
    translate(cx1, cy1, 150, 50);
    translate(cx2, cy2, 150, 50);
    translate(cx3, cy3, 150, 50);

    int refX = 150, refY = 150;

    scale(cx1, cy1, refX, refY, 0.5, 0.5);
    scale(cx2, cy2, refX, refY, 0.5, 0.5);
    scale(cx3, cy3, refX, refY, 0.5, 0.5);

    float angle = -60.0; // 60 degrees
    rotate(cx1, cy1, refX, refY, angle);
    rotate(cx2, cy2, refX, refY, angle);
    rotate(cx3, cy3, refX, refY, angle);

    setcolor(BLUE);
    outtextxy(10, 50, (char*)"Scaling Sx=1.5, Sy=1.5 (BLUE)");
    drawTriangle(cx1, cy1, cx2, cy2, cx3, cy3, BLUE);




    scale(cx1, cy1, refX, refY, 0.5, 0.5);
    scale(cx2, cy2, refX, refY, 0.5, 0.5);
    scale(cx3, cy3, refX, refY, 0.5, 0.5);

    angle = -60.0; // 60 degrees
    rotate(cx1, cy1, refX, refY, angle);
    rotate(cx2, cy2, refX, refY, angle);
    rotate(cx3, cy3, refX, refY, angle);

    translate(cx1, cy1, 150, 50);
    translate(cx2, cy2, 150, 50);
    translate(cx3, cy3, 150, 50);
    setcolor(CYAN);
    outtextxy(10, 50, (char*)"Scaling Sx=1.5, Sy=1.5 (CYAN)");
    drawTriangle(cx1, cy1, cx2, cy2, cx3, cy3, CYAN);

    // TRANSLATION
    int tx1 = x1, ty1 = y1, tx2 = x2, ty2 = y2, tx3 = x3, ty3 = y3;
    translate(tx1, ty1, 300, 0);
    translate(tx2, ty2, 300, 0);
    translate(tx3, ty3, 300, 0);
    
    setcolor(YELLOW);
    outtextxy(10, 30, (char*)"Translation Tx=300, Ty=0 (YELLOW)");
    drawTriangle(tx1, ty1, tx2, ty2, tx3, ty3, YELLOW);
    
    // SCALING
    int sx1 = x1, sy1 = y1, sx2 = x2, sy2 = y2, sx3 = x3, sy3 = y3;
     refX = 180, refY = 250; // Reference point for scaling
    scale(sx1, sy1, refX, refY, 1.5, 1.5);
    scale(sx2, sy2, refX, refY, 1.5, 1.5);
    scale(sx3, sy3, refX, refY, 1.5, 1.5);
    
    setcolor(GREEN);
    outtextxy(10, 50, (char*)"Scaling Sx=1.5, Sy=1.5 (GREEN)");
    drawTriangle(sx1, sy1, sx2, sy2, sx3, sy3, GREEN);
    
    // ROTATION
    int rx1 = x1, ry1 = y1, rx2 = x2, ry2 = y2, rx3 = x3, ry3 = y3;
    angle = 60.0; // 60 degrees
    rotate(rx1, ry1, refX, refY, angle);
    rotate(rx2, ry2, refX, refY, angle);
    rotate(rx3, ry3, refX, refY, angle);
    
    setcolor(RED);
    outtextxy(10, 70, (char*)"Rotation 60 degrees (RED)");
    drawTriangle(rx1, ry1, rx2, ry2, rx3, ry3, RED);

    getch();
    closegraph();
    return 0;
}