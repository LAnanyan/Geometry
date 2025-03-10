#include "Point3D.h"

Point3D::Point3D()
	: Point3D(0., 0., 0.)
{

}

Point3D::Point3D(double x, double y, double z)
	: x(x)
	, y(y)
	, z(z)
{

}

bool operator==(const Point3D& p1, const Point3D& p2)
{
	return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z;
}
