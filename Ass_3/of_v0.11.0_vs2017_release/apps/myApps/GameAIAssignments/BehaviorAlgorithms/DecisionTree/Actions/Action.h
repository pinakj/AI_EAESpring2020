#pragma once
class Action
{
public:

	class AIBoid* character;

	float mQueuedTime = 0.0f;
	float mExpiryTime = 10.0f;

	int prio = 1;

	friend struct ActionList;

	virtual bool CanRunParrallelWith(Action* action) { return false; };

	virtual bool CanInterrupt() { return false; };
	virtual bool CanInterruptAction(Action* action) { return false; };

	virtual bool CanBeInterrupted() { return false; };
	virtual bool CanBeInterruptedByAction(Action* action) { return false; };

	virtual bool IsActionCompleted() { return false; };
	virtual void Execute(float dt) { return; };

	Action(){};
	};

struct ActionList
{
	bool operator() (const Action& a, const Action& b) const {
		return (a.prio > b.prio);
	}
};
