#include "stdafx.h"
#include "glutMFC.h"
#include <afxdb.h>

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

// mouse callback
void glutMFC::mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		int glX = x - 300;
		int glY = -y + 300;

		if (currDrawing == DRAW_LINE)
		{
			Primitive* line = new Line();
			line->parameters.push_back(glX);
			line->parameters.push_back(glY);
			line->parameters.push_back(glX);
			line->parameters.push_back(glY);
			primitives.push_back(line);
		}
		if (currDrawing == DRAW_CIRCLE)
		{
			Primitive* circle = new Circle();
			circle->parameters.push_back(glX);
			circle->parameters.push_back(glY);
			circle->parameters.push_back(0);
			primitives.push_back(circle);
		}
		if (currDrawing == DRAW_RECT)
		{
			Primitive* rect = new Rect();
			rect->parameters.push_back(glX);
			rect->parameters.push_back(glY);
			rect->parameters.push_back(glX);
			rect->parameters.push_back(glY);
			primitives.push_back(rect);
		}
		drawing = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		drawing = false;
		if (sck)
			sck->Send(primitives[primitives.size() - 1]->ToString().c_str(), primitives[primitives.size() - 1]->ToString().size() + 1);
		if (sck2)
			sck2->Send(primitives[primitives.size() - 1]->ToString().c_str(), primitives[primitives.size() - 1]->ToString().size() + 1);
		CDatabase db;
		db.Open(L"Lab2src");
		wstring begin = L"INSERT INTO primitives VALUES (";
		wstring typeval;
		if (currDrawing == DRAW_LINE)
			typeval = L"\'L\', ";
		else if (currDrawing == DRAW_CIRCLE)
			typeval = L"\'C\', ";
		else if (currDrawing == DRAW_RECT)
			typeval = L"\'R\', ";
		wstring pval[4];
		for (int i = 0; i < primitives[primitives.size() - 1]->parameters.size(); i++)
		{
			pval[i] = to_wstring((int)primitives[primitives.size() - 1]->parameters[i]);
			if (i != 3)
				pval[i] += L", ";
		}
		for (int i = primitives[primitives.size() - 1]->parameters.size(); i < 4; i++)
		{
			pval[i] = L"0";
			if (i != 3)
				pval[i] += L", ";
		}
		wstring end = L")";
		wstring res = begin + typeval + pval[0] + pval[1] + pval[2] + pval[3] + end;
		const wchar_t* request = res.c_str();
		db.ExecuteSQL(request);
		db.Close();
	}
}

// mouse motion callback
void glutMFC::mouseMove(int x, int y)
{
	if (drawing)
	{
		if (currDrawing == DRAW_LINE)
		{
			primitives[primitives.size() - 1]->parameters[2] = x - 300;
			primitives[primitives.size() - 1]->parameters[3] = -y + 300;
		}
		if (currDrawing == DRAW_CIRCLE)
		{
			int glX0 = primitives[primitives.size() - 1]->parameters[0];
			int glY0 = primitives[primitives.size() - 1]->parameters[1];
			int glX = x - 300;
			int glY = -y + 300;
			if (abs(glX - glX0) > abs(glY - glY0))
				primitives[primitives.size() - 1]->parameters[2] = abs(glX - glX0);
			else
				primitives[primitives.size() - 1]->parameters[2] = abs(glY - glY0);
		}
		if (currDrawing == DRAW_RECT)
		{
			primitives[primitives.size() - 1]->parameters[2] = x - 300;
			primitives[primitives.size() - 1]->parameters[3] = -y + 300;
		}
	}
}

Primitive::Primitive()
{
}


Primitive::~Primitive()
{
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

string Line::ToString()
{
	// "L:x1.y1.x2.y2"
	string x1 = to_string(this->parameters[0]);
	string y1 = to_string(this->parameters[1]);
	string x2 = to_string(this->parameters[2]);
	string y2 = to_string(this->parameters[3]);
	string res = "L " + x1 + "~" + y1 + "~" + x2 + "~" + y2;
	return res;
}

string Circle::ToString()
{
	// "C:x.y.r"
	string x = to_string(this->parameters[0]);
	string y = to_string(this->parameters[1]);
	string r = to_string(this->parameters[2]);
	string res = "C " + x + "~" + y + "~" + r;
	return res;
}

string Rect::ToString()
{
	// "R:x1.y1.x2.y2"
	string x1 = to_string(this->parameters[0]);
	string y1 = to_string(this->parameters[1]);
	string x2 = to_string(this->parameters[2]);
	string y2 = to_string(this->parameters[3]);
	string res = "R " + x1 + "~" + y1 + "~" + x2 + "~" + y2;
	return res;
}

void glutMFC::Sync(int ind)
{
	for (int i = 0; i < primitives.size(); i++)
	{
		if (!ind)
			sck->Send(primitives[i]->ToString().c_str(), primitives[i]->ToString().size() + 1);
		else
			sck2->Send(primitives[i]->ToString().c_str(), primitives[i]->ToString().size() + 1);
		Sleep(10);
	}
}