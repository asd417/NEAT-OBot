#include "BWAPI.h"
#include "../BuildplanEntry.h"

class NEATOBuildplanEntry : BuildplanEntry {

public:
	NEATOBuildplanEntry(BWAPI::UnitType cType, BWAPI::TilePosition position);
	NEATOBuildplanEntry(BWAPI::UpgradeType cType, BWAPI::TilePosition position);
	NEATOBuildplanEntry(BWAPI::TechType cType, BWAPI::TilePosition position);

private:
	BWAPI::TilePosition desiredPosition;

};