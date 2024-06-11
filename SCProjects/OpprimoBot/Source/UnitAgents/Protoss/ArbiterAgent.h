#ifndef __ARBITERAGENT_H__
#define __ARBITERAGENT_H__

#include "../UnitAgent.h"

/**
 * The ArbiterAgent handles abilities for Protoss Arbiter flying units.
 *
 * Author: Yeonghun Lee (loctitematt417@gmail.com)
 */
class ArbiterAgent : public UnitAgent {

private:

public:
	ArbiterAgent(Unit mUnit) : UnitAgent(mUnit)
	{
		agentType = "ArbiterAgent";
	}

	bool useAbilities();
};

#endif
