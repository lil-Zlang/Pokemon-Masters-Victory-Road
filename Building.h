#ifndef _BUILDING_H
#define _BUILDING_H

#include "GameObject.h"
#include "Point2D.h"
#include <iostream>

class Point2D;
class GameObject;

class Building : public GameObject {
private:
	unsigned int trainer_count = 0;  // change

public:
	Building();
	Building(char in_code, int in_id, Point2D in_loc);
	~Building();

	void AddOneTrainer();
	void RemoveOneTrainer();
	void ShowStatus();
	bool ShouldBeVisible();
};

#endif
