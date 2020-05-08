#include "DTWalk.h"
#include "Boid.h"
#include "DynamicAlign.h"
#include "DynamicArrive.h"
#include "DynamicWander.h"

DTWalk::DTWalk()
{
	prio = 5;
	mExpiryTime = 1;
}


DTWalk::~DTWalk()
{
}

bool DTWalk::CanInterrupt()
{
	return true;
}

bool DTWalk::IsActionCompleted()
{
	ofVec2f distance = character->mTargets.front().mPosition - character->mKinematic.mPosition;
	if (distance.length() <= 100)
	{
		return true;
	}

	return false;
}

void DTWalk::Execute(float dt)
{
	SteeringOutputStructure pos = DynamicArrive::GetSteering(character->mKinematic, character->mTargets.front());
	SteeringOutputStructure rot = DynamicLookWhereYouAreGoing::GetSteering(character->mKinematic);

	character->mKinematic.UpdateDynamicMotion(pos + rot, dt);
	character->mEnergy -= dt * 10;
}

DTWander::DTWander()
{
	mExpiryTime = 1;
}

DTWander::~DTWander()
{
}

bool DTWander::IsActionCompleted()
{
	return false;
}

void DTWander::Execute(float dt)
{
	auto steering = DynamicWander::GetSteering(character->mKinematic);
	character->mKinematic.UpdateDynamicMotion(steering, dt);
	character->mEnergy -= dt * 10;
}
