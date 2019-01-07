#include "stdafx.h"
#include "ArriveSteering.h"
#include "Character.h"

ArriveSteering::ArriveSteering() {
	target = new USVec2D(0, 0);
	loc = new USVec2D(0, 0);
	velToTarget = USVec2D(0, 0);
	accToTarget = USVec2D(0, 0);
}


USVec2D ArriveSteering::getSteering(USVec2D *_target, Character *_c) {

	target = _target;
	*loc = _c->GetLoc();

	float lerpSpeed = _target->Dist(_c->GetLoc()) / _c->GetDestRadius();
	if (lerpSpeed < 0) lerpSpeed = 0;
	else {
		if (lerpSpeed > 1) lerpSpeed = 1;
	}

	velToTarget = USVec2D(_target->mX - _c->GetLoc().mX, _target->mY - _c->GetLoc().mY);
	velToTarget.NormSafe();
	velToTarget = velToTarget * _c->GetMaxVelocity() * lerpSpeed;

	accToTarget = velToTarget - _c->GetLinearVelocity();
	//accToTarget.NormSafe();
	accToTarget = accToTarget * _c->GetMaxAcceleration();

	return accToTarget;
	
}


void ArriveSteering::DrawDebug() {
	
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 1.0f);
	MOAIDraw::DrawPoint(target->mX, target->mY);

	gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 1.0f);
	MOAIDraw::DrawLine(*loc, *loc + velToTarget);

	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 1.0f);
	MOAIDraw::DrawLine(*loc, *loc + accToTarget);
	
}
