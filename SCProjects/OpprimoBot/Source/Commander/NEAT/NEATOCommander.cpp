#include "NEATOCommander.h"

//Unlike other commanders, NEATOCommander will have a workerSquad to control worker production
bool NEATOCommander::needUnit(UnitType type)
{
	int prevPrio = 1000;

	for (Squad* s : squads)
	{
		if (!s->isFull())
		{
			if (s->getPriority() > prevPrio)
			{
				return false;
			}

			if (s->needUnit(type))
			{
				return true;
			}

			prevPrio = s->getPriority();
		}
	}
}


void NEATOCommander::computeActions()
{
	//computeActionsBase does a lot of macro army movement. dont use it
	//computeActionsBase();

	//Execute the buildplans (buildings, upgrades, techs)
	checkBuildplan();


	int cSupply = Broodwar->self()->supplyUsed() / 2;
	int min = Broodwar->self()->minerals();
	int gas = Broodwar->self()->gas();
}

