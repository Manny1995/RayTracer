//
//  main.cpp
//  Homework3
//
//  Created by Immanuel Amirtharaj on 11/21/15.
//  Copyright © 2015 Immanuel Amirtharaj. All rights reserved.
//

// In this lab assignment we use ray tracing to render a few spheres on top of a textured surface.


#include <vector>
#include <cmath>

#include <stdlib.h>
#include <stdio.h>

#include "Vect.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Source.h"
#include "Light.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"

#ifdef _WIN32
#include <gl\glut.h>
#
#elif __APPLE__
#include <GLUT/glut.h>

#endif


#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

using namespace std;

// a struct which manages the rgb color of each pixel
struct RGBType {
	double r;
	double g;
	double b;
};

// Array of pixels which define the viewing window
float myPixels[SCREEN_WIDTH][SCREEN_HEIGHT][3];

// Array of RGB structs which define the colors of the viewing window
RGBType *pixels;


// This function takes in a list of intersections and returns the intersection which is closest to the viewer
int getIndexOfClosestObject(vector<double> intersectionList) {
	// return the index of the winning intersection
	int minIndex;
	
    // no intersections in the list.  This means that there are no intersections in this pixel
    if (intersectionList.size() == 0)
    {
		return -1;
	}
    
    // 1 intersection in the list, so we check if it is within the viewing frame.  If so, then return
    // the index
	else if (intersectionList.size() == 1)
    {
		if (intersectionList.at(0) > 0) {
			return 0;
		}
		else {
			return -1;
		}
	}
    
    // More than one intersection.  In this case, we find the index for the closest object
	else {
        
        // The maxmimum t value
		double max = 0;
        
        // Iterate through the intersectino list and compare and change the maximum value
		for (int i = 0; i < intersectionList.size(); i++)
        {
			if (max < intersectionList[i])
            {
				max = intersectionList[i];
			}
		}
		
		// then starting from the maximum value find the minimum positive t value that is greater
        // than 0
		if (max > 0) {
			// we only want positive intersections
			for (int index = 0; index < intersectionList.size(); index++)
            {
				if (intersectionList[index] > 0 && intersectionList[index] <= max)
                {
					max = intersectionList[index];
					minIndex = index;
				}
			}
            
			return minIndex;
		}
        
        // Did not find an intersection so report that it was not found
		else
        {
            return -1;
		}
	}
}

