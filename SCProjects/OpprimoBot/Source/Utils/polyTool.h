#pragma once

#include <BWAPI.h>
#include <BWTA.h>

namespace BWAPI {
	struct PolyTool {
		PolyTool() = default;
		~PolyTool() = default;

		PolyTool& operator=(PolyTool&) = delete;
		PolyTool& operator=(const PolyTool&) = delete;

		bool onSegment(Point<double> p, Point<double> q, Point<double> r);
		int	orientation(Point<double> p, Point<double> q, Point<double> r);
		bool doIntersect(Point<double> p1, Point<double> q1, Point<double> p2, Point<double> q2);
		bool pointIsInside(const BWTA::Polygon& polygon, Point<double> p);
	};
}