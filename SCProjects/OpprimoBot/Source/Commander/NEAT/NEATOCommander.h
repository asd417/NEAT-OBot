#include "../Commander.h"
#include "db.h"


class NEATOCommander : public Commander {
public:
	NEATOCommander();
	~NEATOCommander();

	virtual void computeActions();

	/** Returns the unique id for this strategy. */
	static string getStrategyId()
	{
		return "NEATO";
	}

	bool needUnit(UnitType type);

	//NEATOCommander will control the number of the squads, (up to 4?) and composition of the squad.
	//Also, it controls the movement of the squads
};