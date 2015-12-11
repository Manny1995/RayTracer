//
//  main.cpp
//  Homework3
//
//  Created by Immanuel Amirtharaj on 11/21/15.
//  Copyright © 2015 Immanuel Amirtharaj. All rights reserved.
//

// This is the class where the light source is derived from

#ifndef _SOURCE_H
#define _SOURCE_H

class Source {
	public:
	
	Source()
    {
        
    }
	
	virtual Vector getLightPosition() {
        return Vector(0, 0, 0);
    }
    
	virtual Color getLightColor() {
        return Color(1, 1, 1, 0);
    }
	
};

#endif