// This function uses an intersection point, ray direction, closest index, and light source to calculate
// the color of the pixel.  This is the mian tracing function
Color getColorAt(Vector intersection, Vector rayDirection, vector<Object*> shapeList, int closestIndex, Light lightSource, double accuracy, double ambientlight) {
	
	Color closestColor = shapeList[closestIndex]->getColor();
	Vector normal = shapeList.at(closestIndex)->getNormalAt(intersection);
    
    // If the first object's special attribute is set to 2 we know it is a plane)
	if (closestColor.special == 2) {
        
            closestColor.red = 0.5;
            closestColor.green = 0.5;
            closestColor.blue = 0.5;

	}
	
	Color pixelColor = closestColor.colorScalar(ambientlight);
	
    // If the special coefficient is between 0 and 1, this is a reflective surface.  This means we
    // have to calculate the reflection for this part
	if (closestColor.special > 0 && closestColor.special <= 1)
    {
        
		// Vector arithmetic to calculate the reflection ray
		double dot1 = normal.dotProduct(rayDirection.negative());
		Vector scalar1 = normal.vectMult(dot1);
		Vector add1 = scalar1.vectAdd(rayDirection);
		Vector scalar2 = add1.vectMult(2);
		Vector add2 = rayDirection.negative().vectAdd(scalar2);
		Vector reflectionDirection = add2.normalize();
		
		Ray reflectionRay = Ray(intersection, reflectionDirection);
		
		// Create a vector of intersections and then iterate through shapes and save the intersections
		vector<double> reflection_intersections;
		
		for (int rIndex = 0; rIndex < shapeList.size(); rIndex++)
        {
			reflection_intersections.push_back(shapeList[rIndex]->findIntersection(reflectionRay));
		}
		
        // Gets the closest intersection of the reflected ray and the surface
		int closestIntersection = getIndexOfClosestObject(reflection_intersections);
		
        // if closestIntersection != -1, there is an intersection.
		if (closestIntersection != -1) {
            
			if (reflection_intersections[closestIntersection] > accuracy)
            {
				
				Vector reflectionIntersection = intersection.vectAdd(reflectionDirection.vectMult(reflection_intersections[closestIntersection]));
				
                //recursively getting color
				Color reflectionColor = getColorAt(reflectionIntersection, reflectionDirection, shapeList, closestIntersection, lightSource, accuracy, ambientlight);
				
				pixelColor = pixelColor.colorAdd(reflectionColor.colorScalar(closestColor.special));
			}
		}
	}
	

    Vector light_direction = lightSource.getLightPosition().vectAdd(intersection.negative()).normalize();
    
    // This cosine angle is used for diffuse shading
    float cosine_angle = normal.dotProduct(light_direction);
    
    if (cosine_angle > 0) {
        // test for shadows
        bool shadowed = false;
        
        // Create a new Vector
        Vector distance_to_light = lightSource.getLightPosition().vectAdd(intersection.negative()).normalize();
        float distance_to_light_magnitude = distance_to_light.magnitude();
        
        Ray shadowRay (intersection, lightSource.getLightPosition().vectAdd(intersection.negative()).normalize());
        
        vector<double> secondary_intersections;
        
        for (int object_index = 0; object_index < shapeList.size() && shadowed == false; object_index++) {
            secondary_intersections.push_back(shapeList.at(object_index)->findIntersection(shadowRay));
        }
        
        for (int c = 0; c < secondary_intersections.size(); c++)
        {
            if (secondary_intersections[c] > accuracy) {
                if (secondary_intersections.at(c) <= distance_to_light_magnitude) {
                    shadowed = true;
                }
            }
            break;
        }
        
        if (shadowed == false)
        {
            pixelColor = pixelColor.colorAdd(closestColor.colorMultiply(lightSource.getLightColor()).colorScalar(cosine_angle));
            
            if (closestColor.special > 0 && closestColor.special <= 1) {
                // special [0-1]
                double dot1 = normal.dotProduct(rayDirection.negative());
                Vector scalar1 = normal.vectMult(dot1);
                Vector add1 = scalar1.vectAdd(rayDirection);
                Vector scalar2 = add1.vectMult(2);
                Vector add2 = rayDirection.negative().vectAdd(scalar2);
                Vector reflectionDirection = add2.normalize();
                
                double specular = reflectionDirection.dotProduct(light_direction);
                if (specular > 0) {
                    specular = pow(specular, 10);
                    pixelColor = pixelColor.colorAdd(lightSource.getLightColor().colorScalar(specular*closestColor.special));
                }
            }
            
        }
        
    }

    return pixelColor;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawPixels(SCREEN_WIDTH, SCREEN_HEIGHT,  GL_RGB, GL_FLOAT, myPixels);
    glutSwapBuffers();
}

