#pragma once

#include "Action.h"
#include "Structures.h"

class RandomSpeed : public Action
{

public:
	RandomSpeed() { prio = 15; 	mExpiryTime = 3;};

	float timer;

	virtual bool CanBeInterrupted() override;
	virtual bool CanInterrupt() override;
	virtual bool IsActionCompleted() override;
	virtual void Execute(float dt) override;
};

