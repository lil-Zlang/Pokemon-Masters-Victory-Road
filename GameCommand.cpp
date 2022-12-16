#include "GameCommand.h"
#include "Model.h"
#include "View.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "Trainer.h"
#include "GameObject.h"
#include <iostream>


using namespace std;

void DoMoveCommand(Model& model, int trainer_id, Point2D p1) {
	Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);
	if (trainer_ptr) {
		trainer_ptr->StartMoving(p1);
		cout << "Moving " << trainer_ptr->GetName() << " to " << p1 << endl; 
	} else {
		cout << "Error: Please enter a valid command!" << endl;
	}
}

void DoMoveToCenterCommand(Model & model, int trainer_id, int center_id) {
	Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);
	PokemonCenter* center_ptr = model.GetPokemonCenterPtr(center_id);
	if (trainer_ptr && center_ptr) {
		trainer_ptr->StartMovingToCenter(center_ptr);
		cout << "Moving " << trainer_ptr->GetName() << " to " << "pokemon center " << center_ptr->GetId() << endl;
	} else {
		cout << "Error: Please enter a valid command!" << endl;
	}
}

void DoMoveToGymCommand(Model & model, int trainer_id, int gym_id) {
	Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);
	PokemonGym* gym_ptr = model.GetPokemonGymPtr(gym_id);
	if (trainer_ptr && gym_ptr) {
		trainer_ptr->StartMovingToGym(gym_ptr);
		cout << "Moving " << trainer_ptr->GetName() << " to " << "gym " << gym_ptr->GetId() << endl;
	} else {
		cout << "Error: Please enter a valid command!" << endl;
	}
}

void DoStopCommand(Model & model, int trainer_id) {
	Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);
	if (trainer_ptr) {
		trainer_ptr->Stop();
	} else {
		cout << "Error: Please enter a valid command!" << endl;
	}
}

void DoTrainInGymCommand(Model & model, int trainer_id, unsigned int battles){
	Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);
	if (trainer_ptr) {
		trainer_ptr->StartBattling(battles);
	} else {
		cout << "Error: Please enter a valid command!" << endl;
	}
}

void DoRecoverInCenterCommand(Model & model, int trainer_id, unsigned int potions_needed){
	Trainer* trainer_ptr = model.GetTrainerPtr(trainer_id);
	if (trainer_ptr) {
		trainer_ptr->StartRecoveringHealth(potions_needed);
	} else {
		cout << "Error: Please enter a valid command!" << endl;
	}
}

void DoGoCommand(Model& model, View & view) {
	cout << "Advancing one tick." << endl;
	model.Update();
	model.ShowStatus();
}

void DoRunCommand(Model & model, View & view) {
	cout << "Advancing to next event." << endl;
}
