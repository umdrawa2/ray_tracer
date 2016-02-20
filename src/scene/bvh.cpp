#include "bvh.h"
#include "scene.h"
#include "ray.h"

using namespace std;

bool BVH::isEmpty()
{
	if(bb->max == Vec3d(-99999, -99999, -99999))
		return true;
	else
		return false;
}

void BVH::newNode(Geometry* obj)
{
	BVH node;
	BoundingBox b = obj->getBoundingBox();
	const int numDims = 3;

	bool leftSide = false;

	if(b.min[0] > (bb->max[0] - bb->min[0]) / 2)
		leftSide = true;

	int i;
	//update max value
	for( i = 0; i < numDims; i++) {
		if(b.max[i] > bb->max[i])
			bb->max[i] = b.max[i];
	}

	//update min value
	for( i = 0; i < numDims; i++) {
		if(b.min[i] < bb->min[i] && bb->min[i] != -99999)
			bb->min[i] = b.min[i];
	}


	b_objects.push_back(obj);

	/*if(b_objects.size() > 1) {
		if(leftSide) {
			if(left != NULL)
				left->newNode(obj);
			else {
				left = new BVH();
				vector<Geometry*> l;
				l.push_back(obj);
				left->buildBVH(l);
			}
		} else {
			if(right != NULL)
				right->newNode(obj);
			else {
				right = new BVH();
				vector<Geometry*> l;
				l.push_back(obj);
				right->buildBVH(l);
			}
		}
	}*/
}

list<Geometry*>* BVH::intersect(const ray& r, isect& i )
{
	typedef vector<Geometry*>::const_iterator iter;

	bool have_one = false;
	int j = 0;
	double tmin = -1.0;
	double tmax = 1.0;
	bool leftEmp = false;
	bool iTest = false;

	if(bb->intersect(r, tmin, tmax))
	{
		if(left!= NULL && !left->isEmpty() ) 
			return left->intersect(r, i);
		else
			leftEmp = true;

		if(right != NULL && !right->isEmpty())
			return right->intersect(r, i);
		else if(leftEmp)
			return &b_objects;
		else 
			return NULL;
	} else 
		return NULL;
}

void BVH::buildBVH(std::vector<Geometry*> objects)
{
	typedef vector<Geometry*>::const_iterator iter;

	for(  iter j = objects.begin(); j != objects.end(); ++j ) {
		newNode(*j);
	}
}

BVH::BVH()
{
	bb = new BoundingBox();
	bb->max = Vec3d(-99999, -99999, -99999);
	bb->min = Vec3d(99999, 99999, 99999);

	parent = NULL;
	left = NULL;
	right = NULL;

	b_objects = list<Geometry*>();
}