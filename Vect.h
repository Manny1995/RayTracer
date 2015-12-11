//
//  Vector.h
//  Homework3
//
//  Created by Immanuel Amirtharaj on 11/21/15.
//  Copyright © 2015 Immanuel Amirtharaj. All rights reserved.
//

// A Vector is the projection of a point in a 3D space.  It is defined as x, y, and z coordinates.
// This class also has member functions which carry out vector operations such as addition, multiplication,
// dot product, and cross product.

#ifndef _VECTOR_H
#define _VECTOR_H

#include "math.h"

class Vector {
	
	public:
	
    double x, y, z;
    
    // Default constructor
	Vector ()
    {
        x = 0;
        y = 0;
        z = 0;
    }
	
    // Initializes the vector with a set of points
    Vector (double i, double j, double k) {
        x = i;
        y = j;
        z = k;
    }
    
    // Returns the magnitude of the vector
	double magnitude ()
    {
		return sqrt((x*x) + (y*y) + (z*z));
	}
	
    // Normalizes the vector (sum of the components = 1)
	Vector normalize ()
    {
		double magnitude = sqrt((x*x) + (y*y) + (z*z));
		return Vector (x/magnitude, y/magnitude, z/magnitude);
	}
	
    // Returns the negative of the vector
	Vector negative ()
    {
		return Vector (-x, -y, -z);
	}
	
    // Takes in a vector as a parameter and returns the dot product
	double dotProduct(Vector v)
    {
		return x*v.x + y*v.y + z*v.z;
	}
    
    // Takes in a vector as a parameter and returns the cross product
	Vector crossProduct(Vector v)
    {
		return Vector (y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
	}
	
    // Takes in a vector as a parameter and returns the sum
	Vector vectAdd (Vector v)
    {
		return Vector (x + v.x, y + v.y, z + v.z);
	}

    // Takes in a scalar number as a parameter and returns the scaled vector
	Vector vectMult (double scalar)
    {
		return Vector (x*scalar, y*scalar, z*scalar);
	}
};

#endif
