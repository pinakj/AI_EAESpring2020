#include "DTManager.h"
#include "DT.h"
#include <iostream>


//taken from mit
template<class T, class S, class C>
S& Container(priority_queue<T, S, C>& iQ) {
	struct PriorityQueue : private priority_queue<T, S, C>
	{
		static S& Container(priority_queue<T, S, C>& iQ) {
			return iQ.*&PriorityQueue::c;
		}
	};
	return PriorityQueue::Container(iQ);
}

DTManager::DTManager()
{
}


DTManager::~DTManager()
{
}

void DTManager::SetAI(Boid * iBoid, DT * iTree)
{
	mCharacter = iBoid;
	mTree = iTree;
}

void DTManager::SetCharacter(Boid * iBoid)
{
	mCharacter = iBoid;
}

void DTManager::Update(float dt)
{
	auto action = mTree->GetAction();
	action->character = (AIBoid*)mCharacter;
	action->mQueuedTime = 0;

	list<Action*>& pendingList = Container(mPendingList);
	pendingList.push_back(action);

	auto& itr = pendingList.begin();
	while (itr != pendingList.end())
	{
		(*itr)->mQueuedTime += dt;
		std::cout << (*itr)->mQueuedTime << std::endl;


		/// Action Wait Time Expired
		if ((*itr)->mQueuedTime > (*itr)->mExpiryTime)
		{
			itr = pendingList.erase(itr);
			continue;
		}

		/// Check if Can Run Parallel with all active actions
		bool parallel = true;
		for (auto& active : mActiveAction)
		{
			if (!(*itr)->CanRunParrallelWith(active))
			{
				parallel = false;
				break;
			}
		}
		/// Action can run parallel so transfer action from pending to active
		if (parallel)
		{
			mActiveAction.push_back(*itr);
			itr = pendingList.erase(itr);
			continue;
		}

		/// Check if this action can interupt any action
		if ((*itr)->CanInterrupt())
		{
			bool isHighPriority = true;
			for (auto active : mActiveAction)
			{
				if (active->prio >= (*itr)->prio)
				{
					isHighPriority = false;
					break;
				}
			}

			if (!isHighPriority)
			{
				itr++;
				continue;
			}

			auto& active = mActiveAction.begin();
			while (active != mActiveAction.end())
			{
				if (!(*itr)->CanRunParrallelWith(*active))
				{
					active = mActiveAction.erase(active);
					continue;
				}
				active++;
			}

			mActiveAction.push_back(*itr);
			itr = pendingList.erase(itr);
			continue;
		}

		itr++;
	}

	auto& activeAction = mActiveAction.begin();
	while (activeAction != mActiveAction.end())
	{
		if ((*activeAction)->IsActionCompleted())
		{
			activeAction = mActiveAction.erase(activeAction);
		}
		else
		{
			(*activeAction)->Execute(dt);
			activeAction++;
		}
	}

}
