#include "Building.h"
#include <iostream>

using namespace std;

Building::Building() : GameObject('B')
{
	display_code = 'B';
	trainer_count = 0;
	cout << "Building default constructed" << endl;
}

Building::Building(char in_code, int in_id, Point2D in_loc) : GameObject('B') {
	id_num = in_id;
	location = in_loc;
	display_code = in_code;
	state = 0;
    trainer_count = 0;          // must declare trainer count start at 0, otherwise if add/sub trainer get bad int value
	cout << "Building constructed" << endl;
}

Building::~Building() {
	cout << "Building destructed." << endl;
}

void Building::AddOneTrainer() {
	trainer_count += 1;
}

void Building::RemoveOneTrainer() {
	trainer_count -= 1;
}

void Building::ShowStatus() {
	GameObject::ShowStatus();
	if (trainer_count == 0 || trainer_count > 1) {
		cout << trainer_count << " trainers are in this building" << endl;
	} else if(trainer_count == 1) {
		cout << trainer_count << " trainers is in this building" << endl;
	}
}
	
bool Building::ShouldBeVisible() {
	return true;
}



