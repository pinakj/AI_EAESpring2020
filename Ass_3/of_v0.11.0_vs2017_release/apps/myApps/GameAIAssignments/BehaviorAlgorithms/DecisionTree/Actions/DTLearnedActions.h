#pragma once
#include "Action.h"
#include "Boid.h"
#include "DynamicPathFollow.h"
#include "DynamicAlign.h"
#include "Structures.h"
#include "DTNode.h"

class DTActionTarget:public Action
{
	bool mCompleted = false;

public:
	DTActionTarget() {
		mExpiryTime = 1;
	}

	~DTActionTarget() {

	}

	function<void()> GetTarget;

	virtual bool CanInterrupt() override {
		return true;
	}

	virtual bool IsActionCompleted() override {

		if (mCompleted)
		{
			mCompleted = false;
			return true;
		}

		return false;

	}

	virtual void Execute(float dt) override {
		mCompleted = true;
		GetTarget();
	}
};

class DTMoveToTarget : public Action
{
	bool mCompleted = false;

public:
	DTMoveToTarget() {
		mExpiryTime = 1;
	}

	~DTMoveToTarget() {

	}

	function<void()> GetTarget;

	virtual bool CanInterrupt() override {
		return true;
	}

	virtual bool IsActionCompleted() override {
		return character->mTargets.empty();
	}

	virtual void Execute(float dt) override {
		auto posSteering = DynamicPathFollow::GetSteering(character->mKinematic, character->mTargets);
		auto rotSteering = DynamicLookWhereYouAreGoing::GetSteering(character->mKinematic);

		character->mKinematic.UpdateDynamicMotion(posSteering + rotSteering, dt);
		((AIBoid*)character)->mEnergy -= 0.166666667f * 0.9f;
	}
};