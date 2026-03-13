#include <stdio.h>
#include <graphics.h>
#include <conio.h>

// 1. Define region codes (TBRL)
const int INSIDE = 0; // 0000
const int LEFT   = 1; // 0001
const int RIGHT  = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP    = 8; // 1000

// Define rectangular area of interest (Clipping Window)
const int x_min = 150;
const int x_max = 450;
const int y_min = 150;
const int y_max = 350;

// Function to compute the region code for a point (x, y)
int computeCode(double x, double y) {
    int code = INSIDE;

    if (x < x_min)       
        code |= LEFT;
    else if (x > x_max)  
        code |= RIGHT;

    if (y < y_min)       
        code |= TOP;
    else if (y > y_max)  
        code |= BOTTOM;

    return code;
}

// Function to implement Cohen-Sutherland and print to graphics screen
void cohenSutherlandClip(double orig_x1, double orig_y1, double orig_x2, double orig_y2, int lineID, int text_y) {
    double x1 = orig_x1, y1 = orig_y1;
    double x2 = orig_x2, y2 = orig_y2;
    
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    int accept = 0;

    while (1) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = 1;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int code_out;
            double x, y;

            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            if (code_out & TOP) { 
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (code_out & BOTTOM) { 
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (code_out & RIGHT) { 
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (code_out & LEFT) { 
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    // --- NEW: Format string and print to Graphics Window ---
    char buffer[100]; // Temporary storage for our formatted text

    if (accept) {
        // Draw the accepted clipped line
        setcolor(LIGHTGREEN);
        line(x1, y1, x2, y2);
        
        // Combine text and coordinates into the buffer (using %.0f for clean integers)
        sprintf(buffer, "Line %d Accepted: (%.0f, %.0f) to (%.0f, %.0f)", lineID, x1, y1, x2, y2);
        
        // Print the buffer to the graphics screen
        outtextxy(50, text_y, (char*)buffer);
    } else {
        // Format rejection text
        sprintf(buffer, "Line %d Rejected: Completely Outside", lineID);
        setcolor(LIGHTRED);
        
        // Print the buffer to the graphics screen
        outtextxy(50, text_y, (char*)buffer);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)""); 

    setcolor(WHITE);
    rectangle(x_min, y_min, x_max, y_max);
    outtextxy(x_min, y_min - 15, (char*)"Clipping Window");

    double lines[3][4] = {
        {100, 200, 300, 100},  // Partially Inside
        {200, 200, 400, 300},  // Completely Inside
        {50,  300, 100, 400}   // Completely Outside
    };

    setcolor(RED);
    for(int i = 0; i < 3; i++) {
        line(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
    }
    
    setcolor(WHITE);
    outtextxy(50, 450, (char*)"Before Clipping. Press any key to clip...");
    
    getch(); 

    // --- SECOND SCREEN: CLIPPED RESULTS ---
    cleardevice();
    
    setcolor(WHITE);
    rectangle(x_min, y_min, x_max, y_max);
    outtextxy(x_min, y_min - 15, (char*)"Clipping Window");
    
    // Set a starting Y coordinate for our text output (below the window)
    int text_y_position = 380; 

    for(int i = 0; i < 3; i++) {
        // Pass the lineID and the current Y position for the text
        cohenSutherlandClip(lines[i][0], lines[i][1], lines[i][2], lines[i][3], i + 1, text_y_position);
        
        // Move the text cursor down by 20 pixels for the next line
        text_y_position += 20; 
    }

    setcolor(WHITE);
    outtextxy(50, 450, (char*)"Press any key to exit...");

    getch();
    closegraph();
    return 0;
}