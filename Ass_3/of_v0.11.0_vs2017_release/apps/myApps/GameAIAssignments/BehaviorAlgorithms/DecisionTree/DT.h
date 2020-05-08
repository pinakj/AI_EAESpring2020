#pragma once
#include "DTNode.h"

class DT
{

	DTNode* mRootNode;

public:

	Action* GetAction() {
		return ((DTActionNode*)(mRootNode->MakeDecision()))->GetAction();
	}

	DT(DTNode* iRootNode);
	~DT();
};

