#ifndef _RAY_H
#define _RAY_H

#include "Vect.h"

class Ray {
	
	public:
	
    Vector origin, direction;

	Ray ();
	
	Ray (Vector, Vector);
	
	// method functions
	Vector getRayOrigin () { return origin; }
	Vector getRayDirection () { return direction; }
	
};

Ray::Ray () {
	origin = Vector(0,0,0);
	direction = Vector(1,0,0);
}

Ray::Ray (Vector o, Vector d) {
	origin = o;
	direction = d;
}

#endif
