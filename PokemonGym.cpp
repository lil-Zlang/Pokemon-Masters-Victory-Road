#include "PokemonGym.h"
#include <iostream>

using namespace std;

PokemonGym::PokemonGym() : Building() {
	display_code = 'G';
	state = NOT_DEFEATED;
	max_number_of_battles = 10;
	num_battle_remaining = max_number_of_battles;
	health_cost_per_battle = 1;
	PokeDollar_cost_per_battle = 1.0;
	experience_per_battle = 2;
	cout << "PokemonGym default constructed" << endl;
}

PokemonGym::PokemonGym(unsigned int max_battle, unsigned int health_loss, 
double PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc) : Building('G', in_id, in_loc) {
	max_number_of_battles = max_battle;
	health_cost_per_battle = health_loss; 
	experience_per_battle = exp_per_battle;
	PokeDollar_cost_per_battle = PokeDollar_cost;
	state = NOT_DEFEATED;
	num_battle_remaining = max_number_of_battles; 
	cout << "PokemonGym constructed" << endl;
}

PokemonGym::~PokemonGym() {
	cout << "PokemonGym destructed." << endl;
}

double PokemonGym::GetPokeDollarCost(unsigned int battle_qty) {
	double cost = PokeDollar_cost_per_battle * battle_qty;
	return cost;
}

unsigned int PokemonGym::GetHealthCost(unsigned int battle_qty) {
	return health_cost_per_battle * battle_qty;
}

unsigned int PokemonGym::GetNumBattlesRemaining() {
	return num_battle_remaining;
}

bool PokemonGym:: IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int health) {
	int health_cost = GetHealthCost(battle_qty);
	double dollar_cost = GetPokeDollarCost(battle_qty);
	if (dollar_cost <= budget && health_cost <= health) {
		return true; 
	} else {
		return false;
	}
}

unsigned int PokemonGym::TrainPokemon(unsigned int battle_units) {
	if (num_battle_remaining >= battle_units) {
		num_battle_remaining -= battle_units;
		return experience_per_battle * battle_units;
	} else {
		unsigned int result = experience_per_battle * num_battle_remaining;
		num_battle_remaining = 0;
		return result;
	}
}

unsigned int PokemonGym::GetExperiencePerBattle() {
	return experience_per_battle;
}


bool PokemonGym::Update() {
	if(num_battle_remaining == 0 && state == NOT_DEFEATED) {
		state = DEFEATED;
		display_code = 'g';
		cout << display_code << " " << id_num << " has been beaten" << endl;
		return true;
	} else {
		return false;
	}
	
}

bool PokemonGym::passed() {
	return num_battle_remaining == 0;
}

void PokemonGym::ShowStatus() {
	cout << "PokemonGymStatus: " << endl;
	Building::ShowStatus();
	cout << "Max number of battles: "<< max_number_of_battles << endl;
	cout << "Health cost per battle: " << health_cost_per_battle << endl;
	cout << "PokeDollar per battle: " << PokeDollar_cost_per_battle << endl;
	cout << "Experience per battle: " << experience_per_battle << endl;
	cout << num_battle_remaining << " battle(s) are remaining for this PokemonGym" << endl;
}
