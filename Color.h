//
//  Color.h
//  Homework3
//
//  Created by Immanuel Amirtharaj on 11/21/15.
//  Copyright © 2015 Immanuel Amirtharaj. All rights reserved.
//

// This has the Color class which has 4 parameters: The first 3 are the RGB values and the 4th value
// (special) is an alpha value which determines transparancy

#ifndef _COLOR_H
#define _COLOR_H

class Color {
	
	public:
	
	Color ()
    {
        red = 0.5;
        green = 0.5;
        blue = 0.5;
    }
	
	Color (double r, double g, double b, double s)
    {
        red = r;
        green = g;
        blue = b;
        special = s;
    }
    
    double red, green, blue, special;

	
    // Returns the average of all rgb values
	double brightness() {
		return(red + green + blue)/3;
	}
    
    // Takes in a color object as a parameter and adds it to the member color to return the
    // added color
    Color colorAdd(Color color) {
        return Color (red + color.red, green + color.green, blue + color.blue, special);
    }
	
    // Takes in a scalar value as a parameter and multiplies it by the rgb color to return
    // the scaled color
	Color colorScalar(double scalar)
    {
		return Color (red*scalar, green*scalar, blue*scalar, special);
	}
	
    // Takes in a color object as a parameter and multiplies each rgb value to the current object's
    // rgb value and returns the multiplied color
	Color colorMultiply(Color color) {
		return Color (red*color.red, green*color.green, blue*color.blue, special);
	}

};



#endif
