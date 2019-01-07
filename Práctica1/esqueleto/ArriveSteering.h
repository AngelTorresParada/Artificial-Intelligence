#pragma once

#include "uslscore\USVec2D.h"
class Character;


class ArriveSteering {

public:
	ArriveSteering();

	USVec2D getSteering(USVec2D *, Character *);

	USVec2D velToTarget;
	USVec2D accToTarget;
	USVec2D *target;
	USVec2D *loc;

	void DrawDebug();
};