#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <iostream>
#include "Point2D.h"

class GameObject {
protected:
	Point2D location; 
	int id_num;
	char display_code;
	char state;

public:
	GameObject(char in_code);
	GameObject(Point2D &in_loc, int in_id, char in_code);
	virtual ~GameObject();
	Point2D GetLocation();
	int GetId();
	char GetState();
	void DrawSelf(char* ptr);
	virtual bool Update() = 0;
	virtual bool ShouldBeVisible() = 0;
	virtual void ShowStatus();
};

#endif