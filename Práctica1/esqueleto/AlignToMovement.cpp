#include "stdafx.h"
#include "AlignToMovement.h"
#include "AlignSteering.h"
#include "character.h"
#define RAD2DEG 180/3.141592

AlignToMovementSteering::AlignToMovementSteering() {
	rotToTarget = 0;
	accToTarget = 0;
	direction = new USVec2D(0, 0);
	loc = new USVec2D(0, 0);
}


float AlignToMovementSteering::getSteering(Character *_c, AlignSteering *_align) {

	float orientation = RAD2DEG * atan2(_c->GetLinearVelocity().mY, _c->GetLinearVelocity().mX);

	return _align->getSteering(orientation, _c);
}


void AlignToMovementSteering::DrawDebug()
{
}
