#include "RefineryAgent.h"
#include "../MainAgents/WorkerAgent.h"
#include "../Managers/AgentManager.h"
#include "../Commander/Commander.h"

RefineryAgent::RefineryAgent(Unit mUnit)
{
	unit = mUnit;
	type = unit->getType();
	unitID = unit->getID();
	agentType = "RefineryAgent";
}

void RefineryAgent::computeActions()
{
	if (Broodwar->getFrameCount() - lastOrderFrame < 10) return;

	for (int i = 0; i < (int)assignedWorkers.size(); i++)
	{
		if (!assignedWorkers.at(i)->isAlive())
		{
			assignedWorkers.erase(assignedWorkers.begin() + i);
			return;
		}
	}

	if ((int)assignedWorkers.size() < Commander::getInstance()->getWorkersPerRefinery())
	{
		if (!isBeingBuilt() && unit->getPlayer()->getID() == Broodwar->self()->getID())
		{
			WorkerAgent* worker = (WorkerAgent*)AgentManager::getInstance()->findClosestFreeWorker(unit->getTilePosition());
			if (worker != NULL)
			{
				worker->getUnit()->rightClick(unit);
				worker->setState(WorkerAgent::GATHER_GAS);
				assignedWorkers.push_back(worker);
			}
		}
	}

	lastOrderFrame = Broodwar->getFrameCount();
}
