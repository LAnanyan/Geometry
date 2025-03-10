#ifndef Segment3D_h_defined
#define Segment3D_h_defined

#include "Point3D.h"
#include "Unittest.h"

class Segment3D
{
public:

	Segment3D(const Point3D& p1, const Point3D& p2);

public:

	double distance_to(const Segment3D& other) const;

private:

	friend class Segment3DUnittest;

	double squared_distance_to(const Segment3D& other) const;

private:
	
	Point3D p1_;
	Point3D p2_;
};

#endif // !Segment3D_h_defined
