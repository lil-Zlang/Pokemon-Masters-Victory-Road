#include "View.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include <iostream>


using namespace std;

View::View() {
	size = 11;
	scale = 2;
	origin = Point2D();
}

bool View::GetSubscripts(int &out_x, int &out_y, Point2D location) {
	Vector2D sub = (location - origin) / scale;
	out_x = sub.x;
	out_y = sub.y;
	if(out_x >= 0 && out_x < size && out_y >= 0 && out_y <= size) {
		return true;
	} else {
		cout << "An object is outside the display" << endl;
		return false;
	}
}

void View::Plot(GameObject* ptr) {
	int out_x, out_y;
	if(GetSubscripts(out_x, out_y, ptr->GetLocation())) {
		if(grid[out_x][out_y][0] == '.') {
			ptr->DrawSelf(grid[out_x][out_y]);
		} else {
			grid[out_x][out_y][0] = '*';
			grid[out_x][out_y][1] = ' ';
		}
	}
} 

void View::Draw()
{
    for (int i = size-1; i > -1; i--)
    {
        for (int j = 0; j <= size-1; j++)
        {
            //draw objects
            if (i >= 0 && j >=0)
            {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }
}

void View::Clear() {
	for (int i = 0; i < view_maxsize; i++) {
		for (int j = 0; j < view_maxsize; j++){
			grid[i][j][0] = '.';
			grid[i][j][1] = ' ';
		}
	}
}
