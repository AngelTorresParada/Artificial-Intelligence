#include "stdafx.h"
#include "AlignSteering.h"
#include "Character.h"

AlignSteering::AlignSteering() {
	target = USVec2D(0,0);
	loc = USVec2D(0, 0);
	rot = 0;
}

float AlignSteering::getSteering(float _target, Character *_c) {
	rot = _c->GetRot();
	if (rot >= 180) rot -= 360;
	else if (rot <= -180) rot += 360;
	printf("%.2f\n", rot);
	loc = _c->GetLoc();
	rotToTarget = _target - rot;
	
	float arriveAngle = 5;

	float lerpRot = abs(rotToTarget) / arriveAngle;
	if (lerpRot >= 1) lerpRot = 1;
	else if (lerpRot <= 0) lerpRot = 0;

	if (rotToTarget >= 180) rotToTarget -= 360;
	else if (rotToTarget <= -180) rotToTarget += 360;
	rotToTarget = rotToTarget * _c->GetMaxAngularVelocity() * lerpRot;

	accToTarget = rotToTarget - _c->GetAngularVelocity();
	accToTarget = accToTarget * _c->GetMaxAngularAcceleration();

	return accToTarget;
}

void AlignSteering::DrawDebug() {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 1.0f);
	MOAIDraw::DrawLine(loc, target);
}


