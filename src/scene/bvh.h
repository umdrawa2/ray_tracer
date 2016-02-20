#pragma once
#ifndef BVH_H
#define BVH_H

#include <list>
#include "scene.h"

using namespace std;

class BVH
{

private:
	void newNode(Geometry* obj);
	bool isEmpty();

public:
	BVH();
	void buildBVH(std::vector<Geometry*>);
	list<Geometry*>* intersect(const ray& r, isect& i );

	//dimensions of the bounding volume
	BoundingBox* bb;
	//nodes to travers the volumes
	BVH* parent;
	BVH* left;
	BVH* right;
	//objects in the volume
	list<Geometry*> b_objects;

};

#endif