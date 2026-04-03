#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <vector>

using namespace std;

struct Point {
	double x;
	double y;
};

enum ClipEdge {
	EDGE_LEFT,
	EDGE_RIGHT,
	EDGE_TOP,
	EDGE_BOTTOM
};

const int X_MIN = 150;
const int Y_MIN = 120;
const int X_MAX = 500;
const int Y_MAX = 360;
const double PI_VAL = 3.14159265358979323846;

void drawPolygon(const vector<Point> &poly, int color, bool closeShape) {
	if (poly.size() < 2) {
		return;
	}

	setcolor(color);
	for (size_t i = 0; i < poly.size() - 1; ++i) {
		line((int)poly[i].x, (int)poly[i].y, (int)poly[i + 1].x, (int)poly[i + 1].y);
	}

	if (closeShape) {
		line((int)poly.back().x, (int)poly.back().y, (int)poly.front().x, (int)poly.front().y);
	}
}

bool isInside(const Point &p, ClipEdge edge) {
	if (edge == EDGE_LEFT) {
		return p.x >= X_MIN;
	}
	if (edge == EDGE_RIGHT) {
		return p.x <= X_MAX;
	}
	if (edge == EDGE_TOP) {
		return p.y >= Y_MIN;
	}
	return p.y <= Y_MAX;
}

Point getIntersection(const Point &s, const Point &e, ClipEdge edge) {
	Point iPoint;
	double x1 = s.x;
	double y1 = s.y;
	double x2 = e.x;
	double y2 = e.y;

	if (edge == EDGE_LEFT || edge == EDGE_RIGHT) {
		double xEdge = (edge == EDGE_LEFT) ? X_MIN : X_MAX;
		double dx = x2 - x1;
		double t = 0.0;
		if (dx != 0.0) {
			t = (xEdge - x1) / dx;
		}
		iPoint.x = xEdge;
		iPoint.y = y1 + t * (y2 - y1);
	} else {
		double yEdge = (edge == EDGE_TOP) ? Y_MIN : Y_MAX;
		double dy = y2 - y1;
		double t = 0.0;
		if (dy != 0.0) {
			t = (yEdge - y1) / dy;
		}
		iPoint.y = yEdge;
		iPoint.x = x1 + t * (x2 - x1);
	}

	return iPoint;
}

vector<Point> clipAgainstEdge(const vector<Point> &inputPoly, ClipEdge edge) {
	vector<Point> output;

	if (inputPoly.empty()) {
		return output;
	}

	Point s = inputPoly.back();
	for (size_t i = 0; i < inputPoly.size(); ++i) {
		Point e = inputPoly[i];
		bool eInside = isInside(e, edge);
		bool sInside = isInside(s, edge);

		if (eInside) {
			if (!sInside) {
				output.push_back(getIntersection(s, e, edge));
			}
			output.push_back(e);
		} else if (sInside) {
			output.push_back(getIntersection(s, e, edge));
		}

		s = e;
	}

	return output;
}

vector<Point> sutherlandHodgmanClip(const vector<Point> &subject) {
	vector<Point> result = subject;
	result = clipAgainstEdge(result, EDGE_LEFT);
	result = clipAgainstEdge(result, EDGE_RIGHT);
	result = clipAgainstEdge(result, EDGE_TOP);
	result = clipAgainstEdge(result, EDGE_BOTTOM);
	return result;
}

Point rotateBy60(const Point &origin, const Point &p) {
	double angle = PI_VAL / 3.0;
	double px = p.x - origin.x;
	double py = p.y - origin.y;

	Point r;
	r.x = origin.x + px * cos(angle) - py * sin(angle);
	r.y = origin.y + px * sin(angle) + py * cos(angle);
	return r;
}

void drawKochSegment(const Point &a, const Point &b, int depth) {
	if (depth == 0) {
		line((int)a.x, (int)a.y, (int)b.x, (int)b.y);
		return;
	}

	Point p1, p2, peak;
	p1.x = a.x + (b.x - a.x) / 3.0;
	p1.y = a.y + (b.y - a.y) / 3.0;

	p2.x = a.x + 2.0 * (b.x - a.x) / 3.0;
	p2.y = a.y + 2.0 * (b.y - a.y) / 3.0;

	peak = rotateBy60(p1, p2);

	drawKochSegment(a, p1, depth - 1);
	drawKochSegment(p1, peak, depth - 1);
	drawKochSegment(peak, p2, depth - 1);
	drawKochSegment(p2, b, depth - 1);
}

void drawKochSnowflake(int depth, int w, int h) {
	double side = (w < h ? w : h) * 0.50;
	double triHeight = side * sqrt(3.0) / 2.0;

	Point a, b, c;
	a.x = w / 2.0;
	a.y = h / 2.0 - triHeight / 2.0;

	b.x = w / 2.0 - side / 2.0;
	b.y = h / 2.0 + triHeight / 2.0;

	c.x = w / 2.0 + side / 2.0;
	c.y = h / 2.0 + triHeight / 2.0;

	setcolor(LIGHTCYAN);
	drawKochSegment(a, b, depth);
	drawKochSegment(b, c, depth);
	drawKochSegment(c, a, depth);
}

int main() {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, (char *)"");

	int w = getmaxx();
	int h = getmaxy();

	vector<Point> subject;
	subject.push_back({90, 180});
	subject.push_back({230, 70});
	subject.push_back({390, 90});
	subject.push_back({560, 180});
	subject.push_back({520, 320});
	subject.push_back({350, 430});
	subject.push_back({170, 390});

	vector<Point> clipped = sutherlandHodgmanClip(subject);

	setbkcolor(BLACK);
	cleardevice();

	setcolor(WHITE);
	outtextxy(10, 10, (char *)"Polygon Clipping (Sutherland-Hodgman)");
	rectangle(X_MIN, Y_MIN, X_MAX, Y_MAX);
	outtextxy(X_MIN, Y_MIN - 18, (char *)"Clipping Window");

	setcolor(RED);
	drawPolygon(subject, RED, true);
	outtextxy(10, h - 40, (char *)"Original polygon shown in RED.");
	outtextxy(10, h - 20, (char *)"Press any key to see clipped polygon...");
	getch();

	cleardevice();
	setcolor(WHITE);
	outtextxy(10, 10, (char *)"Polygon Clipping (Result)");
	rectangle(X_MIN, Y_MIN, X_MAX, Y_MAX);

	setcolor(DARKGRAY);
	drawPolygon(subject, DARKGRAY, true);
	outtextxy(10, 35, (char *)"Original in DARKGRAY");

	if (clipped.size() >= 3) {
		drawPolygon(clipped, LIGHTGREEN, true);
		outtextxy(10, 55, (char *)"Clipped polygon in LIGHTGREEN");
	} else {
		setcolor(LIGHTRED);
		outtextxy(10, 55, (char *)"Polygon rejected after clipping.");
	}

	outtextxy(10, h - 20, (char *)"Press any key for fractal generation...");
	getch();

	cleardevice();
	setcolor(WHITE);
	outtextxy(10, 10, (char *)"Fractal Generation: Koch Snowflake (depth = 4)");
	outtextxy(10, 30, (char *)"Recursive subdivision on each triangle side.");

	drawKochSnowflake(4, w, h);

	setcolor(WHITE);
	outtextxy(10, h - 20, (char *)"Press any key to exit...");
	getch();

	closegraph();
	return 0;
}
