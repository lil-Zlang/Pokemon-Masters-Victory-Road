#include "Model.h"
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "View.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Model::Model() {
	time = 0; 
	num_objects = 6;
	num_trainers = 2;
	num_centers = 2;
	num_gyms = 2;

	center_ptrs[0] = new PokemonCenter(1, 1, 100, Point2D(1, 20));
	center_ptrs[1] = new PokemonCenter(2, 2, 200, Point2D(10, 20));

	trainer_ptrs[0] = new Trainer("Ash", 1, 'T' , 2, Point2D(5,1));
	trainer_ptrs[1] = new Trainer("Misty", 2, 'T' ,1, Point2D(10, 1));

	gym_ptrs[0] = new PokemonGym(10, 1, 2, 3, 1, Point2D());
	gym_ptrs[1] = new PokemonGym(20, 5, 7.5, 4, 2, Point2D(5, 5));

	object_ptrs[0] = trainer_ptrs[0];
	object_ptrs[1] = trainer_ptrs[1];
	object_ptrs[2] = center_ptrs[0];
	object_ptrs[3] = center_ptrs[1];
	object_ptrs[4] = gym_ptrs[0];
	object_ptrs[5] = gym_ptrs[1];

	cout << "Model default constructed." << endl;
}

Model::~Model() {
	for(int i = 0; i < num_objects; i++) {
		delete object_ptrs[i];
	}
	cout << "Model destructed." << endl;
}

Trainer* Model::GetTrainerPtr(int id) {
	for (int i = 0; i < num_trainers; i++) {
		if (trainer_ptrs[i]->GetId() == id)
			return trainer_ptrs[i];
	}
	return NULL;
}

PokemonCenter* Model::GetPokemonCenterPtr(int id) {
	for (int i = 0; i < num_centers; i++) {
		if (center_ptrs[i]->GetId() == id)
			return center_ptrs[i];
	}
	return NULL;
}

PokemonGym* Model::GetPokemonGymPtr(int id) {
	for (int i = 0; i < num_gyms; i++) {
		if (gym_ptrs[i]->GetId() == id)
			return gym_ptrs[i];
	}
	return NULL;
}

bool Model::Update() {
	time++;
	bool result = false, success = true, fail = true;
	int count = 0;

	for (int i = 0; i < num_gyms; i++) {
		if (!(gym_ptrs[i]->passed())) {
			success = false;
		}
	}

	if (success) {
		cout << "GAME OVER: You win! All battles done!" << endl;
		exit(0);
	}

	for(int i = 0; i < num_trainers; i++) {
		if (!(trainer_ptrs[i]->HasFainted())) {
			fail = false;
		}
	}

	if (fail) {
		cout << "GAME OVER: You lose! All of your Trainers' pokemon have fainted!" << endl;
		exit(0);
	}

	for (int i = 0; i < num_objects; i++){
        if (object_ptrs[i]->Update()) {
            result = true;
        }
    }
    return result;
}


void Model::Display(View& view) {
	view.Clear();
	for(int i = 0; i < num_objects; i++) {
		view.Plot(object_ptrs[i]);
	}
	view.Draw();
}

void Model::ShowStatus() {
	cout << "Time: " << time << endl;
	for(int i = 0; i < num_centers; i++) {
		center_ptrs[i]->ShowStatus();
	}

	for(int i = 0; i < num_trainers; i++) {
		trainer_ptrs[i]->ShowStatus();
	}
	
	
	for(int i = 0; i < num_gyms; i++) {
		gym_ptrs[i]->ShowStatus();
	}
}
