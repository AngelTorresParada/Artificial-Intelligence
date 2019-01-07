#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include <params.h>



Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{

	RTTI_BEGIN
		RTTI_EXTEND (MOAIEntity2D)
	RTTI_END

}


Character::~Character()
{

}


float Character::GetMaxAcceleration() {
	return mParams.max_acceleration;
}


float Character::GetMaxVelocity() {
	return mParams.max_velocity;
}


float Character::GetDestRadius() {
	return mParams.dest_radius;
}


float Character::GetMaxAngularAcceleration() {
	return mParams.max_angular_acceleration;
}


float Character::GetMaxAngularVelocity() {
	return mParams.max_angular_velocity;
}

float Character::GetAngularArriveRadius() {
	return mParams.angular_arrive_radius;
}


void Character::OnStart()
{
    ReadParams("params.xml", mParams);
	a = new ArriveSteering();
	s = new SeekSteering(this, mParams.targetPosition);
	align = new AlignSteering();
	atom = new AlignToMovementSteering();
	
}

void Character::OnStop()
{

}


void Character::OnUpdate(float step) {

	USVec2D acceleration = a->getSteering(&mParams.targetPosition, this);

	
	SetLinearVelocity(GetLinearVelocity().mX + step * acceleration.mX, GetLinearVelocity().mY + step * acceleration.mY);
	SetLoc(USVec3D(GetLoc().mX + step * GetLinearVelocity().mX, GetLoc().mY + step * GetLinearVelocity().mY, 0));

	float rotation = atom->getSteering(this, align);
	SetAngularVelocity(GetAngularVelocity() + step * rotation);
	SetRot(GetRot() + step * GetAngularVelocity());
}


void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);

	//s->DrawDebug();
	//a->DrawDebug();
	align->DrawDebug();
}





// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}
	