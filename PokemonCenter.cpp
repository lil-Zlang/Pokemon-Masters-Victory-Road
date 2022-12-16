#include "PokemonCenter.h"
#include <iostream>

using namespace std;

PokemonCenter::PokemonCenter() : Building() {
	display_code = 'C';
	potion_capacity = 100;
	num_potions_remaining = potion_capacity;
	pokedollar_cost_per_potion = 5;
	state = POTIONS_AVAILABLE;
	cout << "PokemonCenter default constructed" << endl;
}

PokemonCenter::PokemonCenter(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc) : Building('C', in_id, in_loc) {
	id_num = in_id;
	location = in_loc;
	pokedollar_cost_per_potion= potion_cost;
	potion_capacity = potion_cap;
	num_potions_remaining = potion_capacity;
	cout << "PokemonCenter constructed" << endl;
	state = POTIONS_AVAILABLE;
}

PokemonCenter::~PokemonCenter() {
	cout << "PokemonCenter destructed." << endl;
}

bool PokemonCenter::HasPotions(){ 
	if(num_potions_remaining >= 1) {
		return true; 
	} else {
		return false;
	}
}
unsigned int PokemonCenter::GetNumPotionRemaining() {
	return num_potions_remaining;
}

bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget) {
	if(budget >= GetPokeDollarCost(potion)) {
		return true;
	} else {
		return false;
	}
}

double PokemonCenter::GetPokeDollarCost(unsigned int potion) {
	return pokedollar_cost_per_potion * potion;
}

unsigned int PokemonCenter::DistributePotion(unsigned int points_needed) { // Potion Health Recovery Param
	if(num_potions_remaining >= points_needed) {
		num_potions_remaining -= points_needed;
		return points_needed * 5;       // Potion Health Recovery Param
	} else {
		unsigned int result = num_potions_remaining;
		num_potions_remaining = 0;          // Potion Health Recovery Param
		return result * 5;
	}
}

bool PokemonCenter::Update() {
	if (num_potions_remaining == 0 && state == POTIONS_AVAILABLE) {
		state = NO_POTIONS_AVAILABLE;
		display_code = 'c';
		cout << "PokemonCenter " << id_num << " has ran out of potions." << endl;
		return true;
	} else {
		return false;
	}
}
void PokemonCenter::ShowStatus() {
	cout << "Pokemon Center Status: " << endl;
	Building::ShowStatus();
	cout << "Pokemon dollars per potion: " << pokedollar_cost_per_potion << endl;
	cout << "has " << num_potions_remaining << " potion(s) remaining." << endl; // was displaying capacity vs potions remaining (display issue)
}
