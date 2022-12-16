#include "Trainer.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;
//sequence
bool Trainer::UpdateLocation() {
    if(fabs(destination.x - location.x) <= fabs(delta.x) && fabs(destination.y - location.y) <= fabs(delta.y)) {
        location = destination;
        return true;
    } else {
        location = location + delta;
        health -= 1;
        PokeDollars += GetRandomAmountOfPokemonDollars();
        return false;
    }
}

void Trainer::SetupDestination(Point2D dest) {
    destination = dest;
    delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
}

Trainer::Trainer() : GameObject('T') {
	speed = 5; 
	is_at_center = false; 
	is_IN_GYM = false; 
	health = 20; 
	experience = 0;
	PokeDollars = 0; 
	battles_to_buy = 0;
    potions_to_buy = 0;
   	current_center = NULL;
	current_gym = NULL;
	destination = Point2D();
	cout << "Trainer default constructed." << endl;
}

Trainer::Trainer(char in_code) : GameObject(in_code){
	speed = 5; 
	is_at_center = false; 
	is_IN_GYM = false; 
	health = 20; 
	experience = 0;
	PokeDollars = 0; 
	battles_to_buy = 0;
    potions_to_buy = 0;
   	current_center = NULL;
	current_gym = NULL;
	destination = Point2D();
	state = TrainerStates::STOPPED;
	cout << "Trainer constructed." << endl;
}

Trainer::Trainer(std::string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc) : GameObject(in_loc, in_id, in_code) {
	speed = in_speed;
	name = in_name;
	is_at_center = false; 
	is_IN_GYM = false; 
	health = 20; 
	experience = 0;
	PokeDollars = 0; 
	battles_to_buy = 0;
    potions_to_buy = 0;
   	current_center = NULL;
	current_gym = NULL;
	destination = Point2D();

	cout << "Trainer constructed." << endl;
}

Trainer::~Trainer() {
	cout << "Trainer destructed." << endl;
}

void Trainer::StartMoving(Point2D dest) {
	if (dest.x == location.x && dest.y == location.y) {
		cout <<  display_code << " " << id_num << " : I'm already there. See?" << endl;
		return;
	}

	else if(HasFainted()) {
		cout <<  display_code << " " << id_num << " : My pokemon have fainted. I may move but you cannot see me." << endl;
	} else {
		SetupDestination(dest);
		if (state == TrainerStates::AT_CENTER) { //state leads removetrainer didnt work
			current_center->RemoveOneTrainer();
			current_center = NULL;
		} else if (state == TrainerStates::IN_GYM) {
			current_gym->RemoveOneTrainer();
			current_gym = NULL;
		}
		state = TrainerStates::MOVING;
		cout <<  display_code << " " << id_num << " : On my way." << endl;
	}
}

void Trainer::StartMovingToGym(PokemonGym* gym) {
	Point2D gym_loc = gym->GetLocation();

	if(gym_loc.x == location.x && gym_loc.y == location.y) {
		state = TrainerStates::IN_GYM;
		cout << display_code << " " << id_num << " : I am already at the PokemonGym!" << endl;
		return;
	}
	else if(HasFainted()) {
		cout << display_code << " " << id_num << " : My Pokemon have fainted so I can't move to gym…" << endl;
	} else {
        if(static_cast<int>(this->GetState()) == 3) current_center->RemoveOneTrainer();             // remove trainer behavior(tricky)
        else if(static_cast<int>(this->GetState()) == 4) current_gym->RemoveOneTrainer();
        current_gym = gym;
		SetupDestination(gym_loc);
		state = TrainerStates::MOVING_TO_GYM;           //state
		cout << display_code << " " << id_num << " : On my way to gym " << gym->GetId() << endl;
	}
}

