//
//  Sphere.h
//  Homework3
//
//  Created by Immanuel Amirtharaj on 11/21/15.
//  Copyright © 2015 Immanuel Amirtharaj. All rights reserved.
//

// A sphere is defined to be an object with a center and a radius.  It will have a color as well as
// functions which manage intersections with rays

#ifndef _SPHERE_H
#define _SPHERE_H

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"

class Sphere : public Object {
	Vector center;
	double radius;
	Color color;
	
	public:
	
	Sphere ()
    {
        center = Vector(0,0,0);
        radius = 1.0;
        color = Color(0.5,0.5,0.5, 0);
    }
	
	Sphere (Vector _center, double _radius, Color _color)
    {
        center = _center;
        radius = _radius;
        color = _color;
    }
	
	// method functions
	Vector getSphereCenter () { return center; }
	double getSphereRadius () { return radius; }
	virtual Color getColor () { return color; }
	
	virtual Vector getNormalAt(Vector point) {
		// normal always points away from the center of a sphere
		Vector normal_Vect = point.vectAdd(center.negative()).normalize();
		return normal_Vect;
	}
	
    // This function takes in a ray as a parameter and returns an intersection if there is one
	virtual double findIntersection(Ray ray) {
        
        // origin vector
		Vector r0 = ray.origin;
		double r0x = r0.x;
		double r0y = r0.y;
		double r0z = r0.z;
		
        // direction of the ray
		Vector rd = ray.direction;
		double rdx = rd.x;
		double rdy = rd.y;
		double rdz = rd.z;
		
        // center of the sphere
		Vector cc = center;
		double cx = cc.x;
		double cy = cc.y;
        double cz = cc.z;
		
        // Values which are used to calculate the discriminant
		double a = 1; // The ray direction is already normalized
		double b = (2*(r0x - cx)*rdx) + (2*(r0y - cy)*rdy) + (2*(r0z - cz)*rdz);
		double c = pow(r0x - cx, 2) + pow(r0y - cy, 2) + pow(r0z - cz, 2) - (radius*radius);
		
		double discriminant = b*b - 4*c;
		
        // Means that the ray intersects the sphere.  In this case we calculate the smallest intersection
		if (discriminant > 0) {
			
			// the first root
			double root_1 = ((-1*b - sqrt(discriminant))/2) - 0.000001;
			
			if (root_1 > 0) {
				// the first root is the smallest positive root
				return root_1;
			}
			else {
				// the second root is the smallest positive root
				double root_2 = ((sqrt(discriminant) - b)/2) - 0.000001;
				return root_2;
			}
		}
        // No intersection between ray and sphere
		else {
			return -1;
		}
	}
};

#endif
