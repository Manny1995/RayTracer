//
//  Plane.h
//  Homework3
//
//  Created by Immanuel Amirtharaj on 11/21/15.
//  Copyright © 2015 Immanuel Amirtharaj. All rights reserved.
//

#ifndef _Plane_H
#define _Plane_H

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"



// This is the class structure for a plane.  A plane can be represented by a vector (center),
// a distance which signifies the points in the range of the plane, and a color which returns
// the color of the plane
class Plane : public Object {

	
	public:
    
    // The normal to the vector
    Vector normal;
    // The distance
    double distance;
    // The color of the plane
    Color color;
	
    
    // Default Constructor
	Plane ()
    {
        normal = Vector(1,0,0);
        distance = 0;
        color = Color(0.5,0.5,0.5, 0);
    }
	
    // Initalize with vector, a distance (range), and a color
    Plane (Vector _normal, double _distance, Color _color)
    {
        normal = _normal;
        distance = _distance;
        color = _color;
    }
    
    
    // Returns the normal vector of the plane
	Vector getPlaneNormal () {
        return normal;
    }
    
    // Returns the distance of the plane
	double getPlaneDistance () {
        return distance;
    }
    
    // Returns the color of the plane surface
	virtual Color getColor () {
        return color;
    }
	
    
    // Takes in a point as a parameter and returns the normal vector.  Because this object is a plane,
    // the normal vector will always be the same so it just returns the normal member vector of the
    // plane
	virtual Vector getNormalAt(Vector point) {
		return normal;
	}
	
    
    // The function which takes in a ray as a parameter and returns the parameter value if there is one
	virtual double findIntersection(Ray ray) {
        
        //
        Vector direction = ray.direction;
		
		double a = direction.dotProduct(normal);
		
        // If the dot product is 0, this means that the ray passed in is parallel to the plane which
        // means that there is no intersection
		if (a == 0) {
			return -1;
		}
        
        // There is an intersection so we should return the parameter variable at where it occurs
		else {
			double b = normal.dotProduct(ray.origin.vectAdd(normal.vectMult(distance).negative()));
			return -1*b/a;
		}
	}
	
};


#endif
