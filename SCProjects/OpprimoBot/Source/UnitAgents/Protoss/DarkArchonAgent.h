#ifndef __DARKARCHONAGENT_H__
#define __DARKARCHONAGENT_H__

#include "../UnitAgent.h"

/**
 * The DarkArchonAgent handles abilities for Protoss Dark Archon units.
 *
 * Author: Yeonghun Lee (loctitematt417@gmail.com)
 */
class DarkArchonAgent : public UnitAgent {

private:
	BaseAgent* findDarkArchonTarget();
	bool hasCastTransform;
	
public:
	DarkArchonAgent(Unit mUnit) : UnitAgent(mUnit)
	{
		agentType = "DarkArchonAgent";
	}

	bool useAbilities();
};

#endif
