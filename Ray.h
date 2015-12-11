//
//  Ray.h
//  Homework3
//
//  Created by Immanuel Amirtharaj on 11/21/15.
//  Copyright © 2015 Immanuel Amirtharaj. All rights reserved.
//

// A Ray is defined as an object with two vectors: one which specifies the origin and the other which
// specifies the direction it is facing

#ifndef _RAY_H
#define _RAY_H

#include "Vect.h"

class Ray {
	
	public:
	
    // The origin and direction member variables
    Vector origin, direction;

    // Default constructor
	Ray ()
    {
        origin = Vector(0,0,0);
        direction = Vector(1,0,0);
    }
	
    // This constructor takes in parameters to initialize the origin and a direction of the vector
	Ray (Vector o, Vector d)
    {
        origin = o;
        direction = d;
    }

};

#endif
