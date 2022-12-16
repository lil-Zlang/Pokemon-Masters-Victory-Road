#include "Vector2D.h"
#include "Point2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "Model.h"
#include "View.h"
#include "GameCommand.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
	
	View v;

	Model m;
	m.ShowStatus();
	m.Display(v);

	char command;
	int x, y, trainer_id, gym_id, center_id, potions_needed, battles;

	while(true) {

		cout << "Enter Command: ";
		cin >> command;

		switch(command) {
			case 'm':
				cin >> trainer_id;
				cin >> x;
				cin >> y;
				DoMoveCommand(m, trainer_id, Point2D(x, y));
				m.Update();
				m.Display(v);
				break;
			
			case 'c':
				cin >> trainer_id >> center_id;
				DoMoveToCenterCommand(m, trainer_id, center_id);
				break;

			case 'g':
				cin >> trainer_id >> gym_id;
				DoMoveToGymCommand(m, trainer_id, gym_id);
				break;

			case 's':
				cin >> trainer_id;
				DoStopCommand(m, trainer_id);
				m.Display(v);
				break;

			case 'p':
				cin >> trainer_id >> potions_needed;
				DoRecoverInCenterCommand(m, trainer_id, potions_needed);
				m.Display(v);
				break;

			case 'b':
				cin >> trainer_id  >> battles;
				DoTrainInGymCommand(m, trainer_id, battles);
				m.Display(v);
				break;

			case 'a': 
				DoGoCommand(m, v);
				m.Display(v);
				break;

			case 'r':
				DoRunCommand(m, v);
				m.Display(v);
				break;

			case 'q':
				m.~Model();
				exit(0);

			default: 
				cout << "ERROR: Please enter a valid command!" << endl;
		}

	}
	return 0;
}
