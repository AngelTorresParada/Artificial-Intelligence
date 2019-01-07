#pragma once
#include "uslscore\USVec2D.h"
class Character;


class AlignSteering {

public:
	AlignSteering();

	float getSteering(float, Character *);

	float rotToTarget;
	float accToTarget;
	USVec2D target;
	USVec2D loc;
	float rot;
	USVec2D vec;

	void DrawDebug();
};