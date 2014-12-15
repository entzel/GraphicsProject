//#include "CSCIx229.h"
static void sun(){


	//light stuff
	extern float emission;  // Emission intensity (%)
	extern float ambient;  // Ambient intensity (%)
	extern float diffuse;  // Diffuse intensity (%)
	extern float specular;  // Specular intensity (%)
	extern float shinyvec[1];    // Shininess (value)
	extern float ylight;  // Elevation of light
	extern float white2[]; //object emmision colors

	//Translate intensity to color vectors
	 float Ambient[]   = {0.01f*ambient ,0.01f*ambient ,0.01f*ambient ,1.0};
     float Diffuse[]   = {0.01f*diffuse ,0.01f*diffuse ,0.01f*diffuse ,1.0};
     float Specular[]  = {0.01f*specular,0.01f*specular,0.01f*specular,1.0};
     float Emission[]  = {0.0,0.0,0.01f*emission,1.0};
	
	//Light position
	float Position[]  = {0, ylight,0, 1.0};
    //Draw it
	glColor3f(1,1,.8);
    //sphere(Position[0],Position[1],Position[2], 3.5);
	glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT,GL_SPECULAR, white2);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
	glEnable(GL_NORMALIZE);
	//Enable lighting
    glEnable(GL_LIGHTING);
	//glColor sets ambient and diffuse color materials
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //Enable light 0
    glEnable(GL_LIGHT0);
    //Set ambient, diffuse, specular components and position of light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);	 
 }