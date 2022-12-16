#ifndef _MODEL_H
#define _MODEL_H

#include "GameObject.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include <iostream>

class View;

class Model{

private:
	int time;

	GameObject* object_ptrs[10];
	int num_objects;

	Trainer* trainer_ptrs[10];
	int num_trainers;

	PokemonCenter* center_ptrs[10];
	int num_centers;

	PokemonGym* gym_ptrs[10];
	int num_gyms;

	Model(Model &);

public:
	Model();
	~Model();

	Trainer* GetTrainerPtr(int id);
	PokemonCenter* GetPokemonCenterPtr(int id);
	PokemonGym* GetPokemonGymPtr(int id);
	bool Update();
	void Display(View& view);
	void ShowStatus();
};

#endif