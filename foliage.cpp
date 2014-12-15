#include "CSCIx229.h"
//#include "myShapes.c"


/*Draw a tree */ 
void tree(double x, double y, double z, double r, double th, unsigned int tex){

	glBindTexture(GL_TEXTURE_2D, tex);

	//Adjust tree, rotate, translate
	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(r,r,r);
	
	//Draw tree poofs	
  glDisable(GL_TEXTURE_2D); //disable for trees and things
  		
	glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);
	sphere(0, 0, 0, .19);
	sphere(0,  .6, 0, .19);
	sphere(.6, 0, 0, .19);
	sphere(-.6, 0, 0, .19);
	sphere(0, 0, .5, .16);
	sphere(0, 0, -.5, .16);
	
	sphere(.1, -.2, .1, .04);
	sphere(-.1, -.2, -.1, .04);
	//Draw tree trunk
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	cube(0, 0 , 0,   .3, -y, .3,      1,    .9, .4, .1, .9, .4, .1, 1, 0.5, 0.4, .8, .4, .5, tex);
    //Undo transofrmations
	glDisable(GL_POLYGON_OFFSET_FILL);
    glPopMatrix();
}

