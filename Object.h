//
//  Object.h
//  Homework3
//
//  Created by Immanuel Amirtharaj on 11/21/15.
//  Copyright © 2015 Immanuel Amirtharaj. All rights reserved.
//

// This is the base class in which the sphere and plane is derived from.  Also has a find intersection
// color, and getNormal virtual member functions which are implemented in the subclasses

#ifndef _OBJECT_H
#define _OBJECT_H

#include "Ray.h"
#include "Vect.h"
#include "Color.h"


class Object {	
	public:
	
    // Default constructor
	Object ()
    {
        
    }
	
	// Returns the color
	virtual Color getColor ()
    {
        return Color (0.0, 0.0, 0.0, 0);
    }
	
    // Returns the normal vector at the point of the surface
	virtual Vector getNormalAt(Vector intersection_position)
    {
		return Vector (0, 0, 0);
	}
	
    // Returns the intersection parameter value if there is an intersection with the object and
    // the ray passed in
	virtual double findIntersection(Ray ray) {
		return 0;
	}
	
};



#endif
