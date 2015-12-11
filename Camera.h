//
//  Color.h
//  Homework3
//
//  Created by Immanuel Amirtharaj on 11/21/15.
//  Copyright © 2015 Immanuel Amirtharaj. All rights reserved.
//

// The Camera object simulates the user's viewing coordinates.  It is defined by the camera position, the
// camera's direction (the direction the viewer is looking at), the right position which sets the horizontal
// offset and the down position which sets the vertical offset


#ifndef _Camera_H
#define _Camera_H

#include "Vect.h"

class Camera {
	
	public:
	
    Vector position, direction, right, down;

    
    // Default constructor
	Camera ()
    {
        position = Vector(0,0,0);
        direction = Vector(0,0,1);
        right = Vector(0,0,0);
        down = Vector(0,0,0);
    }
	
    // Takes in parameters to initialize the camera with a position, direction, right, and down
	Camera (Vector p, Vector d, Vector r, Vector _d)
    {
        position = p;
        direction = d;
        right = r;
        down = _d;
    }
	
};



#endif
