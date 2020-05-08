#pragma once

#include "Action.h"
#include "Structures.h"

class DTWalk:public Action
{
public:
	DTWalk();
	~DTWalk();

	virtual bool CanInterrupt() override;
	virtual bool IsActionCompleted() override;
	virtual void Execute(float dt) override;
};

class DTWander:public Action
{
public:
	DTWander();
	~DTWander();

	virtual bool IsActionCompleted() override;
	virtual void Execute(float dt) override;
};