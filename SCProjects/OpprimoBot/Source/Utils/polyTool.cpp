#include "polyTool.h"
namespace BWAPI {

	// Function to check if a point is on a line segment
	bool PolyTool::onSegment(Point<double> p, Point<double> q, Point<double> r) {
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;
	return false;
	}

	// To find the orientation of the ordered triplet (p, q, r).
	// The function returns:
	// 0 -> p, q, and r are collinear
	// 1 -> Clockwise
	// 2 -> Counterclockwise
	int PolyTool::orientation(Point<double> p, Point<double> q, Point<double> r) {
	double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
	}

	// Function to check if two line segments intersect
	bool PolyTool::doIntersect(Point<double> p1, Point<double> q1, Point<double> p2, Point<double> q2) {
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1, and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1, and q2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2, and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2, and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false;
	}

	// Function to check if a point is inside a polygon
	bool PolyTool::pointIsInside(const BWTA::Polygon& polygon, Point<double> p) {
	int n = polygon.size();
	if (n < 3) return false;

	// Create a point for the ray
	Point<double> extreme = { 1e10, p.y };

	// Count intersections of the above line with polygon edges
	int count = 0, i = 0;
	do {
		int next = (i + 1) % n;

		// Check if the line segment from polygon[i] to polygon[next] intersects with the ray
		if (doIntersect(polygon[i], polygon[next], p, extreme)) {
			// If the point p is collinear with line segment i-next, check if it lies on the segment
			if (orientation(polygon[i], p, polygon[next]) == 0)
				return onSegment(polygon[i], p, polygon[next]);

			count++;
		}
		i = next;
	} while (i != 0);

	// Return true if count is odd, false otherwise
	return count & 1; // Same as (count % 2 == 1)
	}
}