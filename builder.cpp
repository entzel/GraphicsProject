/*
S- Zoom in
s- Zoom out
l/L -toggle sun
+/- increase/decreas field of view angle
e/E decrease/increase the sun's emission intensity
</> move light
 l          Toggles lighting
 */
/*TO DO

get color when it is clicked and apply it to customizable piece switch is on


Skybox!?
create trees?
fog?

*/

#include <stdbool.h>
#include "CSCIx229.h"
#include "sunFixture.h"
#include <iostream>
#include <new>
#include <cstring>
#include <list>
//#include "HouseClass.h"

using namespace std;


//----------Global variables--------
int ptime;
double asp = 1.0;	//  Aspsect ratio
int th=0;         //  Azimuth of view angle`
int ph=10;         //  Elevation of view angle
int fov=45;       //  Field of view (for perspective)
double dim = 40.0;
int zh = 0;
int SCREEN_WIDTH = 700;
int SCREEN_HEIGHT = 700;
int mousex = 0;
int mousey =0;
//House houses [10]; //Total number of houses that can be in scene
//House tempHouse;

//Textures	
unsigned int winTexture[6];
unsigned int doorTexture[5];
unsigned int Htexture[16];
unsigned int texture[14];

//Light stuff (see sunFixture.h)
int light = 20;
float emission  =   50;  // Emission intensity (%)
float ambient   =  90;  // Ambient intensity (%)
float diffuse   = 100;  // Diffuse intensity (%)
float specular  =   5;  // Specular intensity (%)
double shininess =   0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
float ylight  =   20;  // Elevation of light
float white2[] = {1,1,1,1}; //object emmision colors
float black2[] = {0,0,0,1};

//----------Button stuff----------------------------------------------------
int button_pressed = 0; //Initially no buttons are pressed
int enter = 0;
//---House Button---
 //House button position
float button_left = -0.99; 
float button_right = -0.7;
float button_bottom = -0.84;
float button_top = -0.61;
//Texture selector button stuff
int hoverindex = 2;
float selector_left = -0.69; 
float selector_right = -0.39;
float selector_bottom = -0.85;
float selector_top = -0.61;
int roofChange = 0;
int doorChange = 0;
int paintChange = 0;
int windowChange = 0;

int leftclicked = 0;
int rightclicked = 0;
float la_button_left = -.69; 
float la_button_right = -.5475;
float la_button_bottom = -0.95;
float la_button_top = -0.84;

float ra_button_left = -.545; 
float ra_button_right = -.39;
float ra_button_bottom = -0.95;
float ra_button_top = -0.84;

float color_button_left = 0.39; 
float color_button_right = 1.0;
float color_button_bottom = -1;
float color_button_top = -0.61;

int upclicked = 0;
int downclicked = 0;
float up_button_left = .24; 
float up_button_right = .34;
float up_button_bottom = -0.72;
float up_button_top = -0.62;

float down_button_left = .24; 
float down_button_right = .34;
float down_button_bottom = -0.84;
float down_button_top = -.74;

float save_button_left = -.37; 
float save_button_right = -.09;
float save_button_bottom = -0.98;
float save_button_top = -0.87;

float done_button_left = -.38; 
float done_button_right = -.08;
float done_button_bottom = -0.84;
float done_button_top = -0.71;

int edithover = 0;


//---House Pop up feature stuff-----(When house button is pressed)
int housePopup = 0; //The house pop up is initially off until button is pressed
//Initial parameters of popped up house
double PHx =0; double PHy = 0; double PHz= 0; double PHth = 0; 
double PHwidth = 5; double PHheight = 5; double PHdepth = 5; double PHroofheight= 1.9;
float PHred =.70; float PHgreen= .2; float PHblue=0; 
int PHhousetex = 11;  int PHrooftex= 4; int PHwindowtex = 2;
double PHredDoor = 1; double PHgreenDoor = 0;  double PHblueDoor = 0; int PHdoortex = 0;
double PHredW = .6; double PHgreenW = .6;  double PHblueW = 0;
double PHredR = .8; double PHgreenR = .2;  double PHblueR = 0;


//-----------HOUSE CLASS-------------------------------------------------

float white[] = {1,1,1,1}; //object emmision colors
float black[] = {0,0,0,1};
float shinyvec2[1];    // Shininess (value)

 void roof(double x, double y, double z, double th, double width, double height, double depth, unsigned int rooftex, double red, double green, double blue)
{	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, rooftex);
	//Adjust the roof
	glScaled(width,1,depth);
	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glColor3f(red, green, blue);
	if(height <= .03){
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex3f(-1,0,-1);
		glTexCoord2f(1,0); glVertex3f(+1,0,-1);
		glTexCoord2f(1,1);glVertex3f(+1,0,+1);
		glTexCoord2f(0,1);glVertex3f(-1,0,+1); 
		glNormal3f(0, -1, 0);
		glEnd();
		}
	else{

	glScaled(1.2, height, 1.2);	

	//front
	glBegin(GL_POLYGON);
	glNormal3d(0, +1, +1); 
	glTexCoord2f(-1,0); glVertex3f(-1, 0, +1);
	glTexCoord2f(0, +1); glVertex3f(0, +1, 0);
	glTexCoord2f(+1, 0); glVertex3f(+1, 0, +1);
	glEnd();
	
	//right
	glBegin(GL_POLYGON);
	glNormal3d(+1, +1, 0); 
	glTexCoord2f(-1,0); glVertex3f(+1, 0, -1);
	glTexCoord2f(0,+1); glVertex3f(0, +1, 0);
	glTexCoord2f(+1,0); glVertex3f(+1, 0, +1);
	glEnd();
	
	//back
	glBegin(GL_POLYGON);
	glNormal3d(0, +1, -1); 
	glTexCoord2f(+1,0);glVertex3f(+1, 0, -1);
	glTexCoord2f(0, +1); glVertex3f(0, +1, 0);
	glTexCoord2f(-1,0); glVertex3f(-1, 0, -1);
	glEnd();
	
	//left
	glBegin(GL_POLYGON);
	glNormal3d(-1., +1, 0); 
	glTexCoord2f(-1,0); glVertex3f(-1, 0, -1);
	glTexCoord2f(0, +1); glVertex3f(0, +1, 0);
	glTexCoord2f(+1,0); glVertex3f(-1, 0, +1);
	glEnd();
	}
	
	glPopMatrix();
	
}

