#include "stdafx.h"
#include "SeekSteering.h"
#include "params.h"
#include "character.h"

SeekSteering::SeekSteering(Character *_c, USVec2D _target) {
	c = _c;
	target = _target;
	accToTarget = USVec2D(0, 0);
	velToTarget = USVec2D(0, 0);
}


void SeekSteering::setCharacter(Character *_c) {
	c = _c;
}

void SeekSteering::setTargetPosition(float _x, float _y) {
	target.mX = _x;
	target.mY = _y;
}


void SeekSteering::getAcceleration(float *_x, float *_y) {
	*_x = accelerationX;
	*_y = accelerationY;
}


USVec2D SeekSteering::getSteering() {
	velToTarget = USVec2D(target.mX - c->GetLoc().mX, target.mY - c->GetLoc().mY);
	velToTarget.NormSafe();
	velToTarget = velToTarget * c->GetMaxVelocity();

	accToTarget = velToTarget - c->GetLinearVelocity();
	accToTarget.NormSafe();
	accToTarget = accToTarget * c->GetMaxAcceleration();

	return accToTarget;
}

void SeekSteering::DrawDebug() {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 1.0f);
	MOAIDraw::DrawPoint(target.mX, target.mY);

	gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 1.0f);
	MOAIDraw::DrawLine(c->GetLoc(), c->GetLoc() + velToTarget);

	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 1.0f);
	MOAIDraw::DrawLine(c->GetLoc(), c->GetLoc() + accToTarget);
	
}
