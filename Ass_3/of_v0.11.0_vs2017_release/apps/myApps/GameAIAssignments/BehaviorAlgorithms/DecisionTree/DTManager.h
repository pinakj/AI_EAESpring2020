#pragma once


#include "Action.h"
#include "AIManager.h"

#include <queue>
#include <list>
#include <vector>

using namespace std;

class Boid;
class DT;


class DTManager : public AIManager
{

	priority_queue<Action*, list<Action*>, ActionList> mPendingList;
	list<Action*> mActiveAction;

	Boid* mCharacter;
	DT* mTree;

public:
	DTManager();
	~DTManager();

	void SetAI(Boid* iBoid, DT* iTree);
	void SetCharacter(Boid* iBoid);
	virtual void Update(float dt);

};