class House{

	public:
		House();
		
		House(double inx, double iny, double inz, double inth, double inwidth,  double inheight, double indepth, double inroofheight,
		double inred, double ingreen, double inblue, double inredDoor, double ingreenDoor, double inblueDoor,
		double Rinred, double Ringreen, double Rinblue, double Winred, double Wingreen, double Winblue, 
		unsigned int inhousetex, unsigned int inrooftex, unsigned int inwindowtex,unsigned int indoortex);
		
		double x; 
		double y;
		double z;
		double th;
		double width;
		double height;
		double depth; 
		double roofheight;
		unsigned int housetex;
		unsigned int rooftex;
		unsigned int windowtex;
		unsigned int doortex;
		double red; 
		double green; 
		double blue; 
		double redDoor; double greenDoor; double blueDoor; 
		double Rred; double Rgreen; double Rblue;
		double Wred; double Wgreen; double Wblue;
		//double backr; double backg; double backb; 
        //double rightr; double rightg; double rightb; double leftr; double leftg; double leftb;
	    void drawHouse( void );
};

House::House()
{
	/*x = 0;
	y= 0;
	z= 0;
	th = 0; 
	width= 0;
	height= 0;
	depth = 0; 
	roofheight = 0; 
	red = 0; 
	green = 0; 
	blue = 0;
	housetex = 0; 
	rooftex = 0;
	windowtex = 0;
	redDoor = 0; 
	greenDoor = 0;
	blueDoor = 0;
	doortex = 0;
	*/
	x =0;  y = 0;  z= 0; th = 0; 
	width = 5; height = 5;  depth = 5; roofheight= 1.9;
	red =.70; green= .2;  blue=1; // housetex = 5;  rooftex= 3; windowtex = 0;
	redDoor = 1;  greenDoor = 0;   blueDoor = 0;  //doortex = 1;
	Wred = .6; Wgreen = .6; Wblue = 0;
	Rred = .8;  Rgreen = .2;  Rblue = 0;
	housetex = Htexture[11]; rooftex= Htexture[4]; 
	windowtex = winTexture[2]; doortex = doorTexture[0];
}

House::House(double inx, double iny, double inz, double inth, double inwidth,  double inheight, double indepth, double inroofheight,
		double inred, double ingreen, double inblue, double inredDoor, double ingreenDoor, double inblueDoor,
		double Rinred, double Ringreen, double Rinblue, double Winred, double Wingreen, double Winblue, 
		unsigned int inhousetex, unsigned int inrooftex, unsigned int inwindowtex,unsigned int indoortex)
{
	x = inx; 
	y= iny;
	z= inz;
	th = inth; 
	width= inwidth;
	height= inheight;
	depth = indepth; 
	roofheight = inroofheight; 
	red = inred; 
	green = ingreen; 
	blue = inblue;
	housetex = inhousetex; 
	rooftex = inrooftex;
	windowtex = inwindowtex;
	redDoor = inredDoor; 
	greenDoor = ingreenDoor;
	blueDoor = inblueDoor;
	doortex = indoortex;
	Rred = Rinred;
	Rgreen = Ringreen;
	Rblue = Rinblue;
	Wred = Winred;
	Wgreen = Wingreen;
	Wblue = Winblue;

}

