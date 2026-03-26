#include <stdio.h>
#include <graphics.h>
#include <conio.h>

// Clipping window limits
const double x_min = 150;
const double y_min = 150;
const double x_max = 450;
const double y_max = 350;

int clipTest(double p, double q, double *tE, double *tL) {
    if (p == 0) {
        if (q < 0) {
            return 0;
        }
        return 1;
    }

    double t = q / p;

    if (p < 0) {
        if (t > *tL) {
            return 0;
        }
        if (t > *tE) {
            *tE = t;
        }
    } else {
        if (t < *tE) {
            return 0;
        }
        if (t < *tL) {
            *tL = t;
        }
    }

    return 1;
}

int liangBarskyClip(
    double x1,
    double y1,
    double x2,
    double y2,
    double *cx1,
    double *cy1,
    double *cx2,
    double *cy2
) {
    double dx = x2 - x1;
    double dy = y2 - y1;

    double tE = 0.0;
    double tL = 1.0;

    if (clipTest(-dx, x1 - x_min, &tE, &tL) &&
        clipTest(dx, x_max - x1, &tE, &tL) &&
        clipTest(-dy, y1 - y_min, &tE, &tL) &&
        clipTest(dy, y_max - y1, &tE, &tL)) {

        *cx1 = x1 + tE * dx;
        *cy1 = y1 + tE * dy;
        *cx2 = x1 + tL * dx;
        *cy2 = y1 + tL * dy;
        return 1;
    }

    return 0;
}

void drawResult(
    double x1,
    double y1,
    double x2,
    double y2,
    int lineID,
    int textY
) {
    double cx1, cy1, cx2, cy2;
    char message[120];

    if (liangBarskyClip(x1, y1, x2, y2, &cx1, &cy1, &cx2, &cy2)) {
        setcolor(LIGHTGREEN);
        line((int)cx1, (int)cy1, (int)cx2, (int)cy2);

        sprintf(
            message,
            "Line %d Accepted: (%.0f, %.0f) to (%.0f, %.0f)",
            lineID,
            cx1,
            cy1,
            cx2,
            cy2
        );
        setcolor(WHITE);
        outtextxy(50, textY, (char *)message);
    } else {
        sprintf(message, "Line %d Rejected: Completely Outside", lineID);
        setcolor(LIGHTRED);
        outtextxy(50, textY, (char *)message);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    double lines[4][4] = {
        {100, 200, 320, 120},
        {200, 200, 420, 300},
        {70, 370, 120, 430},
        {80, 320, 520, 240}
    };

    setcolor(WHITE);
    rectangle((int)x_min, (int)y_min, (int)x_max, (int)y_max);
    outtextxy((int)x_min, (int)y_min - 15, (char *)"Clipping Window");

    setcolor(RED);
    for (int i = 0; i < 4; i++) {
        line((int)lines[i][0], (int)lines[i][1], (int)lines[i][2], (int)lines[i][3]);
    }

    setcolor(WHITE);
    outtextxy(50, 450, (char *)"Before clipping (Liang-Barsky). Press any key...");
    getch();

    cleardevice();

    setcolor(WHITE);
    rectangle((int)x_min, (int)y_min, (int)x_max, (int)y_max);
    outtextxy((int)x_min, (int)y_min - 15, (char *)"Clipping Window");

    int textY = 380;
    for (int i = 0; i < 4; i++) {
        drawResult(lines[i][0], lines[i][1], lines[i][2], lines[i][3], i + 1, textY);
        textY += 20;
    }

    setcolor(WHITE);
    outtextxy(50, 450, (char *)"After clipping. Press any key to exit...");

    getch();
    closegraph();
    return 0;
}
