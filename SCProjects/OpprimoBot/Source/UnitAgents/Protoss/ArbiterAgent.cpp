#include "ArbiterAgent.h"

bool ArbiterAgent::useAbilities()
{
	if (isOfType(unit->getType(), UnitTypes::Protoss_Arbiter))
	{
		TechType stasisField = TechTypes::Stasis_Field;
		if (Broodwar->self()->hasResearched(stasisField) && unit->getEnergy() >= 100)
		{
			int range = TechTypes::Stasis_Field.getWeapon().maxRange();
			//Check if enemy units are visible
			for (auto& u : Broodwar->enemy()->getUnits())
			{
				if (u->exists())
				{
					if (unit->getDistance(u) <= range && !u->isStasised())
					{
						if (unit->useTech(stasisField, u->getPosition()))
						{
							Broodwar << "Stasis Field used on " << u->getType().getName() << endl;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
