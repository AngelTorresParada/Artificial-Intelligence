#pragma once
#include "uslscore\USVec2D.h"
class Character;
class AlignSteering;


class AlignToMovementSteering {

public:
	AlignToMovementSteering();

	float getSteering(Character *, AlignSteering *);

	float rotToTarget;
	float accToTarget;
	USVec2D *direction;
	USVec2D *loc;

	void DrawDebug();
};