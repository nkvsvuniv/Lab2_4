#pragma once
#include <GL\glut.h>
#include <vector>
#include <string>

// drawing defines
#define  DRAW_POINT   0
#define  DRAW_LINE    1
#define  DRAW_CIRCLE  2
#define  DRAW_RECT    3

using namespace std;

class Primitive
{
public:
	vector<int> parameters;
	int paramQ;
	string type;

	Primitive();
	virtual ~Primitive();
	virtual void Draw() = 0;
	virtual string ToString() = 0;
};

class Point : public Primitive
{
public:
	Point() : Primitive() { paramQ = 2; type = "point"; }
	~Point() {}
	void Draw();
	string ToString();
};

class Line : public Primitive
{
public:
	Line() : Primitive() { paramQ = 4; type = "line"; }
	~Line() {}
	void Draw();
	string ToString();
};

class Circle : public Primitive
{
public:
	Circle() : Primitive() { paramQ = 3; type = "circle"; }
	~Circle() {}
	void Draw();
	string ToString();
};

class Rect : public Primitive
{
public:
	Rect() : Primitive() { paramQ = 4; type = "rectangle"; }
	~Rect() {}
	void Draw();
	string ToString();
};

class glutMFC
{
public:
	std::vector<Primitive*> primitives;
	bool drawing = false;
	int currDrawing = 0;
	
	glutMFC();
	~glutMFC();

	// CALLBACKS

	void display();
	void resize(int width, int height);
	void render();
	
};