#ifndef _VIEW_H
#define _VIEW_H

#include "GameObject.h"
#include "GameCommand.h"
#include "Model.h"
#include "Point2D.h"
#include <iostream>

const int view_maxsize = 20;

class View {

private:
	int size;
	double scale;
	Point2D origin;
	char grid[view_maxsize][view_maxsize][2];
	bool GetSubscripts(int &out_x, int &out_y, Point2D location);
public:
	View();
	void Clear();
	void Plot(GameObject* ptr);
	void Draw();
};

#endif