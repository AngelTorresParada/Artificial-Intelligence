#pragma once

#include "uslscore\USVec2D.h"
class Character;


class SeekSteering {

	Character *c;
	USVec2D target;
	float accelerationX;
	float accelerationY;
	

	public:
		SeekSteering(Character *, USVec2D);
		void setCharacter(Character *);
		void setTargetPosition(float, float);

		void getAcceleration(float *, float *);
		USVec2D getSteering();

		void DrawDebug();
		
		USVec2D velToTarget;
		USVec2D accToTarget;
};