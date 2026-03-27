#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>

typedef struct {
	float x;
	float y;
} Point;

Point quadraticBezierPoint(Point p0, Point p1, Point p2, float t) {
	float u = 1.0f - t;
	Point p;

	p.x = u * u * p0.x + 2.0f * u * t * p1.x + t * t * p2.x;
	p.y = u * u * p0.y + 2.0f * u * t * p1.y + t * t * p2.y;

	return p;
}

Point cubicBezierPoint(Point p0, Point p1, Point p2, Point p3, float t) {
	float u = 1.0f - t;
	Point p;

	p.x = u * u * u * p0.x
		+ 3.0f * u * u * t * p1.x
		+ 3.0f * u * t * t * p2.x
		+ t * t * t * p3.x;

	p.y = u * u * u * p0.y
		+ 3.0f * u * u * t * p1.y
		+ 3.0f * u * t * t * p2.y
		+ t * t * t * p3.y;

	return p;
}

void drawControlPolygon(Point points[], int n) {
	int i;

	setcolor(DARKGRAY);
	for (i = 0; i < n - 1; i++) {
		line((int)points[i].x, (int)points[i].y, (int)points[i + 1].x, (int)points[i + 1].y);
	}

	for (i = 0; i < n; i++) {
		setcolor(WHITE);
		circle((int)points[i].x, (int)points[i].y, 3);
		floodfill((int)points[i].x, (int)points[i].y, WHITE);
	}
}

void drawQuadraticBezier(Point p0, Point p1, Point p2, int curveColor) {
	float t;
	Point prev = p0;
	Point curr;

	setcolor(curveColor);
	for (t = 0.01f; t <= 1.0f; t += 0.01f) {
		curr = quadraticBezierPoint(p0, p1, p2, t);
		line((int)prev.x, (int)prev.y, (int)curr.x, (int)curr.y);
		prev = curr;
	}
}

void drawCubicBezier(Point p0, Point p1, Point p2, Point p3, int curveColor) {
	float t;
	Point prev = p0;
	Point curr;

	setcolor(curveColor);
	for (t = 0.01f; t <= 1.0f; t += 0.01f) {
		curr = cubicBezierPoint(p0, p1, p2, p3, t);
		line((int)prev.x, (int)prev.y, (int)curr.x, (int)curr.y);
		prev = curr;
	}
}

void drawText(int x, int y, const char *text) {
	outtextxy(x, y, const_cast<char *>(text));
}

void drawPanelLabel(int x, int y, const char *text) {
	setcolor(LIGHTCYAN);
	drawText(x, y, text);
}

int main() {
	int gd = DETECT, gm;
	int w, h;
	int c1, c2, c3;
	int qRowY, cRowY;

	initgraph(&gd, &gm, (char *)"");

	w = getmaxx();
	h = getmaxy();

	setbkcolor(BLACK);
	cleardevice();

	drawText(10, 10, "Bezier Curves: Quadratic and Cubic Parametric Functions");

	c1 = w / 6;
	c2 = w / 2;
	c3 = (5 * w) / 6;

	qRowY = h / 4;
	cRowY = (3 * h) / 4;

	/* Quadratic 1: control point in middle */
	{
		Point q[3] = {
			{(float)(c1 - 65), (float)(qRowY + 45)},
			{(float)c1, (float)(qRowY - 65)},
			{(float)(c1 + 65), (float)(qRowY + 45)}
		};
		drawPanelLabel(c1 - 82, qRowY - 95, "Quadratic: control in middle");
		drawControlPolygon(q, 3);
		drawQuadraticBezier(q[0], q[1], q[2], YELLOW);
	}

	/* Quadratic 2: control point far on one side */
	{
		Point q[3] = {
			{(float)(c2 - 65), (float)(qRowY + 45)},
			{(float)(c2 - 130), (float)(qRowY - 85)},
			{(float)(c2 + 65), (float)(qRowY + 45)}
		};
		drawPanelLabel(c2 - 86, qRowY - 95, "Quadratic: far on one side");
		drawControlPolygon(q, 3);
		drawQuadraticBezier(q[0], q[1], q[2], LIGHTGREEN);
	}

	/* Quadratic 3: control point far on other side */
	{
		Point q[3] = {
			{(float)(c3 - 65), (float)(qRowY + 45)},
			{(float)(c3 + 130), (float)(qRowY - 85)},
			{(float)(c3 + 65), (float)(qRowY + 45)}
		};
		drawPanelLabel(c3 - 88, qRowY - 95, "Quadratic: far on other side");
		drawControlPolygon(q, 3);
		drawQuadraticBezier(q[0], q[1], q[2], LIGHTMAGENTA);
	}

	/* Cubic 1: both control points close together */
	{
		Point c[4] = {
			{(float)(c1 - 70), (float)(cRowY + 40)},
			{(float)(c1 - 20), (float)(cRowY - 85)},
			{(float)(c1 + 15), (float)(cRowY - 78)},
			{(float)(c1 + 70), (float)(cRowY + 40)}
		};
		drawPanelLabel(c1 - 92, cRowY - 120, "Cubic: control points close");
		drawControlPolygon(c, 4);
		drawCubicBezier(c[0], c[1], c[2], c[3], CYAN);
	}

	/* Cubic 2: control points far apart */
	{
		Point c[4] = {
			{(float)(c2 - 70), (float)(cRowY + 40)},
			{(float)(c2 - 145), (float)(cRowY - 95)},
			{(float)(c2 + 145), (float)(cRowY - 95)},
			{(float)(c2 + 70), (float)(cRowY + 40)}
		};
		drawPanelLabel(c2 - 86, cRowY - 120, "Cubic: control points far apart");
		drawControlPolygon(c, 4);
		drawCubicBezier(c[0], c[1], c[2], c[3], LIGHTRED);
	}

	/* Cubic 3: control points at opposite ends */
	{
		Point c[4] = {
			{(float)(c3 - 70), (float)(cRowY + 40)},
			{(float)(c3 - 145), (float)(cRowY - 95)},
			{(float)(c3 + 145), (float)(cRowY + 95)},
			{(float)(c3 + 70), (float)(cRowY + 40)}
		};
		drawPanelLabel(c3 - 92, cRowY - 120, "Cubic: opposite-end controls");
		drawControlPolygon(c, 4);
		drawCubicBezier(c[0], c[1], c[2], c[3], WHITE);
	}

	drawText(10, h - 20, "Press any key to exit...");
	getch();
	closegraph();

	return 0;
}
