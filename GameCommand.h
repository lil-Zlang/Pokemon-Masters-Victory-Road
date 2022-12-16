#ifndef _GAMECOMMAND_H
#define _GAMECOMMAND_H

#include "GameObject.h"
#include "Model.h"
#include "View.h"

class Model;
class View;

void DoMoveCommand(Model& model, int trainer_id, Point2D p1);
void DoMoveToCenterCommand(Model& model, int trainer_id, int center_id);
void DoMoveToGymCommand(Model& model, int trainer_id, int gym_id);
void DoStopCommand(Model& model, int trainer_id);
void DoTrainInGymCommand(Model& model, int trainer_id, unsigned int battles);
void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed);
void DoGoCommand(Model& model, View& view);
void DoRunCommand(Model& model, View& view);

#endif