#ifndef Point3D_h_defined
#define Point3D_h_defined

struct Point3D
{
	Point3D();
	Point3D(double x, double y, double z);

	double x;
	double y;
	double z;
};

bool operator==(const Point3D& vec1, const Point3D& vec2);

#endif // !Point3D_h_defined
