#ifndef _VECT_H
#define _VECT_H

#include "math.h"

class Vector {
	double x, y, z;
	
	public:
	
	Vector ();
	
	Vector (double, double, double);
	
	// method functions
	double getVectX() { return x; }
	double getVectY() { return y; }
	double getVectZ() { return z; }
	
	double magnitude () {
		return sqrt((x*x) + (y*y) + (z*z));
	}
	
	Vector normalize () {
		double magnitude = sqrt((x*x) + (y*y) + (z*z));
		return Vector (x/magnitude, y/magnitude, z/magnitude);
	}
	
	Vector negative () {
		return Vector (-x, -y, -z);
	}
	
	double dotProduct(Vector v) {
		return x*v.getVectX() + y*v.getVectY() + z*v.getVectZ();
	}
	
	Vector crossProduct(Vector v) {
		return Vector (y*v.getVectZ() - z*v.getVectY(), z*v.getVectX() - x*v.getVectZ(), x*v.getVectY() - y*v.getVectX());
	}
	
	Vector vectAdd (Vector v) {
		return Vector (x + v.getVectX(), y + v.getVectY(), z + v.getVectZ());
	}

	Vector vectMult (double scalar) {
		return Vector (x*scalar, y*scalar, z*scalar);
	}
};

Vector::Vector () {
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector (double i, double j, double k) {
	x = i;
	y = j;
	z = k;
}

#endif
