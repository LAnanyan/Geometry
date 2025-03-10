#include "Vector3D.h"

Vector3D::Vector3D()
	: Vector3D(Point3D())
{

}

Vector3D::Vector3D(const Point3D& p)
	: p_(p)
{

}

double Vector3D::x() const
{
	return p_.x;
}

double Vector3D::y() const
{
	return p_.y;
}

double Vector3D::z() const
{
	return p_.z;
}

Vector3D& Vector3D::operator+=(const Vector3D& vec)
{
	p_.x += vec.p_.x;
	p_.y += vec.p_.y;
	p_.z += vec.p_.z;
	
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& vec)
{
	return *this += -vec;
}

Vector3D Vector3D::operator-() const
{
	return Vector3D(Point3D(-p_.x, -p_.y, -p_.z));
}

Vector3D operator+(const Vector3D& vec1, const Vector3D& vec2)
{
	Vector3D result(vec1);
	return result += vec2;
}

Vector3D operator-(const Vector3D& vec1, const Vector3D& vec2)
{
	return vec1 + -vec2;
}

double operator*(const Vector3D& vec1, const Vector3D& vec2)
{
	return vec1.x() * vec2.x() +
		vec1.y() * vec2.y() +
		vec1.z() * vec2.z();
}

Vector3D operator*(const Vector3D& vec, double factor)
{
	return Vector3D(
		Point3D(vec.x() * factor, 
			vec.y() * factor, 
			vec.z() * factor
		)
	);
}

Vector3D operator*(double factor, const Vector3D& vec)
{
	return vec * factor;
}

