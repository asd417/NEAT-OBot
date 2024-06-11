#include "DarkTemplarAgent.h"
#include "../../Pathfinding/NavigationAgent.h"
#include "../../Managers/AgentManager.h"

#include "../../Commander/Commander.h"

bool DarkTemplarAgent::useAbilities()
{
	if (isOfType(unit->getType(), UnitTypes::Protoss_Dark_Templar))
	{
		//Morph to Archon	
		if (!isBeingBuilt())
		{
			Squad* sq = Commander::getInstance()->getSquad(squadID);
			if (sq != NULL)
			{
				if (sq->morphsTo().getID() == UnitTypes::Protoss_Dark_Archon.getID())
				{
					// Check if maelstrom has been researched
					if (!enemyUnitsVisible() && !hasCastTransform && shouldMakeDarkArchon())
					{
						BaseAgent* target = findDarkArchonTarget();
						if (target != NULL)
						{
							if (unit->useTech(TechTypes::Dark_Archon_Meld, target->getUnit()))
							{
								hasCastTransform = true;
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}

bool DarkTemplarAgent::shouldMakeDarkArchon() {
	return Broodwar->self()->hasResearched(TechTypes::Enum::Maelstrom) || Broodwar->self()->isResearching(TechTypes::Enum::Maelstrom);
}

BaseAgent* DarkTemplarAgent::findDarkArchonTarget()
{
	Squad* mSquad = Commander::getInstance()->getSquad(squadID);
	if (mSquad != NULL)
	{
		Agentset agents = mSquad->getMembers();
		for (auto& a : agents)
		{
			if (a->isAlive() && a->getUnitID() != unitID && a->isOfType(UnitTypes::Protoss_Dark_Templar) && !a->isBeingBuilt())
			{
				double dist = a->getUnit()->getPosition().getDistance(unit->getPosition());
				if (dist <= 64)
				{
					return a;
				}
			}
		}
	}

	return NULL;
}
