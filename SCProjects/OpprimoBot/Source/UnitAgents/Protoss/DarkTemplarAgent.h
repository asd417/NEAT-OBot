#ifndef __DARKTEMPLARAGENT_H__
#define __DARKTEMPLARAGENT_H__

#include "../UnitAgent.h"

/**
 * The DarkTemplarAgent handles abilities for Protoss Dark Templar units.
 *
 * Author: Yeonghun Lee (loctitematt417@gmail.com)
 */
class DarkTemplarAgent : public UnitAgent {

private:
	BaseAgent* findDarkArchonTarget();
	bool shouldMakeDarkArchon();
	bool hasCastTransform;

public:
	DarkTemplarAgent(Unit mUnit) : UnitAgent(mUnit)
	{
		agentType = "HighTemplarAgent";
	}

	bool useAbilities();
};

#endif
