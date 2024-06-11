#include "DarkArchonAgent.h"
#include "../../Pathfinding/NavigationAgent.h"
#include "../../Managers/AgentManager.h"
#include "../../Commander/Commander.h"


bool DarkArchonAgent::useAbilities()
{
	if (isOfType(unit->getType(), UnitTypes::Protoss_Dark_Archon))
	{
		//Not transformed to Archon. Use spells.

		//PSI storm
		TechType maelstrom = TechTypes::Maelstrom;
		if (Broodwar->self()->hasResearched(maelstrom) && unit->getEnergy() >= 100)
		{
			int range = TechTypes::Maelstrom.getWeapon().maxRange();
			//Check if enemy units are visible
			for (auto& u : Broodwar->enemy()->getUnits())
			{
				if (u->exists())
				{
					if (unit->getDistance(u) <= range && u->getType().isOrganic() && !u->isBurrowed())
					{
						if (unit->useTech(maelstrom, u->getPosition()))
						{
							Broodwar << "Maelstrom used on " << u->getType().getName() << endl;
							return true;
						}
					}
				}
			}
		}

	}

	return false;
}
