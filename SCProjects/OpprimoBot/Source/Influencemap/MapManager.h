#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__

#pragma once

#include <BWAPI.h>
#include <BWTA.h>

#include <map>
#include "../Utils/Sets.h"
//using namespace BWAPI;
//using namespace BWTA;
//using namespace std;

//#include <CGAL/Simple_cartesian.h>
//#include <CGAL/Segment_Delaunay_graph_2.h>
//#include <CGAL/Segment_Delaunay_graph_traits_2.h>
//#include <CGAL/Polygon_2.h>

//namespace CGAL {
//
//typedef CGAL::Simple_cartesian<leda_bigfloat>    CKD;
//typedef CGAL::Polygon_2<CKD> PolygonD;
//std::map<const BWTA::Polygon*, PolygonD> polygonDs;
//}
//using namespace CGAL;
namespace BWAPI {

	//template <typename T>
	//struct CKD : Simple_cartesian<T> {};

	//template <typename T>
	//struct PolygonD : CGAL::Polygon_2<T> {};

	//template <typename T>
	//struct PointD : CGAL::Point_2<T> {};


struct MRegion {
	BWTA::Region* region;
	int inf_own_ground;
	int inf_own_air;
	int inf_own_buildings;
	int inf_en_ground;
	int inf_en_air;
	int inf_en_buildings;

	void resetInfluence()
	{
		inf_own_ground = 0;
		inf_own_air = 0;
		inf_own_buildings = 0;
		inf_en_ground = 0;
		inf_en_air = 0;
		inf_en_buildings = 0;
	}
};

class MRegionSet : public SetContainer<MRegion*, std::hash<void*>> {
public:

};

/** This class creates an influence map where own and enemy influence (buildings, ground strength,
 * air strength) are calculate for each BWTA region.
 *
 * Author: Johan Hagelback (johan.hagelback@gmail.com)
 */
class MapManager {

private:
	MRegionSet map;
	BaseLocationSet bases;
	StartLocationSet starts;
	int lastCallFrame;
	
	MapManager();
	static MapManager* instance;

	MRegion* getMapFor(Position p);

	const MRegion* getMapRegion(const BWTA::Region* r);
	const BWTA::Chokepoint* findGuardChokepoint(const MRegion* mr);
	bool isValidChokepoint(const Chokepoint* cp);
	
public:
	/** Destructor */
	~MapManager();

	/** Returns the instance of the class. */
	static MapManager* getInstance();

	/** Updates the influence map. */
	void update();

	/** Returns a good chokepoint to place defensive forces at. */
	const BWTA::Chokepoint* getDefenseLocation();

	/** Checks if any region with enemy influence has been found. */
	bool hasEnemyInfluence();

	/** Returns a suitable position to attack the enemy at. */
	TilePosition findAttackPosition();

	/** Returns the closest spotted enemy building. If no building has been spotted, a player starting location is returned instead. */
	TilePosition findRushPosition();

	/** Checks if the player has infuence in the specified position. */
	bool hasOwnInfluenceIn(TilePosition pos);

	/** Checks if the enemy has influence in the specified position. */
	bool hasEnemyInfluenceIn(TilePosition pos);

	/** Returns the player ground unit infuence in the specified position. */
	int getOwnGroundInfluenceIn(TilePosition pos);

	/** Returns the enemy ground influence in the specified position. */
	int getEnemyGroundInfluenceIn(TilePosition pos);

	/** Prints debug info to screen. */
	void printInfo();
};

	
}

#endif
