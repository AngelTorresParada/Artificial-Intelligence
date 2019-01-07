#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <moaicore/MOAIEntity2D.h>
#include <params.h>
#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "AlignSteering.h"
#include "AlignToMovement.h"

class Character: public MOAIEntity2D
{
public:
    DECL_LUA_FACTORY(Character)
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float step);
public:
	virtual void DrawDebug();

	Character();
	~Character();
	
	void SetLinearVelocity(float x, float y) { mLinearVelocity.mX = x; mLinearVelocity.mY = y;}
	void SetAngularVelocity(float angle) { mAngularVelocity = angle;}

	float GetMaxAcceleration();
	float GetMaxVelocity();
	float GetDestRadius();
	float GetMaxAngularAcceleration();
	float GetMaxAngularVelocity();
	float GetAngularArriveRadius();
	
	USVec2D GetLinearVelocity() const { return mLinearVelocity;}
	float GetAngularVelocity() const { return mAngularVelocity;}
	USVec2D GetTargetPosition() { return mParams.targetPosition; }
private:
	USVec2D mLinearVelocity;
	float mAngularVelocity;
	
	Params mParams;
	SeekSteering *s;
	ArriveSteering *a;
	AlignSteering *align;
	AlignToMovementSteering *atom;
	
	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
};

#endif