void House::drawHouse(void)
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec2);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(width,height,depth);
	
	//et specular color to white
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec2);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
	
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 1);
	cube(0,0, 0,  1, 1, 1, 1, red, green, blue, red, green, blue,  red, green, blue,  red, green, blue, housetex);
	glPolygonOffset(-1, -1);
	roof(0, 1, 0, 1, 1, roofheight , 1, rooftex, Rred, Rgreen, Rblue);
		
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(-1, -1);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	if(height <= 10){
		drawupflat(1, .55, -.3, 90, .13, .25, Wred, Wgreen, Wblue, windowtex); //left window
		drawupflat(1, .55, .3, 90, .13, .25, Wred, Wgreen, Wblue, windowtex); //left window
		drawupflat(-1, .5, -.35, 90, .15, .3, Wred, Wgreen, Wblue, windowtex); //right window
		drawupflat(-1, .5, .35, 90, .15, .3, Wred, Wgreen, Wblue, windowtex); //right window
		drawupflat(0, .5, -1, 1, .33, .22, Wred, Wgreen, Wblue, windowtex); //back window
		drawupflat(.63, .5, 1, 1, .18, .22, Wred, Wgreen, Wblue, windowtex);  //front window
		drawupflat(0, .41,  1,  1, .2, .4, redDoor, greenDoor, blueDoor, doortex);
	}
	if(height > 10){
		drawupflat(1, .275, -.3, 90, .065, .125, Wred, Wgreen, Wblue, windowtex); //left window
		drawupflat(1, .275, .3, 90, .065, .125, Wred, Wgreen, Wblue, windowtex); //left window
		drawupflat(-1, .275, -.35, 90, .07, .15, Wred, Wgreen, Wblue, windowtex); //right window
		drawupflat(-1, .275, .35, 90, .075, .15, Wred, Wgreen, Wblue, windowtex); //right window
		drawupflat(0, .275, -1, 1, .155, .11, Wred, Wgreen, Wblue, windowtex); //back window
		drawupflat(.63, .275, 1, 1, .09, .11, Wred, Wgreen, Wblue, windowtex);  //front window
		drawupflat(0, .205,  1,  1, .19, .2, redDoor, greenDoor, blueDoor, doortex);
		
		drawupflat(.63, .75, 1, 1, .09, .11, Wred, Wgreen, Wblue, windowtex);  //front window
		glPolygonOffset(-1, 1);
		drawupflat(-.6, .75, 1, 1, .09, .11, Wred, Wgreen, Wblue, windowtex);  //front window
		drawupflat(1, .755, .3, 90, .165, .125, Wred, Wgreen, Wblue, windowtex); //left window
		drawupflat(-.35, .75, -1, 1, .075, .15, Wred, Wgreen, Wblue, windowtex); //backwindow
		drawupflat(.35, .75, -1, 1, .075, .15, Wred, Wgreen, Wblue, windowtex);  //back window
		drawupflat(-1, .75, .35, 90, .11, .14, Wred, Wgreen, Wblue, windowtex); //right window
		drawupflat(-1, .75, -.35, 90, .11, .14, Wred, Wgreen, Wblue, windowtex); //right window
	}
	glPopMatrix();
		
	glDisable(GL_POLYGON_OFFSET_FILL);
	}


//-----------------END OF HOUSE CLASS--------------------------------------------
list<House> houses;
 
 void drawToolBar(){
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
   //  Save transform attributes (Matrix Mode and Enabled Modes)
   glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);
   //  Save projection matrix and set unit transform
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glOrtho(-asp,+asp,-1,1,-1,1);
   //  Save model view matrix and set to indentity
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glDisable(GL_LIGHTING);

   //background bar
   glColor3f(0.8, 0.8, 0.0);
   glBegin(GL_QUADS);
   glVertex2f(-2,-1);
   glVertex2f(+2.2,-1);
   glVertex2f(+2.2,-0.6);
   glVertex2f(-2,-0.6);
   glEnd();
   
   	
	//Color gradient
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0, 0); glVertex2f(color_button_left, color_button_bottom);
    glColor3f(0.0, 1.0, 0);glVertex2f(color_button_right, color_button_bottom);
	glColor3f(0.0, 0.0, 1.0);glVertex2f(color_button_left, color_button_top);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0); glVertex2f(color_button_right, color_button_top);
	glColor3f(0.0, 1.0, 1.0); glVertex2f(color_button_left + .02, color_button_top);
	glColor3f(1.0, 0.0, 1.0); glVertex2f(color_button_right, color_button_bottom + .02);
	glEnd();
	
	//Save house button
	glEnable(GL_TEXTURE_2D);
	if((roofChange == 0 && doorChange == 0 && paintChange == 0 && windowChange == 0)){
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
		glBindTexture(GL_TEXTURE_2D,texture[13]);
	}
	else{
		glColor3f(0, .5, 1);
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
		if(enter == 1) 
			glColor3f(0,0,.8); glBindTexture(GL_TEXTURE_2D,texture[13]);
		}
	glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex2f(save_button_left, save_button_bottom);
    glTexCoord2f(1,0); glVertex2f(save_button_right, save_button_bottom);
    glTexCoord2f(1,1); glVertex2f(save_button_right, save_button_top);
    glTexCoord2f(0,1); glVertex2f(save_button_left, save_button_top);
    glEnd();
	

	
    glColor3f(0.8, 0.8, 0.0);
	//left arrow
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	if((roofChange == 0 && doorChange == 0 && paintChange == 0 && windowChange == 0)){
		glBindTexture(GL_TEXTURE_2D,texture[12]);
	}
	else{
		if(rightclicked == 0) glBindTexture(GL_TEXTURE_2D,texture[10]);
		else glBindTexture(GL_TEXTURE_2D,texture[11]);
	}
	 glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex2f(la_button_left, la_button_bottom);
    glTexCoord2f(1,0); glVertex2f(la_button_right, la_button_bottom);
    glTexCoord2f(1,1); glVertex2f(la_button_right, la_button_top);
    glTexCoord2f(0,1); glVertex2f(la_button_left, la_button_top);
    glEnd();
	
	//right arrow
	if((roofChange == 0 && doorChange == 0 && paintChange == 0 && windowChange == 0)){
		glBindTexture(GL_TEXTURE_2D,texture[12]);
	}
	else{
		if(rightclicked == 0) glBindTexture(GL_TEXTURE_2D,texture[10]);
		else glBindTexture(GL_TEXTURE_2D,texture[11]);
	}
	 glBegin(GL_QUADS);
    glTexCoord2f(1,0); glVertex2f(ra_button_left, ra_button_bottom);
    glTexCoord2f(0,0); glVertex2f(ra_button_right, ra_button_bottom);
    glTexCoord2f(0,1); glVertex2f(ra_button_right, ra_button_top);
    glTexCoord2f(1,1); glVertex2f(ra_button_left, ra_button_top);
    glEnd();
	
	//up_arrow
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	if((roofChange == 0 && doorChange == 0 && paintChange == 0 && windowChange == 0)){
		glBindTexture(GL_TEXTURE_2D,texture[12]);
	}
	else{
		if(upclicked == 0) glBindTexture(GL_TEXTURE_2D,texture[10]);
		else glBindTexture(GL_TEXTURE_2D,texture[11]);
	}
	 glBegin(GL_QUADS);
    glTexCoord2f(1,1); glVertex2f(up_button_left, up_button_bottom);
    glTexCoord2f(1,0); glVertex2f(up_button_right, up_button_bottom);
    glTexCoord2f(0,0); glVertex2f(up_button_right, up_button_top);
    glTexCoord2f(0,1); glVertex2f(up_button_left, up_button_top);
    glEnd();
	
	//down_arrow
	if((roofChange == 0 && doorChange == 0 && paintChange == 0 && windowChange == 0)){
		glBindTexture(GL_TEXTURE_2D,texture[12]);
	}
	else{
		if(downclicked == 0) glBindTexture(GL_TEXTURE_2D,texture[10]);
		else glBindTexture(GL_TEXTURE_2D,texture[11]);
	}
	 glBegin(GL_QUADS);
    glTexCoord2f(0,1); glVertex2f(down_button_left, down_button_bottom);
    glTexCoord2f(0,0); glVertex2f(down_button_right, down_button_bottom);
    glTexCoord2f(1,0); glVertex2f(down_button_right, down_button_top);
    glTexCoord2f(1,1); glVertex2f(down_button_left, down_button_top);
    glEnd();
	
	//edit done button
	if((roofChange == 0 && doorChange == 0 && paintChange == 0 && windowChange == 0)){
		glBindTexture(GL_TEXTURE_2D,texture[7]);
	}
	else
		if(edithover) glBindTexture(GL_TEXTURE_2D, texture[9]);
		else glBindTexture(GL_TEXTURE_2D,texture[8]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex2f(done_button_left, done_button_bottom);
    glTexCoord2f(1,0); glVertex2f(done_button_right, done_button_bottom);
    glTexCoord2f(1,1); glVertex2f(done_button_right, done_button_top);
    glTexCoord2f(0,1); glVertex2f(done_button_left, done_button_top);
    glEnd();
	
	glEnable(GL_DEPTH_TEST);
	
   //  Reset model view matrix
   glPopMatrix();
   //  Reset projection matrix
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   //  Pop transform attributes (Matrix Mode and Enabled Modes)
   glPopAttrib();
 }
 

