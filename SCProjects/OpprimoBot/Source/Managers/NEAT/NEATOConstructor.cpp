
#include "NEATOConstructor.h"
#include "../AgentManager.h"
#include "../ResourceManager.h"
#include "../../MainAgents/WorkerAgent.h"

NEATOConstructor* NEATOConstructor::instance = NULL;

NEATOConstructor::NEATOConstructor() {
	lastCallFrame = Broodwar->getFrameCount();
}

NEATOConstructor::~NEATOConstructor() {
	NEATOConstructor::instance = NULL;
}

NEATOConstructor* NEATOConstructor::getInstance()
{
	if (instance == NULL)
	{
		instance = new NEATOConstructor();
	}
	return instance;
}

void NEATOConstructor::computeActions()
{
	//Check if we need more supply buildings
	// NEATOCommander doesn't do that. We'll let the neural network figure that out

	//Check if we need to expand
	// NEATOCommander doesn't do that. We'll let the neural network figure that out

	if (buildPlan.size() == 0 && buildQueue.size() == 0)
	{
		//Nothing to do
		return;
	}

	//Dont call too often
	int cFrame = Broodwar->getFrameCount();
	if (cFrame - lastCallFrame < 10)
	{
		return;
	}
	lastCallFrame = cFrame;

	if (AgentManager::getInstance()->getNoWorkers() == 0)
	{
		//No workers so cant do anything
		return;
	}

	//Check if we have possible "locked" items in the buildqueue
	// NEATOCommander doesn't do that. We'll let the neural network figure that out

	//Check if we can build next building in the buildplan
	if ((int)buildPlan.size() > 0)
	{
		executeOrder(buildPlan.at(0));
	}
}

bool NEATOConstructor::executeOrder(UnitType type)
{
	//Max 5 concurrent buildings allowed at the same time
	if ((int)buildQueue.size() >= 5)
	{
		return false;
	}

	//Check if we meet requirements for the building
	map<UnitType, int> reqs = type.requiredUnits();
	for (map<UnitType, int>::iterator j = reqs.begin(); j != reqs.end(); j++)
	{
		if (!AgentManager::getInstance()->hasBuilding((*j).first))
		{
			return false;
		}
	}

	//Default Opprimobot lets BuildingPlacer decide where to place building.
	//NEATOCommander will use neural network to decide that

	//if (type.isResourceDepot())
	//{
	//	TilePosition pos = BuildingPlacer::getInstance()->findExpansionSite();
	//	if (pos.x == -1)
	//	{
	//		//No expansion site found.
	//		if ((int)buildPlan.size() > 0) buildPlan.erase(buildPlan.begin());
	//		return true;
	//	}
	//}

	if (type.isRefinery())
	{
		TilePosition rSpot = BuildingPlacer::getInstance()->searchRefinerySpot();
		if (rSpot.x < 0)
		{
			//No buildspot found
			if ((int)buildPlan.size() > 0) buildPlan.erase(buildPlan.begin());
			return true;
		}
	}
	
	//Check if we have resources
	if (!ResourceManager::getInstance()->hasResources(type))
	{
		return false;
	}

	// build Zerg building that morphs without worker
	if (isZerg())
	{
		pair<UnitType, int> builder = type.whatBuilds();
		if (builder.first.getID() != UnitTypes::Zerg_Drone.getID())
		{
			//Needs to be morphed
			if (executeMorph(builder.first, type))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	//Check if we have a free worker
	bool found = false;
	BaseAgent* a = AgentManager::getInstance()->findClosestFreeWorker(Broodwar->self()->getStartLocation());
	if (a != NULL)
	{
		WorkerAgent* w = (WorkerAgent*)a;
		found = true;
		//Actually build
		if (w->assignToBuild(type))
		{
			lock(0, a->getUnitID());
			return true;
		}
		else
		{
			//Unable to find a buildspot. Dont bother checking for all
			//other workers
			handleNoBuildspotFound(type);
			return false;
		}
	}

	return false;
}
