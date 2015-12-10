//
//  main.cpp
//  Homework3
//
//  Created by Immanuel Amirtharaj on 11/21/15.
//  Copyright © 2015 Immanuel Amirtharaj. All rights reserved.
//

// This has the Color class which has 4 parameters: The first 3 are the RGB values and the 4th value
// (special)

#ifndef _COLOR_H
#define _COLOR_H

class Color {
	
	public:
	
	Color ();
	
	Color (double, double, double, double);
    
    double red, green, blue, special;

	
	double brightness() {
		return(red + green + blue)/3;
	}
	
	Color colorScalar(double scalar) {
		return Color (red*scalar, green*scalar, blue*scalar, special);
	}
	
	Color colorAdd(Color color) {
		return Color (red + color.red, green + color.green, blue + color.blue, special);
	}
	
	Color colorMultiply(Color color) {
		return Color (red*color.red, green*color.green, blue*color.blue, special);
	}
	
//	Color colorAverage(Color color) {
//		return Color ((red + color.red)/2, (green + color.green)/2, (blue + color.blue)/2, special);
//	}
    
    
	// If needed this function clips the rgb of a color to 1
//	Color clip() {
//		double alllight = red + green + blue;
//		double excesslight = alllight - 3;
//		if (excesslight > 0) {
//			red = red + excesslight*(red/alllight);
//			green = green + excesslight*(green/alllight);
//			blue = blue + excesslight*(blue/alllight);
//		}
//        
//        
//		if (red > 1)
//        {
//            red = 1;
//        }
//        
//		if (green > 1)
//        {
//            green = 1;
//        }
//        
//		if (blue > 1)
//        {
//            blue = 1;
//        }
//        
//		if (red < 0)
//        {
//            red = 0;
//        }
//        
//		if (green < 0)
//        {
//            green = 0;
//        }
//        
//		if (blue < 0) {blue = 0;}
//		
//		return Color (red, green, blue, special);
//	}
};

// default initialization
Color::Color ()
{
	red = 0.5;
	green = 0.5;
	blue = 0.5;
}

// initialize color with rgb and special value
Color::Color (double r, double g, double b, double s)
{
	red = r;
	green = g;
	blue = b;
	special = s;
}

#endif