//New House pop up function
void HousePop(double inx, double iny, double inz, double inth, double inwidth,  double inheight, double indepth, double inroofheight,
		double inred, double ingreen, double inblue, double inredDoor, double ingreenDoor, double inblueDoor,
		double Rinred, double Ringreen, double Rinblue, double Winred, double Wingreen, double Winblue, 
		unsigned int inhousetex, unsigned int inrooftex, unsigned int inwindowtex,unsigned int indoortex)
{		House tempHouse(inx, iny, inz, inth, inwidth, inheight, indepth, inroofheight,
		 inred, ingreen, inblue, inredDoor, ingreenDoor, inblueDoor,
		 Rinred, Ringreen, Rinblue, Winred, Wingreen, Winblue, 
		inhousetex, inrooftex, inwindowtex, indoortex);	
	if(enter == 0){
	tempHouse.drawHouse();
	}
	else{
		housePopup = 0;
		//House tempHouse(x, y, z, th,width, height,depth, roofheight, red, green, blue,
		//redDoor, greenDoor, blueDoor, PHredR, PHgreenR, PHblueR, PHredW, PHgreenW, PHblueW,
		//housetex, rooftex, windowtex, doortex);
		
		houses.push_back(tempHouse);
		enter = 0;
		 PHx =0;  PHy = 0;  PHz= 0; PHth = 0; 
	     PHwidth = 5; PHheight = 5;  PHdepth = 5; PHroofheight= 1.9;
		PHred =.70; PHgreen= .2;  PHblue=0;  PHhousetex = 11;  PHrooftex= 4; PHwindowtex = 2;
		PHredDoor = 1;  PHgreenDoor = 0;   PHblueDoor = 0;  PHdoortex = 0;
		PHredW = .6; PHgreenW = .6; PHblueW = 0;
		PHredR = .8;  PHgreenR = .2;  PHblueR = 0;
		
	   //printf("things should have reset, PHx : %f", PHx);
	}
}