void Trainer::StartMovingToCenter(PokemonCenter* center) {
	Point2D cen_loc = center->GetLocation();

	if(cen_loc.x == location.x && location.y == cen_loc.y) {
		state = TrainerStates::AT_CENTER;   //state
		cout << display_code << " " << id_num << " : I am already at the Center!" << endl;
		return ;
	}

	else if(HasFainted()) {
		cout << display_code << " " << id_num << " : My pokemon have fainted so I should have gone to the center.." << endl;
	} else {
        if(static_cast<int>(this->GetState()) == 3) current_center->RemoveOneTrainer();
        else if(static_cast<int>(this->GetState()) == 4) current_gym->RemoveOneTrainer();
        current_center = center;
		SetupDestination(cen_loc);
		state = TrainerStates::MOVING_TO_CENTER;
		cout << display_code << " " << id_num << " : On my way to center " << (center->GetId()) << endl;
	}
}

void Trainer::StartBattling(unsigned int num_battles) {

	if(HasFainted()) {
		cout << display_code << " " << id_num << " : My Pokemon have fainted so no more battles for me..." << endl;
	} else if (static_cast<int>(this->GetState()) != 4) { // state change
		cout << display_code << " " << id_num << " : I can only battle in a PokemonGym!" << endl;
	} else if (current_gym->passed()) {
		cout << display_code << " " << id_num << " : Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
	} else if (!(current_gym->IsAbleToBattle(num_battles, PokeDollars, health))) {
		cout << display_code << " " << id_num << " : Not enough money for battles" << endl;
	} else {
		state = TrainerStates::BATTLING_IN_GYM;
		cout << "Starting to battle at PokemonGym " << current_gym->GetId() << " with " << num_battles << " battles" << endl;
		if (num_battles > current_gym->GetNumBattlesRemaining()) {
			num_battles = current_gym->GetNumBattlesRemaining();
		}
		battles_to_buy = num_battles;
	}
}

void Trainer::StartRecoveringHealth(unsigned int num_potions) {
	Point2D cen_loc = current_center->GetLocation();

	if (!(current_center->CanAffordPotion(num_potions, PokeDollars))) {
		cout << display_code << id_num << ": Not enough money to recover health." << endl;
	} else if (!current_center->HasPotions()) {
		cout << display_code << id_num << ": Cannot recover! No potion remaining in this Pokemon Center" << endl;
	} else if (location.x != cen_loc.x || location.y != cen_loc.y) {
		cout << display_code << id_num << ": I can only recover health at a Pokemon Center!" << endl;
	} else {
		state = TrainerStates::RECOVERING_HEALTH; // state
		cout << display_code << id_num << ": Started recovering " << num_potions << " at PokemonCenter " << current_center->GetId() << endl;
		if (num_potions > current_center->GetNumPotionRemaining()) {
			num_potions = current_center->GetNumPotionRemaining();
		}
		potions_to_buy = num_potions;
	}
}

void Trainer::Stop() {
	state = TrainerStates::STOPPED; 
	cout <<  display_code << id_num << ": Stopping..." << endl;
}

bool Trainer::HasFainted() {
	return health == 0;
}

bool Trainer::ShouldBeVisible() {
	return !HasFainted();
}

double GetRandomAmountOfPokemonDollars() {
    return double(rand() % 3);        // money generation
}

