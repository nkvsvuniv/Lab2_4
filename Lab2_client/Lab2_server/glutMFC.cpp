#include "stdafx.h"
#include "glutMFC.h"


glutMFC::glutMFC()
{
}


glutMFC::~glutMFC()
{
}


// display callback
void glutMFC::display()
{
	glClearColor(0, 0, 0, 0);//set the background color to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glColor3f(1.0f, 1.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(-300.0f, -300.0f, 0.0f);
	glVertex3f(-300.0f, 300.0f, 0.0f);
	glVertex3f(300.0f, 300.0f, 0.0f);
	glVertex3f(300.0f, -300.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f); //set cube color
	for (int i = 0; i < primitives.size(); i++)
		primitives[i]->Draw();
	glutSwapBuffers();
}


// resize callback
void glutMFC::resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)width / (float)height, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set the viewing position and orientation
	gluLookAt(
		0.0, 0.0, 725.0, // eye location
		0.0, 0.0, 0.0, // center location
		0.0, 1.0, 0.0); // up vector
}


// idle callback
void glutMFC::render()
{
	glClearColor(0, 0, 0, 0);//set the background color to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glColor3f(1.0f, 1.0f, 1.0f); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(-300.0f, -300.0f, 0.0f);
	glVertex3f(-300.0f, 300.0f, 0.0f);
	glVertex3f(300.0f, 300.0f, 0.0f);
	glVertex3f(300.0f, -300.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	for (int i = 0; i < primitives.size(); i++)
		primitives[i]->Draw();
	glutSwapBuffers();
}


Primitive::Primitive()
{
}


Primitive::~Primitive()
{
}

void Point::Draw()
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POINTS);
		glVertex3f(this->parameters[0], this->parameters[1], 0);
	glEnd();
}

void Line::Draw()
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(this->parameters[0], this->parameters[1], 0);
		glVertex3f(this->parameters[2], this->parameters[3], 0);
	glEnd();
}

void Circle::Draw()
{
	int x0 = this->parameters[0];
	int y0 = this->parameters[1];
	int r = this->parameters[2];
	float t = 0.0f;
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	while (t <= 8 * atan(1))
	{
		glVertex3f(x0 + r*cos(t), y0 + r*sin(t), 0);
		t += 0.01;
	}
	glEnd();
}

void Rect::Draw()
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex3f(this->parameters[0], this->parameters[1], 0);
		glVertex3f(this->parameters[0], this->parameters[3], 0);
		glVertex3f(this->parameters[2], this->parameters[3], 0);
		glVertex3f(this->parameters[2], this->parameters[1], 0);
	glEnd();
}

string Point::ToString()
{
	// "P:x.y"
	string x = to_string(this->parameters[0]);
	string y = to_string(this->parameters[1]);
	string res = "P:" + x + "." + y;
	return res;
}

string Line::ToString()
{
	// "L:x1.y1.x2.y2"
	string x1 = to_string(this->parameters[0]);
	string y1 = to_string(this->parameters[1]);
	string x2 = to_string(this->parameters[2]);
	string y2 = to_string(this->parameters[3]);
	string res = "L:" + x1 + "." + y1 + "." + x2 + "." + y2;
	return res;
}

string Circle::ToString()
{
	// "C:x.y.r"
	string x = to_string(this->parameters[0]);
	string y = to_string(this->parameters[1]);
	string r = to_string(this->parameters[2]);
	string res = "C:" + x + "." + y + "." + r;
	return res;
}

string Rect::ToString()
{
	// "R:x1.y1.x2.y2"
	string x1 = to_string(this->parameters[0]);
	string y1 = to_string(this->parameters[1]);
	string x2 = to_string(this->parameters[2]);
	string y2 = to_string(this->parameters[3]);
	string res = "R:" + x1 + "." + y1 + "." + x2 + "." + y2;
	return res;
}
