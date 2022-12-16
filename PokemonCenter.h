#ifndef _POKEMONCENTER_H
#define _POKEMONCENTER_H

#include "GameObject.h"
#include "Building.h"
#include <iostream>

enum PokemonCenterStates { 
	POTIONS_AVAILABLE = 0,
	NO_POTIONS_AVAILABLE = 1
};

class PokemonCenter: public Building {
private:
	unsigned int potion_capacity;
	unsigned int num_potions_remaining;
	double pokedollar_cost_per_potion;

public:
	PokemonCenter();
	PokemonCenter (int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc);
	~PokemonCenter();
	bool HasPotions();
	unsigned int GetNumPotionRemaining();
	bool CanAffordPotion(unsigned int potion, double budget);
	double GetPokeDollarCost(unsigned int potion);
	unsigned int DistributePotion(unsigned int potion_needed);
	bool Update();
	void ShowStatus();
};

#endif