bool Trainer::Update() {
	unsigned int tmp;
	cout << name << " status:" << endl;

	switch(static_cast<int>(this->GetState())) {
		case 0:
			cout << "Health: " << health << endl;
			cout << "PokeDollars: " << PokeDollars << endl;
			cout << "Experience: " << experience << endl;
			return false;
			break;

		case 1:
			if (UpdateLocation()) {
				cout << "Health: " << health << endl;
				cout << "PokeDollars: " << PokeDollars << endl;
				cout << "Experience: " << experience << endl;
				cout << display_code << id_num << ": I'm there!" << endl;
				state = TrainerStates::STOPPED;
				return true;
			} else {
				cout << "Health: " << health << endl;
				cout << "PokeDollars: " << PokeDollars << endl;
				cout << "Experience: " << experience << endl;
				cout << display_code << id_num << ": step..." << endl;
				return false;
			}
			break;
        case 2:
            return false;
		case 6:
			if (UpdateLocation()) {
				state = TrainerStates::IN_GYM;
				current_gym->AddOneTrainer();
				cout << "Health: " << health << endl;
				cout << "PokeDollars: " << PokeDollars << endl;
				cout << "Experience: " << experience << endl;
				cout << display_code << id_num << ": I'm there!" << endl;
				return true;
			} else {
				cout << "Health: " << health << endl;
				cout << "PokeDollars: " << PokeDollars << endl;
				cout << "Experience: " << experience << endl;
				cout << display_code << id_num << ": step..." << endl;
				return false;
			}
			break;

		case 5:
			if (UpdateLocation()) {
                state = TrainerStates::AT_CENTER; // THIS IS CORRECT NOTATION TO UPDATE STATES
				current_center->AddOneTrainer();
				cout << "Health: " << health << endl;
				cout << "PokeDollars: " << PokeDollars << endl;
				cout << "Experience: " << experience << endl;
				return true;
			} else {
				cout << "Health: " << health << endl;
				cout << "PokeDollars: " << PokeDollars << endl;
				cout << "Experience: " << experience << endl;
				cout << display_code << id_num << ": step..." << endl;
				return false;
			}
			break;

		case 4:
			cout << "Health: " << health << endl;
			cout << "PokeDollars: " << PokeDollars << endl;
			cout << "Experience: " << experience << endl;
			return false;

		case 3:
			cout << "Health: " << health << endl;
			cout << "PokeDollars: " << PokeDollars << endl;
			cout << "Experience: " << experience << endl;
			return false;

		case 7:
			tmp = current_gym->TrainPokemon(battles_to_buy);
			experience += tmp;
			health -= current_gym->GetHealthCost(battles_to_buy); 
			PokeDollars -= current_gym->GetPokeDollarCost(battles_to_buy); 
			cout << "Health: " << health << endl;
			cout << "PokeDollars: " << PokeDollars << endl;
			cout << "Experience: " << experience << endl;
			cout << "**" << name << " completed " << battles_to_buy << " training unit(s)!**" << endl;
			cout << "**" << name << " gained " << tmp << " experience point(s)!**" << endl;
			if (health == 0) {
				state = TrainerStates::FAINTED;
			} else {
				state = TrainerStates::IN_GYM;
			}
			return true;

		case 8:
			tmp = current_center->DistributePotion(potions_to_buy);
			health += tmp;
			PokeDollars -= current_center->GetPokeDollarCost(potions_to_buy);
			cout << "Health: " << health << endl;
			cout << "PokeDollars: " << PokeDollars << endl;
			cout << "Experience: " << experience << endl;
			cout << "**" << name << " recovered " << tmp << " health!**" << endl;
			cout << "**" << name << " bought " << potions_to_buy << " potion(s)!**" << endl;
			state = TrainerStates::AT_CENTER;
			return true;
	}
	return false;
}


void Trainer::ShowStatus() {
	cout << name << " status:" << endl;
	GameObject::ShowStatus();
	switch(static_cast<int>(this->GetState())){
		case 0:
			cout << " stopped" << endl;
			break;

		case 1:
			cout << "moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << endl;
			break;
            
        case 2:
            cout<< this-> name << "is fainted" << endl;
            break;

		case 6:
			cout << "heading to Pokemon Gym " << current_gym->GetId() << " at a speed of " << speed << " at each step of "<< delta << endl;
			break;

		case 5:
			cout << "heading to Pokemon Center " << current_center->GetId() << " at a speed of " << speed << " at each step of "<< delta << endl;
			break;

		case 4:
			cout << "inside PokemonGym " << current_gym->GetId() << endl;
			break;

		case 3:
			cout << "inside Pokemon Center " << current_center->GetId() << endl;
			break;

		case 7:
			cout << "battling in PokemonGym " << current_gym->GetId() << endl;
			break;

		case 8:
			cout << " recovering health in Pokemon Center " << current_center->GetId() << endl;
			break;	
	}
}

string Trainer::GetName() {
	return name;
}
