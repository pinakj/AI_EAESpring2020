#include "RandomSpeed.h"
#include "Boid.h"
#include "DynamicAlign.h"
#include "DynamicArrive.h"


bool RandomSpeed::CanBeInterrupted()
{
	return false;
}

bool RandomSpeed::CanInterrupt()
{
	return true;
}

bool RandomSpeed::IsActionCompleted()
{
	return false;
}

void RandomSpeed::Execute(float dt)
{
	float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.5f));
	character->setColor(ofColor(0,0,0));
	character->mKinematic.mVelocity = ofVec2f(character->mKinematic.mVelocity.x*r2, character->mKinematic.mVelocity.y*r2);
}
