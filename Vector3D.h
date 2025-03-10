#ifndef Vector3D_h_defined
#define Vector3D_h_defined

#include "Point3D.h"

class Vector3D
{
public:

	Vector3D();
    explicit Vector3D(const Point3D& p);

public:

	double x() const;
	double y() const;
	double z() const;

public:

	Vector3D& operator+=(const Vector3D& vec);
	Vector3D& operator-=(const Vector3D& vec);

	Vector3D operator-() const;

private:

	Point3D p_;
};

Vector3D operator+(const Vector3D& vec1, const Vector3D& vec2);
Vector3D operator-(const Vector3D& vec1, const Vector3D& vec2);

double operator*(const Vector3D& vec1, const Vector3D& vec2);
Vector3D operator*(const Vector3D& vec, double factor);
Vector3D operator*(double factor, const Vector3D& vec);

#endif // !Vector3D_h_defined