void initTracer()
{
    int width = SCREEN_WIDTH;
    int height = SCREEN_HEIGHT;
    int n = width*height;
    pixels = new RGBType[n];
    
    int aadepth = 1;
    double aspectratio = (double)width/(double)height;
    double ambientlight = 0.2;
    double accuracy = 0.00000001;
    
    Vector O (0,0,0);
    Vector X (1,0,0);
    Vector Y (0,1,0);
    Vector Z (0,0,1);
    

    
    
    Vector campos (3, 1.5, -4);
    
    Vector look_at (0, 0, 0);
    Vector diff_btw (campos.x - look_at.x, campos.y - look_at.y, campos.z - look_at.z);
    
    Vector camdir = diff_btw.negative().normalize();
    Vector camright = Y.crossProduct(camdir).normalize();
    Vector camdown = camright.crossProduct(camdir);
    Camera scene_cam (campos, camdir, camright, camdown);
    

    Color tile_floor (1, 1, 1, 2);
    Color gray (0.5, 0.5, 0.5, 0);
    Color black (0.0, 0.0, 0.0, 0);
    
    Light light (Vector(7, 10, -8), Color(1.0, 1.0, 1.0, 0));

    // The container which holds all the objects in the scene
    vector<Object*> shapesList;

    // Initialize 3 spheres and add them to the vector of objects
    Sphere sphere1 (Vector(0, 0.2, 0.5), 1, Color(0.5, 0.5, 1.0, 0));
    Sphere sphere2 (Vector(1.7, 1.5, -0.5), 0.5, Color(0.5, 1.0, 1.0, 0.3));
    Sphere sphere3 (Vector(-3, 0.25, 0), 1, Color(1.0, 0.5, 0.5, 0.5));
    Sphere sphere4 (Vector(2.8, 0.5, -0.5), 1, Color(1.0, 1.0, 0.5, 0));


    Plane floor (Y, -1, tile_floor);
    
    // Add objects to the vector (dynamic cast to superclass)
    shapesList.push_back(dynamic_cast<Object*>(&sphere1));
    shapesList.push_back(dynamic_cast<Object*>(&sphere2));
    shapesList.push_back(dynamic_cast<Object*>(&sphere3));
    shapesList.push_back(dynamic_cast<Object*>(&sphere4));

    shapesList.push_back(dynamic_cast<Object*>(&floor));
    
    int thisone, aa_index;
    double xamnt, yamnt;
    double tempRed, tempGreen, tempBlue;
    
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            thisone = y*width + x;
            
            // start with a blank pixel
            double tempRed[aadepth*aadepth];
            double tempGreen[aadepth*aadepth];
            double tempBlue[aadepth*aadepth];
            
            for (int aax = 0; aax < aadepth; aax++) {
                for (int aay = 0; aay < aadepth; aay++) {
                    
                    aa_index = aay*aadepth + aax;
                    
                    // create the ray from the camera to this pixel
                    if (aadepth == 1) {
                        
                        // start with no anti-aliasing
                        if (width > height) {
                            // the image is wider than it is tall
                            xamnt = ((x+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
                            yamnt = ((height - y) + 0.5)/height;
                        }
                        else if (height > width) {
                            // the imager is taller than it is wide
                            xamnt = (x + 0.5)/ width;
                            yamnt = (((height - y) + 0.5)/height)/aspectratio - (((height - width)/(double)width)/2);
                        }
                        else {
                            // the image is square
                            xamnt = (x + 0.5)/width;
                            yamnt = ((height - y) + 0.5)/height;
                        }
                    }

                    Vector cam_ray_origin = scene_cam.position;
                    Vector cam_ray_direction = camdir.vectAdd(camright.vectMult(xamnt - 0.5).vectAdd(camdown.vectMult(yamnt - 0.5))).normalize();
                    
                    Ray cam_ray (cam_ray_origin, cam_ray_direction);
                    
                    vector<double> intersections;
                    
                    for (int index = 0; index < shapesList.size(); index++) {
                        intersections.push_back(shapesList[index]->findIntersection(cam_ray));
                    }
                    
                    int index_of_winning_object = getIndexOfClosestObject(intersections);
                    
                    if (index_of_winning_object == -1) {
                        // set the backgroung black
                        tempRed[aa_index] = 0;
                        tempGreen[aa_index] = 0;
                        tempBlue[aa_index] = 0;
                    }
                    else{
                        // index coresponds to an object in our scene
                        if (intersections.at(index_of_winning_object) > accuracy) {
                            // determine the position and direction vectors at the point of intersection
                            
                            Vector intersection_position = cam_ray_origin.vectAdd(cam_ray_direction.vectMult(intersections.at(index_of_winning_object)));
                            Vector rayDirection = cam_ray_direction;
                            
                            Color intersection_color = getColorAt(intersection_position, rayDirection, shapesList, index_of_winning_object, light, accuracy, ambientlight);
                            
                            tempRed[aa_index] = intersection_color.red;
                            tempGreen[aa_index] = intersection_color.green;
                            tempBlue[aa_index] = intersection_color.blue;
                        }
                    }
                }
            }
            
            // average the pixel color
            double totalRed = 0;
            double totalGreen = 0;
            double totalBlue = 0;
            
            for (int iRed = 0; iRed < aadepth*aadepth; iRed++) {
                totalRed = totalRed + tempRed[iRed];
            }
            for (int iGreen = 0; iGreen < aadepth*aadepth; iGreen++) {
                totalGreen = totalGreen + tempGreen[iGreen];
            }
            for (int iBlue = 0; iBlue < aadepth*aadepth; iBlue++) {
                totalBlue = totalBlue + tempBlue[iBlue];
            }
            
            double avgRed = totalRed/(aadepth*aadepth);
            double avgGreen = totalGreen/(aadepth*aadepth);
            double avgBlue = totalBlue/(aadepth*aadepth);
            
            pixels[thisone].r = avgRed;
            pixels[thisone].g = avgGreen;
            pixels[thisone].b = avgBlue;
        }
    }
    
}


// This is the main function which first renders the image and then updates the pixel array.
// Then it initializes and creates a window to show the scene.
int main (int argc, char *argv[]) {
	
    initTracer();
    // Now that we have the array of pixels
    int count = 0;
    for (int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            myPixels[i][j][0] = pixels[count].r;
            myPixels[i][j][1] = pixels[count].g;
            myPixels[i][j][2] = pixels[count].b;
            
            count++;
        }
    }
    
    glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Raytracing Assignment");
    glutDisplayFunc(display);
    glutMainLoop();
	return 0;
}
