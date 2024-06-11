#include "NEATOBuildplanEntry.h"

//NEATOBuildplan does not rely on supplycount to build.
//It will build whenever necessary
NEATOBuildplanEntry::NEATOBuildplanEntry(BWAPI::UnitType cType, BWAPI::TilePosition position) : BuildplanEntry(cType, 0)
{
	desiredPosition = position;
}

NEATOBuildplanEntry::NEATOBuildplanEntry(BWAPI::UpgradeType cType, BWAPI::TilePosition position) : BuildplanEntry(cType, 0)
{
	desiredPosition = position;
}

NEATOBuildplanEntry::NEATOBuildplanEntry(BWAPI::TechType cType, BWAPI::TilePosition position) : BuildplanEntry(cType, 0)
{
	desiredPosition = position;
}
