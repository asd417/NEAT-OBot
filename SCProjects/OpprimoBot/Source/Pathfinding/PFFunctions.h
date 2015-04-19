#ifndef __PFFUNCTIONS_H__
#define __PFFUNCTIONS_H__

#include "../MainAgents/BaseAgent.h"

using namespace BWAPI;
using namespace std;

/** Helper class for the NavigationAgent. Contains methods to calculate the potentials generated by own units, enemy units
 * and neutral objects in specific points.
 *
 * Author: Johan Hagelback (johan.hagelback@gmail.com)
 */
class PFFunctions {

private:
	
public:

	/** Returns the distance between two positions. */
	static float getDistance(WalkPosition w1, WalkPosition w2);

	/** Returns the distance between a unit and a position. */
	static float getDistance(WalkPosition wt, Unit unit);

	/** Calculates the potential otherOwnUnit generates around unit at distance d. */
	static float calcOwnUnitP(float d, WalkPosition wt, Unit unit, Unit otherOwnUnit);

	/** Calculates the terrain potential in a position. */
	static float getTerrainP(BaseAgent* agent, WalkPosition wt);

	/** Calculates the trail potential in a position. Trails are used to reduce the local
	 * optima problem when using potential fields. */
	static float getTrailP(BaseAgent* agent, WalkPosition wt);

	/** Calculates the goal potential for a defending unit. */
	static float getGoalP(BaseAgent* agent, WalkPosition wt);

	/** Calculates the potential an offensive attacking unit generates at distance d around an enemy unit. */
	static float calcOffensiveUnitP(float d, Unit attacker, Unit enemy);
	
	/** Calculates the potential a defensive attacking unit generates at distance d around an enemy unit. */
	static float calcDefensiveUnitP(float d, Unit attacker, Unit enemy);

	/** Returns true if the own unit can attack the target. */
	static bool canAttack(Unit ownUnit, Unit target);

	/** Returns the max range for the unit targeting ground. */
	static int getGroundRange(Unit cUnit);

	/** Returns the max range for the unit targeting air. */
	static int getAirRange(Unit cUnit);
	
};

#endif