/* OpenGL calls this routine to display the scene
*/ 
void display(){

	//Eye position
	double Ex = -2*dim*Sin(th)*Cos(ph);
	double Ey = +2*dim        *Sin(ph);
	double Ez = +2*dim*Cos(th)*Cos(ph);
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//Background should be sky blue!
	glClearColor(0.0f, 0.99f, 0.999f, 0.1f);
	
	glEnable(GL_DEPTH_TEST);
	//Set perspective
	glLoadIdentity();
	gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
	
	glEnable(GL_FOG);
	glFogf(GL_FOG_DENSITY, .4f);
	float FogCol[3]={0.6f,0.6f,0.6f}; // Define a nice light grey
	glFogfv(GL_FOG_COLOR,FogCol);     // Set the fog color
  
  
	glFogi(GL_FOG_MODE, GL_LINEAR); // Note the 'i' after glFog - the GL_LINEAR constant is an integer.
	glFogf(GL_FOG_START, 96.f);
	glFogf(GL_FOG_END, 450.f);
	
	//Let there be light
	if(light)
		sun();
	 else{
		glDisable(GL_LIGHTING);
	}
	//Texture stuff
	glEnable(GL_TEXTURE_2D);
	//example house
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_BLEND);
	HousePop(-20, 0, -2, 25, 5.3, 3.3, 4.4, 1.2, .7, .2, 0, 1, 0, 0, .8, .2, 0,
	.6, .6, 0, Htexture[11], Htexture[4], winTexture[2], doorTexture[0]);
	
	//if someone pressed the housebutton, pop up an editable house object
	if (housePopup == 1){
	
		HousePop(PHx, PHy, PHz, PHth, PHwidth, PHheight, PHdepth, PHroofheight, PHred, 
		PHgreen, PHblue,PHredDoor, PHgreenDoor, PHblueDoor, PHredR, PHgreenR, PHblueR,
		PHredW, PHgreenW, PHblueW, Htexture[PHhousetex], Htexture[PHrooftex], winTexture[PHwindowtex], 
		doorTexture[PHdoortex]);
	}
	
	list<House>::iterator p = houses.begin();
	while(p != houses.end()) {
		p->drawHouse();
		p++;
	}	 
	//for(int i = 0; i < 10; i++){
	//	houses[i].drawHouse();
	//}
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	//float green[]   = {0.0, 0.01f*diffuse, 0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white2);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black2);
	//glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,green);
	//Draw some happy trees

	glColor3f(0, .8, 0);	tree(-4, 12, -49,    5, 12, Htexture[2]);
		glColor3f(0, .7, 0);tree(-34, 11, -40,    6, 72, Htexture[2]);
	glColor3f(0, .2, .3);	tree(-83, 7, -39,    4.6, 10, Htexture[2]);
		glColor3f(0, .7, .3);tree(-26, 10, -30,    3.2, 0, Htexture[2]);
	
	glColor3f(0, .6, .3); tree(-96, 8, 2,    2, 20, Htexture[2]);
	glColor3f(0, .6, .3);tree(29, 8, -60,    3.2, 70, Htexture[2]);
	glColor3f(0, .6, .3);tree(26, 8.4, 60,    5, 30, Htexture[2]);
	glColor3f(0, .6, .3);tree(37, 9.5, 80,    4.1, 62, Htexture[2]);
	glColor3f(0, .6, .3);tree(26, 9, 85,    3, 25, Htexture[2]);
	glColor3f(0, .6, .3);tree(29, 7.6, 88,    4.2, 45, Htexture[2]);
	glColor3f(0, .6, .3);tree(45, 6.4, 88,    2.6, 25, Htexture[2]);
	glColor3f(0, .6, .3); tree(-89, 11, -95, 6, 2, Htexture[2]);
	glColor3f(0, .6, .3);tree(-8, 10, -51,    4, 40, Htexture[2]);
	glColor3f(0, .6, .3);tree(-87, 17, -20,    7.4, 30, Htexture[2]);
    glColor3f(0, .6, .2);tree(-92, 16, 0,    3.4, 36, Htexture[2]);
   glColor3f(0, .6, .3);tree(-90, 18, -12,    3, 90, Htexture[2]);
  glColor3f(0, .4, .3);tree(-84, 14, 8,    3, 5, Htexture[2]);
	glColor3f(0, .4, .3);tree(-82, 16, 0,    5.8, 12, Htexture[2]);
	
	glColor3f(0, .75, .2);tree(2, 15, 89,    4, 94, Htexture[2]);
	glColor3f(0, .75, .2);tree(5, 8, 90,    3, 25, Htexture[2]);
	glColor3f(0, .75, .2);tree(2, 6, 78,    2.6, 25, Htexture[2]);
	
	glColor3f(0, .75, .2);tree(-10, 7, -23,    2.5, 0, Htexture[2]);
	
    //Draw the ground
    drawflat(0,0,0, 0, 100, 100, 0, .95, 0, texture[0]);   
	
	//Draw the toolbar
	drawToolBar();
	
	
	//Disable depth and lighting for the buttons
	glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glLoadIdentity();
	//Get ready to draw these here buttons
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
	
	glColor3f(0.8, 0.8, 0.0);
	//Customizable button
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[hoverindex]);
	//Draw the button
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(selector_left, selector_bottom, 0);
    glTexCoord2f(1,0); glVertex3f(selector_right, selector_bottom, 0);
    glTexCoord2f(1,1); glVertex3f(selector_right, selector_top, 0);
    glTexCoord2f(0,1); glVertex3f(selector_left, selector_top, 0);
    glEnd();
	
	 glColor3f(0.8, 0.8, 0.0);
   //House BUTTON
     if (button_pressed){
		//if the button is pressed give the clicked texture index
		housePopup = 1;
		glColor3f(0, 0, 1);
		//Sleep(400);
		}

	//Don't forget texture stuff
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	//Draw the button
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(button_left, button_bottom, 0);
    glTexCoord2f(1,0); glVertex3f(button_right, button_bottom, 0);
    glTexCoord2f(1,1); glVertex3f(button_right, button_top, 0);
    glTexCoord2f(0,1); glVertex3f(button_left, button_top, 0);
    glEnd();
	
	button_pressed = 0;
	rightclicked =0;
	leftclicked = 0;
	upclicked = 0;
	downclicked = 0;
	edithover = 0;
	
	//Set everything back to normal
	glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
   
	//Render the scene and make it visible
    //ErrCheck("display");
    glFlush();
    glutSwapBuffers();
}

