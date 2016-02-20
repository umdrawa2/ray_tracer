#include <cmath>

#include "Sphere.h"

using namespace std;

const double HUGE_DOUBLE = 1e100;

bool Sphere::intersectLocal( const ray& r, isect& i ) const
{
    // YOUR CODE HERE:
    // Add sphere intersection code here.
    // it currently ignores all spheres and just return false.
	Vec3d p = r.getPosition();
    Vec3d d = r.getDirection();

	double t = -1, p_1, p_2, p_3, d_1, d_2, d_3, c, b, a;

	//all of the variables we'll need for intersection
	p_1 = p.getPointer()[0];
	p_2 = p.getPointer()[1];
	p_3 = p.getPointer()[2];
	d_1 = d.getPointer()[0];
	d_2 = d.getPointer()[1];
	d_3 = d.getPointer()[2];

	c = p_1 * p_1 + p_2 * p_2 + p_3 * p_3 - 1;
	a = d_1 * d_1 + d_2 * d_2 + d_3 * d_3;
	b = d_1 * p_1 * 2 + d_2 * p_2 * 2 + d_3 * p_3 * 2;

	double t1 = (-b + sqrt(b * b - 4.0 * a * c)) / (2 * a);
	double t2 = (-b - sqrt(b * b - 4.0 * a * c)) / (2 * a);

	if(t1 > 0) {
		if(t2 <= 0 || t2 > t1)
			t = t1;
	} 
	
	if(t2 > 0) {
		if(t1 <= 0 || t1 > t2)
			t = t2;
	} 

	if(t < RAY_EPSILON) 
		return false;

	i.setT(t);
	i.setObject(this);

	Vec3d n = p + t * d;
	n.normalize();
	i.setN(n);

	Vec3d intersect_point = r.at((float)i.t);
	i.setUVCoordinates(Vec2d(intersect_point[0], intersect_point[1]));

    return true;
}

