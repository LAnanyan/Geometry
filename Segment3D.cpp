#include "Segment3D.h"
#include "Vector3D.h"

#include <limits>
#include <cmath>
#include <algorithm>
#include <stdexcept>

Segment3D::Segment3D(const Point3D& p1, const Point3D& p2)
	: p1_(p1)
	, p2_(p2)
{
	if (p1_ == p2_)
	{
		throw std::invalid_argument("The segment's endpoints must be different");
	}
}

double Segment3D::distance_to(const Segment3D& other) const
{
	return std::sqrt(squared_distance_to(other));
}

double Segment3D::squared_distance_to(const Segment3D& other) const
{
	// Imagine we have two segments: s1, and s2, 
	// where each of the segemnts has two endpoints: p1, and p2, 
	// with the corresponding x, y, z coordinates.
	// We can represent their parametrized equation as:
	// { x1 = s1.p1.x + (s1.p2.x - s1.p1.x) * t
	// { y1 = s1.p1.y + (s1.p2.y - s1.p1.y) * t , where t lies between [0, 1]
	// { z1 = s1.p1.z + (s1.p2.z - s1.p1.z) * t
	// 
	// { x2 = s2.p1.x + (s2.p2.x - s2.p1.x) * s
	// { y2 = s2.p1.y + (s2.p2.y - s2.p1.y) * s , where s lies between [0, 1]
	// { z2 = s2.p1.z + (s2.p2.z - s2.p1.z) * s

	// The formula of the distance (D) of two segments is:
	// D ^ 2 = (x1 - x2) ^ 2 + (y1 - y2) ^ 2 + (z1 - z2) ^ 2 (1)

	// We can write the right part of the equation (1) as:
	// (s1.p1.x + (s1.p2.x - s1.p1.x) * t - (s2.p1.x + (s2.p2.x - s2.p1.x) * s)) ^ 2 +
	// (s1.p1.y + (s1.p2.y - s1.p1.y) * t - (s2.p1.y + (s2.p2.y - s2.p1.y) * s)) ^ 2 +
	// (s1.p1.z + (s1.p2.z - s1.p1.z) * t - (s2.p1.z + (s2.p2.z - s2.p1.z) * s)) ^ 2 (2)

	// Now let's assume the result as a function with two variable arguments (t and s): f(t, s)

	// s^
	//  |
	// 1|------
	//  |     |       (3)
	//  |     |
	// -+--------->
	// 0|     1   t

	// We should find all those t and s, which lie in [0, 1] square (3) 
	// { d(f(t, s)) / d(t) = 0
	// { d(f(t, s)) / d(s) = 0

	// If we calculate the derivatives and simplify the equations, we can represent the system like:
	// { A * t + B * s + C = 0
	// { D * t + E * s + F = 0

	// We will find the solution to the equation by using the Cramer's rule:
	// t = (B * F - C * E) / (A * E - B * D)
	// s = (A * F - C * B) / (A * E - B * D)

	const Vector3D rp11(p1_);
	const Vector3D rp12(p2_);
	const Vector3D rp21(other.p1_);
	const Vector3D rp22(other.p2_);

	const Vector3D r1 = rp12 - rp11;
	const Vector3D r2 = rp22 - rp21;
	const Vector3D d1 = rp11 - rp21;
	const Vector3D d2 = rp12 - rp22;

	const double A = r1 * r1;
	const double B = -r1 * r2;
	const double C = d1 * r1;
	const double D = B;
	const double E = r2 * r2;
	const double F = -d1 * r2;
	const double denom = A * E - B * D;

	// NOTE: we will use the squared distances throughout the calculation
	double min_squared_distance = std::numeric_limits<double>::max();

	Vector3D d;

	// If the denominator is zero, it means the segments are on the smame line or parallel lines.
	// Otherwise, if result t and s values lie in [0, 1], then we can put them in the (2) 
	// equation to get our first candidate distance:
	if (std::abs(denom) > std::numeric_limits<double>::epsilon())
	{
		const double t = (B * F - C * E) / denom;
		const double s = (C * D - A * F) / denom;

		if (t >= 0. && t <= 1. && s >= 0. && s <= 1.)
		{
			d = (rp11 + r1 * t) - (rp21 + r2 * s);
			min_squared_distance = d * d;
		}
	}

	// However, this is not all. We should also check the bounds of the square (3):
	// 1. min(f(t, 0)), where t lies in [0, 1]
	// 2. min(f(0, s)), where s lies in [0, 1]
	// 3. min(f(t, 1)), where t lies in [0, 1]
	// 4. min(f(1, s)), where s lies in [0, 1]

	// As the functions above become simple quadratic functions with one variable argument,
	// we can find the desired values of t and s by setting the derivative of the function equal to 0
	// After finding vales of t and s, we will do one of the following step based on the result:
	// 1. If the result t or the result s lie in [0, 1], we will use them to find the next candidate distance
	// 2. If the result t or the result s do not lie in [0, 1], we will use the closest values to them, 
	//	  that belong to the square (3), which can be either 0 or 1

	double t1 = std::clamp(d1 * r1 / A, 0., 1.);
	double t2 = std::clamp(d2 * r1 / A, 0., 1.);
	double s1 = std::clamp(d1 * r2 / E, 0., 1.);
	double s2 = std::clamp(d2 * r2 / E, 0., 1.);

	// And finally, place the result values of t and s in (2) and find the minimum of all candidate distances:

	// For f(t, 0)
	d = (rp11 + r1 * t1) - (rp21 + r2 * 0.);
	min_squared_distance = std::min(min_squared_distance, d * d);

	// For f(t, 1)
	d = (rp11 + r1 * t2) - (rp21 + r2 * 1.);
	min_squared_distance = std::min(min_squared_distance, d * d);

	// For f(0, s)
	d = (rp11 + r1 * 0.) - (rp21 + r2 * s1);
	min_squared_distance = std::min(min_squared_distance, d * d);

	// For f(1, s)
	d = (rp11 + r1 * 1.) - (rp21 + r2 * s2);
	min_squared_distance = std::min(min_squared_distance, d * d);

	return min_squared_distance;
}