/*void processHits(GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLuint names, *ptr;

   printf("hits = %d\n", hits);
   ptr = (GLuint *) buffer;
   for (i = 0; i < hits; i++) {   for each hit  
      names = *ptr;
      printf(" number of names for hit = %d\n", names); ptr++;
      printf("  z1 is %g;", (float) *ptr/0x7fffffff); ptr++;
      printf(" z2 is %g\n", (float) *ptr/0x7fffffff); ptr++;
      printf("   the name is ");
      for (j = 0; j < names; j++) {   for each name 
         printf("%d ", *ptr); ptr++;
      }
      printf("\n");
   }
}
*/

void processMousePassiveMotion(int x, int y){
	if(roofChange == 0 && doorChange == 0 && paintChange == 0 && windowChange == 0){
		if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > selector_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < selector_right && (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> selector_bottom && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < selector_top){
			//Hightlight the roof
			if((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > selector_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < (selector_right) && (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> (selector_top -  .15) && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < selector_top) 
				hoverindex = 6;
				
			//Hightlight the door	
			else if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > selector_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < (selector_right - .17 )&& (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> (selector_bottom) && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < selector_top- .15)
				hoverindex = 4;
				
			//window
			else if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > (selector_left+.17) && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < (selector_right) && (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> (selector_bottom + .08) && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < selector_top- .15) 
				hoverindex = 3;
				
			else hoverindex = 5;
				
		}
		else hoverindex = 2;
	}
}

#define BUFSIZE 512
void picker(int button, int state, int x, int y){
	mousex = x;
	mousey = y;
	//Left mouse button
	if (button == GLUT_LEFT_BUTTON)
	{
		//Clicked in location of our on-screen button
		if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > button_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < button_right && (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> button_bottom && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < button_top)
		{
			//Pressed or released?
			if (state == GLUT_DOWN)button_pressed = 1;
			else{
				button_pressed = 0;
				glutWarpPointer(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
			}
		}
		
		if (state == GLUT_DOWN){
		if(roofChange == 0 && doorChange == 0 && paintChange == 0 && windowChange == 0){
			if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > selector_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < selector_right && (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> selector_bottom && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < selector_top){
			
				//change the roof texture
				if((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > selector_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < (selector_right) && (
				SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> (selector_top -  .15) && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < selector_top){
					roofChange = 1;
				}
				
				//change the door texture	
				else if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > selector_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < (selector_right - .17 )&& (
				SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> (selector_bottom) && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < selector_top- .15){
					doorChange = 1;
				}
				
				//change the window texture
				else if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > (selector_left+.17) && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < (selector_right) && (
				SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> (selector_bottom + .08) && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < selector_top- .15){ 
					windowChange = 1;
				}
				else{
					 paintChange = 1;
					}
			}
		}
		
		//cycle textures left
		if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > la_button_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < la_button_right && (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> la_button_bottom && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < la_button_top){
			leftclicked = 1;
			if (roofChange)
				if(PHrooftex ==0){PHrooftex = 15;}
				else PHrooftex--;
			//	if(tempHouse.rooftex == 0) tempHouse.rooftex = 5;
			//	else tempHouse.rooftex ++;
				
			else if(doorChange)	
				if(PHdoortex ==0){ PHdoortex = 4;}
					else PHdoortex--;
					
			else if(windowChange)
				if(PHwindowtex == 0){ PHwindowtex = 5;}
					else PHwindowtex--;
					
			else if(paintChange)
				if(PHhousetex ==0){PHhousetex = 15;}
					else PHhousetex--;
			else leftclicked = 0;
		}
		//cycle textures right
		if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > ra_button_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < ra_button_right && (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> ra_button_bottom && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < ra_button_top){
			rightclicked = 1;
			if (roofChange)
				if(PHrooftex ==15){PHrooftex = 0;}
				else PHrooftex++;
				
			else if(doorChange)	
				if(PHdoortex ==4){ PHdoortex = 0;}
					else PHdoortex++;
					
			else if(windowChange)
				if(PHwindowtex == 5){ PHwindowtex = 0;}
					else PHwindowtex++;
					
			else if(paintChange)
				if(PHhousetex ==15){PHhousetex = 0;}
					else PHhousetex++;
			else rightclicked = 0;
		}
		
		//increase color brightness
		if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > up_button_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < up_button_right && (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> up_button_bottom && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < up_button_top){
			upclicked = 1;
			if (roofChange){
				if(!(PHredR==1 || PHblueR == 1 || PHgreenR == 1))
					PHredR= PHredR + .02;
					PHgreenR= PHgreenR + .02;
					PHblueR= PHblueR + .02;
				}	
			else if(doorChange){
				if(!(PHredDoor==1 || PHblueDoor == 1 || PHgreenDoor == 1))
					PHredDoor= PHredDoor + .02;
					PHgreenDoor= PHgreenDoor + .02;
					PHblueDoor= PHblueDoor + .02;
			}	
			else if(windowChange){
				if(!(PHredW==1 || PHblueW == 1 || PHgreenW == 1))
					PHredW= PHredW + .02;
					PHgreenW= PHgreenW + .02;
					PHblueW= PHblueW + .02;
			}		
			else if(paintChange){
				if(!(PHred==1 || PHblue == 1 || PHgreen == 1))
					PHred= PHred + .02;
					PHgreen= PHgreen + .02;
					PHblue= PHblue + .02;
				}
			else upclicked = 0;
		}

	//decrease color brightness
		if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > down_button_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < down_button_right && (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> down_button_bottom && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < down_button_top){
			downclicked = 1;
			if (roofChange){
				if(!(PHredR==0 || PHblueR == 0 || PHgreenR == 0))
					PHredR= PHredR - .02;
					PHgreenR= PHgreenR - .02;
					PHblueR= PHblueR - .02;
			}	
			else if(doorChange){	
				if(!(PHredDoor==0 || PHblueDoor == 0 || PHgreenDoor == 0))
					PHredDoor= PHredDoor - .02;
					PHgreenDoor= PHgreenDoor - .02;
					PHblueDoor= PHblueDoor - .02;
			}		
			else if(windowChange){
				if(!(PHredW==0 || PHblueW == 0 || PHgreenW == 0))
					PHredW= PHredW - .02;
					PHgreenW= PHgreenW - .02;
					PHblueW= PHblueW - .02;
			}	
			else if(paintChange){
				if(!(PHred==0 || PHblue == 0 || PHgreen == 0))
					PHred= PHred - .02;
					PHgreen= PHgreen - .02;
					PHblue= PHblue - .02;
			}
			else downclicked = 0;
		}
			
			
		if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > done_button_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < done_button_right && (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> done_button_bottom && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < done_button_top){
			roofChange = 0;
			doorChange = 0; 
			paintChange = 0;
			windowChange = 0;
			edithover = 1;
		}
					
		if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > save_button_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < save_button_right && (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> save_button_bottom && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < save_button_top){
			enter = 1;
		}
		//Clicked in location of our on-screen button
		if(!(roofChange == 0 && doorChange == 0 && paintChange == 0 && windowChange == 0)){
		if ((x*2.0 - SCREEN_HEIGHT)/SCREEN_WIDTH > color_button_left && (x*2.0 - SCREEN_WIDTH)/SCREEN_WIDTH < color_button_right && (
		SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT> color_button_bottom && (SCREEN_HEIGHT - y*2.0)/SCREEN_HEIGHT < color_button_top)
		{
		    mousey = SCREEN_HEIGHT - y;
			unsigned char pixel[4];					//unsigned_byte
			glReadPixels(x, mousey, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

			if(roofChange){
				PHblueR = (double)pixel[2]/255;
				PHredR = (double)pixel[0]/255;
				PHgreenR = (double)pixel[1]/255;
				}
			if(doorChange){
				PHblueDoor = (double)pixel[2]/255;
				PHredDoor = (double)pixel[0]/255;
				PHgreenDoor = (double)pixel[1]/255;
				}
			if(paintChange){
				PHred =(double)pixel[0]/255;
				PHblue = (double)pixel[2]/255;
				PHgreen  =(double)pixel[1]/255;
				}
			if(windowChange){
				PHblueW = (double)pixel[2]/255;
				PHredW =(double)pixel[0]/255;
				PHgreenW = (double)pixel[1]/255;
				}
		}
	}
	}
}
}
		//THIS IS the attempt at a picker algorithm, temporarily gone.
		/*glSelectBuffer(BUFSIZE, selectBuf); //Array to be used for recording object hits
		(void) glRenderMode(GL_SELECT); 	//Enter Selection Mode
		
		//Initialize the name stack
		glInitNames();  
		glPushName(0);
		
		//Save current transformation state.
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
	
		// Create a 5x5 picking region near cursor location
		gluPickMatrix((GLdouble) mousex, (GLdouble) (viewport[3] - mousey), 5.0,
		5.0, viewport);
		drawHouse(GL_SELECT, -7,0, 0,    0,     3, 5, 3.4,   2,   .85,.8,0,  .9,.9,0, .7,.7,0,   0.9,.8,0, texture[1], texture[5]);
		
		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glFlush ();
		
		hits = glRenderMode (GL_RENDER);
		processHits (hits, selectBuf);
		glutPostRedisplay();
		*/
	
	


/*
 *  GLUT calls this routine when the window is resized
 */
void idle(){
   //Elapsed time in seconds
   ptime = glutGet(GLUT_ELAPSED_TIME)/1000.0;
  
   //Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}


/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{	 
	//Right arrow key - increase angle by 5 degrees
    if (key == GLUT_KEY_RIGHT)
		th += 5;
    //Left arrow key - decrease angle by 5 degrees
	else if (key == GLUT_KEY_LEFT) 
		th -= 5;
    //Up arrow key - increase elevation by 5 degrees
	else if ((key == GLUT_KEY_UP)&& (ph < 90))
		ph += 2;
    //Down arrow key - decrease elevation by 5 degrees
    else if ((key == GLUT_KEY_DOWN)&&(ph > 10))
		ph -= 2;
    //PageUp key - increase dim
    else if (key == GLUT_KEY_PAGE_DOWN)
		dim += 0.1;
    //PageDown key - decrease dim
	else if (key == GLUT_KEY_PAGE_UP && dim>1)
		dim -= 0.1;
		
		
    //Keep angles to +/-360 degrees
    th %= 360;
    ph %= 360;
    //Update projection
    Project(fov,asp,dim);
    //Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}


 /*  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{  
	//quit with esc
	if (ch == 27)
		exit(0);
	//Zoom in
	else if(ch == 'p')
		dim++;
	else if(ch =='o')
		dim = dim-1;
	//Reset view angle
	else if (ch == '0')
		th = ph = 0;
		
	//Change field of view angle
	else if (ch == '+' && ch>1)
		fov--;
	else if (ch == '-' && ch<179)
		fov++;
		
	if(housePopup == 1){
	//enter the house as permanent
		if(ch == 'n')
			enter = 1;
	//Move the object
		//A moves left
		if(ch == 'a' && PHx > -95)
			PHx= PHx -1;
		//D moves right
		if(ch == 'd' && PHx < 95)
			PHx = PHx +1;
	    //w moves out
		if(ch == 'w' && PHz > -95)
			PHz = PHz -1;
		//s moves in
		if(ch == 's' && PHz < 95)
			PHz = PHz +1;
		
		// z/Z shrinks/expands the z dimension
		if(ch == 'z')
			PHdepth = PHdepth +1;
		if(ch == 'Z' && PHdepth > 1)
			PHdepth = PHdepth -1;
			
			// x/X shrinks/expands the x dimension
		if(ch == 'x')
			PHwidth = PHwidth +1;
		if(ch == 'X' && PHwidth > 1)
			PHwidth = PHwidth -1;	
			
		// c/C shrinks/expands the y dimension
		if(ch == 'c')
			PHheight = PHheight +.5;
		if(ch == 'C' && PHheight > .5)
			PHheight = PHheight -.5;	
			
			
		// v/V shrinks/expands the roof
		if(ch == 'v' && PHroofheight >= .5)
			PHroofheight = PHroofheight +.25;
		else if(ch == 'v' && PHroofheight < .5 && PHroofheight >= .1)
			PHroofheight = PHroofheight + .1;	
		else if(ch == 'v' && PHroofheight < .1 && PHroofheight >= .01)		
				PHroofheight = PHroofheight + .01;
	
		if(ch == 'V' && PHroofheight > .5)
			PHroofheight = PHroofheight -.25;
		else if(ch == 'V' && PHroofheight <= .5 && PHroofheight > .1)
			PHroofheight = PHroofheight -.1;
		else if(ch == 'V' && PHroofheight <=.1 && PHroofheight > .01)		
				PHroofheight = PHroofheight - .01;
				
		// f rotates he house 
		if(ch == 'f'){
			if(PHth < 360)
				PHth = PHth + 2;
			else PHth = 0;
			}
		if(ch == 'F'){
			if(PHth > 0)
				PHth = PHth -2 ;
			else PHth = 360;
		}	
	}

    //Translate shininess power to value (-1 => 0)
	shinyvec[0] = shininess<0 ? 0 : pow(2.0,shininess);
    //Reproject
    Project(fov,asp,dim);
    //Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //save window width and height
   SCREEN_WIDTH= width;
   SCREEN_HEIGHT = height;
   //  Set projection
   Project(fov,asp,dim);
}

	

int main(int argc, char* argv[]){
 
	//Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
   glutCreateWindow("Textures and Lighting");
   
      //  Load textures
   texture[0] = LoadTexBMP("grass.bmp");
   texture[1] = LoadTexBMP("newhouse.bmp");
   texture[2] = LoadTexBMP("edithouse.bmp");
   texture[3] = LoadTexBMP("windowclick.bmp");
   texture[4] = LoadTexBMP("doorclick.bmp");
   texture[5] = LoadTexBMP("paintclick.bmp");
   texture[6] = LoadTexBMP("roofclick.bmp");
   texture[7] = LoadTexBMP("preedit.bmp");
   texture[8] = LoadTexBMP("doneedit.bmp");
   texture[9] = LoadTexBMP("doneeditclick.bmp");
   texture[10] = LoadTexBMP("larrow.bmp");
   texture[11] = LoadTexBMP("lcarrow.bmp");   
   texture[12] = LoadTexBMP("rarrow.bmp");   
   texture[13] = LoadTexBMP("Save.bmp");   
   
   Htexture[0] = LoadTexBMP("crate.bmp");
   Htexture[1] = LoadTexBMP("StoneWall.bmp");
   Htexture[2] = LoadTexBMP("bark.bmp");
   Htexture[3] = LoadTexBMP("roof.bmp");
   Htexture[4] = LoadTexBMP("brick.bmp");
   Htexture[5] = LoadTexBMP("s.bmp");
   Htexture[6] = LoadTexBMP("roof2.bmp");
   Htexture[7] = LoadTexBMP("roof3.bmp");
   Htexture[8] = LoadTexBMP("roof4.bmp");
   Htexture[9] = LoadTexBMP("roof5.bmp");
   
   Htexture[10] = LoadTexBMP("paint.bmp"); 
   Htexture[11] = LoadTexBMP("paint2.bmp");   
   Htexture[12] = LoadTexBMP("paint3.bmp");
   Htexture[13] = LoadTexBMP("paint4.bmp"); 
   Htexture[14] = LoadTexBMP("paint5.bmp");   
   Htexture[15] = LoadTexBMP("paint6.bmp");
   
   doorTexture[0] = LoadTexBMP("door.bmp");
   doorTexture[1] = LoadTexBMP("door2.bmp");
   doorTexture[2] = LoadTexBMP("door3.bmp");
   doorTexture[3] = LoadTexBMP("door4.bmp");
   doorTexture[4] = LoadTexBMP("door5.bmp");
   
   winTexture[0] = LoadTexBMP("window2.bmp");
   winTexture[1] = LoadTexBMP("window.bmp");
   winTexture[2] = LoadTexBMP("window3.bmp");
   winTexture[3] = LoadTexBMP("window4.bmp");
   winTexture[4] = LoadTexBMP("window5.bmp");
   winTexture[5] = LoadTexBMP("window6.bmp");
   

   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   
   //process mouse callbacks
	glutMouseFunc(picker);
	//glutMotionFunc(processMouseActiveMotion);
	glutPassiveMotionFunc(processMousePassiveMotion);
	//glutEntryFunc(processMouseEntry);
   
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
