//
//  Light.h
//  Homework3
//
//  Created by Immanuel Amirtharaj on 11/21/15.
//  Copyright © 2015 Immanuel Amirtharaj. All rights reserved.
//

// A light object is defined by a vector as its position and its color

#ifndef _Light_H
#define _Light_H

#include "Source.h"
#include "Vect.h"
#include "Color.h"

class Light : public Source {
	
	public:
	
    Vector position;
    Color color;
    
    // Default constructor
	Light ()
    {
        position = Vector(0,0,0);
        color = Color(1,1,1, 0);
    }
	
    // Initializes the object with its position and light color
	Light (Vector p, Color c)
    {
        position = p;
        color = c;
    }
	    
    
    // Returns the light position.  Necessary because only way to access the variables since this
    // is inheriting
	virtual Vector getLightPosition ()
    {
        return position;
    }
    
    // Returns the light color.  Necessary because only way to access the variables since this
    // is inheriting
	virtual Color getLightColor ()
    {
        return color;
    }
	
};



#endif
