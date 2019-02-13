#include<windows.h>
#include <iostream>
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "text3d.h"
using namespace std;

#include "imageloader.h"

using namespace std;

int r_count = 0 , s_count = 0 ;
/// this variables are used for controlling how many times scaling can be done

float computeScale(const char* strs[2]) {
	float maxWidth = 0;
	for(int i = 0; i < 2; i++) {
		float width = t3dDrawWidth(strs[i]);
		if (width > maxWidth) {
			maxWidth = width;
		}
	}

	return 2.6f / maxWidth;
}

float _ang = -30.0f;
float _sca;

int fog_flag = 0 ;

const char* STRS[2] = {"Shinto", "Shrine"};
/// words to display

void cleanup() {
	t3dCleanup();
}

GLfloat s_var = 1;
GLfloat x_ax = 0 , y_ax = 0 , z_ax = 0;

/*----------------------*/
float angle = -5.0f;
float angle2 = 0.0f;
float angle3 = 0.0f;
float posL1=0.1f;
float posL2=0.1f;
float posL3=0.1f;
float R=0,G=0,B=0;
int night = 0;
int timer_flag = 0;

void Light()
{
	GLfloat lightColor0[] = {posL1, posL2, posL3, 1.0f};
	GLfloat lightPos0[] = {0.0f, 8.0f, -8.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
}


void keyboardkey(int key, int x, int y)
{

	if(key==GLUT_KEY_DOWN)
    {
        R = 1.0; G = 0.8; B = 0.5;
        night = 0;

    }
	else if(key==GLUT_KEY_UP)
    {
        R = 0.0; G = 0.0; B = 0.0;
        night = 1;

    }

    /// rotate around x axis
    if(key == GLUT_KEY_RIGHT)
    {
        cout<<angle<<endl;
        //timer_flag=1;
        if(angle < 193)
        {
            angle+=1.0;
        }

        if(angle > 360.0)
        {
            angle-=360.0;
            cout<<angle<<endl;
        }
    }
    else if(key == GLUT_KEY_LEFT)
    {

        cout<<angle<<endl;

        if(angle > -7)
        {
            angle-=1.0;
        }

        if(angle<0)
        {
            //angle +=360;
            cout<<angle<<endl;
        }
    }



    glutPostRedisplay();

}
/*---------------------------------*/

void handleKeypress(unsigned char key, int x, int y)
{

	switch (key)
	{
		case 27:
			exit(0);
	}


	if(key == 's' || key =='S') /// zoom in
    {
        if(s_count < 9)
        {
            s_count = s_count + 1;
            s_var +=0.05;
        }


        if(r_count >0)
            r_count = r_count-1;
    }

    if(key =='r' || key =='R') /// zoom out
    {


        if(r_count < 9)
        {
            r_count = r_count + 1 ;
            s_var -=0.05;
        }

        if(s_count > 0)
            s_count = s_count - 1 ;
    }


    /// rotate around y axis
    if(key == 'm' || key =='M')
    {
        angle2 +=1.0;

        if(angle2 > 360.0)
        {
            angle2 -=360.0;
        }
    }

    if(key == 'n' || key =='N')
    {
        angle2 -=1.0;
        if(angle2 <0)
        {
            angle2 +=360;;
        }
    }

    /// rotate around z axis
    if(key == 'o' || key =='O')
    {
        angle3 +=1.0;

        if(angle3 > 360.0)
        {
            angle3 -=360.0;
        }
    }

    if(key == 'p' || key =='P')
    {
        angle3 -=1.0;
        if(angle3 <0)
        {
            angle3 +=360;;
        }
    }



    if(key == 'F' || key =='f') /// fog effect on
    {
        fog_flag = 1 ;
    }

    if(key == 'G' || key =='g') /// fog effect off
    {
        fog_flag = 0 ;
    }



}

GLuint loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 image->pixels);
	return textureId;
}

GLuint _textureId0, _textureId1, _textureId_t_f_l, _textureId_sh_b, _textureId_wl, _textureId_roof,  _textureId_door,
       _textureId_window, _textureId_stairs , _textureId_sky, _textureId_nightsky, _textureId_ground, _textureId_pl;

void initRendering() {
    glClearColor(0.5,0.5,0.5,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	t3dInit();
	glEnable(GL_FOG);



	Image* image0 = loadBMP("grass0.bmp");
	_textureId0 = loadTexture(image0);
	delete image0;

	Image* image1 = loadBMP("r1.bmp");
	_textureId_t_f_l = loadTexture(image1);
	delete image1;

	Image* image2 = loadBMP("rockywall.bmp");
	_textureId_sh_b = loadTexture(image2);
	delete image2;

	Image* image3 = loadBMP("wall_img.bmp");
	_textureId_wl = loadTexture(image3);
	delete image3;

	Image* image4 = loadBMP("roof.bmp");
	_textureId_roof = loadTexture(image4);
	delete image4;

	Image* image5 = loadBMP("door.bmp");
	_textureId_door = loadTexture(image5);
	delete image5;

	Image* image6 = loadBMP("window.bmp");
	_textureId_window = loadTexture(image6);
	delete image6;

	Image* image7 = loadBMP("stair.bmp");
	_textureId_stairs = loadTexture(image7);
	delete image7;

	Image* image8 = loadBMP("skypic.bmp");
	_textureId_sky = loadTexture(image8);
	delete image8;

	Image* image9 = loadBMP("night.bmp");
	_textureId_nightsky = loadTexture(image9);
	delete image9;

	Image* image10 = loadBMP("ground.bmp");
	_textureId_ground = loadTexture(image10);
	delete image10;

	Image* image11 = loadBMP("wwod.bmp");
	_textureId_pl = loadTexture(image11);
	delete image11;


}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(R,G,B,1);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1.0};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 5.0f);

    if(fog_flag == 1)
    {
        glEnable(GL_FOG);
        GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1.0};
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogi(GL_FOG_MODE, GL_LINEAR);
        glFogf(GL_FOG_START, 5.0f);
        glFogf(GL_FOG_END, 26.0f);
        glFogf(GL_FOG_DENSITY, 0.05f);
    }

    if(fog_flag == 0)
    {
        glDisable(GL_FOG);
    }





    Light();


	glTranslatef(0.0f, 1.0f, -15.0f);
	glScalef(s_var,s_var,s_var);

	//glRotatef(angle, x_ax, y_ax, z_ax);


	//if(x_ax == 1)
  //  {
        ///glRotatef(angle,1.0, 0.0f, 0.0f);
   // }
   // else if(y_ax == 1)
   // {
        ///glRotatef(angle2,0.0, 1.0f, 0.0f);
   // }
   // else if(z_ax == 1)
   // {
   //     glRotatef(angle,0.0, 0.0f, 1.0f);
   // }


/*----------
	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
*/
	glEnable(GL_TEXTURE_2D);

	if(night == 1)
    {
        glBindTexture(GL_TEXTURE_2D, _textureId_nightsky);
    }
    else if(night == 0)
    {
        glBindTexture(GL_TEXTURE_2D, _textureId_sky);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    /// this quad is for the sky picture
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-30.5f, -20.5f, -9.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(30.5f, -20.5f, -9.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(30.5f, 20.5f, -9.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-30.5f, 20.5f, -9.5f);
	glEnd();

	glRotatef(angle,1.0, 0.0f, 0.0f);
    glRotatef(angle2,0.0, 1.0f, 0.0f);
    //glRotatef(angle3,0.0, 0.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, _textureId0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// bottom
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -4.5f, 2.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -4.5f, 2.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -4.5f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -4.5f, -8.5f);
	glEnd();



	glBindTexture(GL_TEXTURE_2D, _textureId_stairs);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /*----------------------------*/ //done
    glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -5.0f, 2.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -5.0f, 2.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -4.5f, 2.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -4.5f, 2.5f);
	glEnd();
	/*-----------------------------*/ // done
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -6.2f, -8.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -6.2f, -8.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -4.5f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -4.5f, -8.5f);
	glEnd();
	/*-----------------------------*/ //done
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(6.5f, -5.0f, 2.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -5.0f, -8.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -4.5f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(6.5f, -4.5f, 2.5f);
	glEnd();
	/*-----------------------------*/ // done
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -5.0f, 2.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-6.5f, -5.0f, -8.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-6.5f, -4.5f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -4.5f, 2.5f);
	glEnd();

	/*------------------------------*/ //// done
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -5.5f, 3.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -5.5f, 3.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -5.0f, 3.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -5.0f, 3.0f);
	glEnd();
	/*-------------------------------*/ ////done
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(6.5f, -5.5, 3.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -5.5f, -8.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -5.0f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(6.5f, -5.0f, 3.0f);
	glEnd();
	/*--------------------------------*/ // // done
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -5.5, 3.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-6.5f, -5.5f, -8.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-6.5f, -5.0f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -5.0f, 3.0f);
	glEnd();
	/*----------------------------------*/ //done
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -6.0, 3.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -6.0f, 3.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -5.5f, 3.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -5.5f, 3.5f);
	glEnd();
	/*----------------------------------*/ //done
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(6.5f, -6.0, 3.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -6.0f, -8.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -5.5f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(6.5f, -5.5f, 3.5f);
	glEnd();
	/*----------------------------------*/ // done
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -6.0, 3.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-6.5f, -6.0f, -8.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-6.5f, -5.5f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -5.5f, 3.5f);
	glEnd();
	/*----------------------------------*/ // done
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -6.2, 4.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -6.2f, 4.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -6.0f, 4.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -6.0f, 4.0f);
	glEnd();
	/*----------------------------------*///done
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(6.5f, -6.2, 4.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -6.2f, -8.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -6.0f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(6.5f, -6.0f, 4.0f);
	glEnd();
	/*----------------------------------*///done

	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -6.2, 4.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-6.5f, -6.2f, -8.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-6.5f, -6.0f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -6.0f, 4.0f);
	glEnd();

	/*----------------------------------*/


    // 2nd bottom
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -5.0f, 3.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -5.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -5.0f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -5.0f, -8.5f);
	glEnd();

	 // 3rd bottom
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -5.5f, 3.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -5.5f, 3.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -5.5f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -5.5f, -8.5f);
	glEnd();

	// 4th bottom
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-6.5f, -6.0f, 4.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.5f, -6.0f, 4.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.5f, -6.0f, -8.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-6.5f, -6.0f, -8.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureId0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// 5th bottom
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-100.5f, -6.2f, 100.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(100.5f, -6.2f, 100.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(100.5f, -6.2f, -100.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-100.5f, -6.2f, -100.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureId_t_f_l);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//tori front left
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5f, -4.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.0f, -4.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.0f, .5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.5f, .5f, 1.5f);
	glEnd();

	//tori back left
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5f, -4.5f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.0f, -4.5f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.0f, .5f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.5f, .5f, 1.0f);
	glEnd();

	// tori left up
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5f, .5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.0f, .5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.0f, .5f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.5f, .5f, 1.0f);
	glEnd();


	// tori left - left face
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5f, -4.5f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.5f, -4.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.5f, 0.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.5f, .5f, 1.0f);
	glEnd();

	// tori left - right face
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.0f, -4.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.0f, -4.5f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.0f, 0.5f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.0f, .5f, 1.5f);
	glEnd();

    //tori front right
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.5f, -4.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.0f, -4.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.0f, .5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5f, .5f, 1.5f);
	glEnd();

	//tori back right
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.5f, -4.5f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.0f, -4.5f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.0f, .5f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5f, .5f, 1.0f);
	glEnd();

	// tori right up
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.5f, .5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.0f, .5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.0f, .5f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.5f, .5f, 1.0f);
	glEnd();

	// tori right - left face
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.5f, -4.5f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5f, -4.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.5f, 0.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.5f, .5f, 1.0f);
	glEnd();

	// tori right - right face
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.0f, -4.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.0f, -4.5f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.0f, 0.5f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.0f, .5f, 1.5f);
	glEnd();

	// tori upper one
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.f, .5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.f, .5f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.f, .5f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.f, .5f, 1.5f);
	glEnd();

	// tori upper two
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.5f, 0.7f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.5f, 0.7f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.5f, 0.7f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.5f, 0.7f, 1.5f);
	glEnd();

	// tori upper zero
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, 0.0f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.2f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.2f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.2f, 0.0f, 1.5f);
	glEnd();

	///
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.0f, 0.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, 0.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.5f, 0.7f, 1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5f, 0.7f, 1.5f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.0f, 0.5f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, 0.5f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.5f, 0.7f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5f, 0.7f, 1.0f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.0f, .5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, .5f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.5f, 0.7f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.5f, 0.7f, 1.5f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.0f, .5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0f, .5f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.5f, 0.7f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5f, 0.7f, 1.5f);
	glEnd();
///
/*
	// side tori
	//glColor3f(0.8f, 0.8f, 0.8f);
	//left front
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.5f, -4.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0f, -4.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.0f, -2.0f, 1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5f, -2.0f, 1.5f);
	glEnd();
	// left back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.5f, -4.5f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0f, -4.5f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.0f, -2.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5f, -2.0f, 1.0f);
	glEnd();
	// side right
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.0f, -4.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0f, -4.5f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.0f, -2.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.0f, -2.0f, 1.5f);
	glEnd();
	// side left
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.5f, -4.5f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.5f, -4.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.5f, -2.0f, 1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5f, -2.0f, 1.0f);
	glEnd();
*/
///

	/*-------------------------------------------------------------------*/
	/*-------------------------------------------------------------------*/
	/*--------------------------------------------------------------------*/
	//leftfront 01
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.5f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -4.5f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -3.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -3.4f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// left back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.5f, -3.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -4.5f, -3.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -3.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -3.6f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side right
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.0f, -4.5f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -4.5f, -3.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -3.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -3.5f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side left
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.5f, -3.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.2f, -4.5f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -3.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -3.6f);
	glEnd();
	/*------------------------------------------------------*/
	// upper
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -2.0f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -2.0f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -3.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -3.6f);
	glEnd();
	/*------------------------------------------------------*/



	//leftfront 02
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.5f, -5.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -4.5f, -5.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -5.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -5.4f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// left back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.5f, -5.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -4.5f, -5.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -5.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -5.6f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side right
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.0f, -4.5f, -5.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -4.5f, -5.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -5.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -5.5f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side left
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.5f, -5.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.2f, -4.5f, -5.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -5.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -5.6f);
	glEnd();
	/*------------------------------------------------------*/
	// upper
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -2.0f, -5.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -2.0f, -5.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -5.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -5.6f);
	glEnd();
	/*------------------------------------------------------*/



	//leftfront 03
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -7.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -7.4f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// left back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -7.6f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side right
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.0f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -7.5f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side left
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.2f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -7.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -7.6f);
	glEnd();
	/*------------------------------------------------------*/
	// upper
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -2.0f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -2.0f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.0f, -7.6f);
	glEnd();
	/*------------------------------------------------------*/
	/*------------------------------------------------------*/

	/*--------------------------------------------------------------------*/
	//right front 01
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -4.5f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -4.5f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -3.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -3.4f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// right back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -4.5f, -3.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -4.5f, -3.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -3.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -3.6f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side right
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.0f, -4.5f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -4.5f, -3.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -3.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -3.5f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side left
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -4.5f, -3.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -4.5f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -3.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -3.6f);
	glEnd();
	/*------------------------------------------------------*/
	// upper
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -2.0f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -2.0f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -3.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -3.6f);
	glEnd();
	/*------------------------------------------------------*/



	//right front 02
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -4.5f, -5.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -4.5f, -5.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -5.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -5.4f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// right back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -4.5f, -5.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -4.5f, -5.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -5.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -5.6f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side right
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.0f, -4.5f, -5.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -4.5f, -5.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -5.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -5.5f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side left
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -4.5f, -5.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -4.5f, -5.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -5.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -5.6f);
	glEnd();
	/*------------------------------------------------------*/
	// upper
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -2.0f, -5.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -2.0f, -5.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -5.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -5.6f);
	glEnd();
	/*------------------------------------------------------*/



	//right front 03
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -7.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -7.4f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// right back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -7.6f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side right
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.0f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -7.5f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side left
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -7.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -7.6f);
	glEnd();
	/*------------------------------------------------------*/
	// upper
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -2.0f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -2.0f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.0f, -7.6f);
	glEnd();


	/*------------------------------------------------------*/

	//middle right front
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.2f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.0f, -2.0f, -7.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.2f, -2.0f, -7.4f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// right back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.2f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.2f, -2.0f, -7.6f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side right
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.0f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.0f, -2.0f, -7.5f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side left
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.2f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.2f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.2f, -2.0f, -7.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.2f, -2.0f, -7.6f);
	glEnd();
	/*------------------------------------------------------*/
	// upper
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.2f, -2.0f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, -2.0f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.2f, -2.0f, -7.6f);
	glEnd();

	/*------------------------------------------------------*/

	//middle left front
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.0f, -2.0f, -7.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.2f, -2.0f, -7.4f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// right back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.2f, -2.0f, -7.6f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side right
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.0f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.0f, -2.0f, -7.5f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side left
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.2f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.2f, -2.0f, -7.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.2f, -2.0f, -7.6f);
	glEnd();
	/*------------------------------------------------------*/
	// upper
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, -2.0f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0f, -2.0f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.2f, -2.0f, -7.6f);
	glEnd();
	/*------------------------------------------------------*/

    //middle front
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.2f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, -2.0f, -7.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2f, -2.0f, -7.4f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// right back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.2f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2f, -2.0f, -7.6f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side right
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, -2.0f, -7.5f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side left
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.2f, -4.5f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2f, -4.5f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2f, -2.0f, -7.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2f, -2.0f, -7.6f);
	glEnd();
	/*------------------------------------------------------*/
	// upper
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.2f, -2.0f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, -2.0f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, -2.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2f, -2.0f, -7.6f);
	glEnd();
	/*------------------------------------------------------*/
	/*------------------------------------------------------*/


	/*--------------------------------------------------------*/
	glBegin(GL_QUADS); // left connector 01- up
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -2.5f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -2.5f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.5f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.5f, -7.6f);
	glEnd();
	glBegin(GL_QUADS); // left connector 01- down
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -3.0f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -3.0f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -3.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -3.0f, -7.6f);
	glEnd();
	glBegin(GL_QUADS); // left connector 01- left
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -3.0f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.2f, -3.0f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.2f, -2.5f, -3.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.5f, -7.6f);
	glEnd();
	glBegin(GL_QUADS); // left connector 01- right
	glNormal3f(1.0, .0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.0f, -3.0f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -3.0f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -2.5f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.0f, -2.5f, -3.4f);
	glEnd();
	glBegin(GL_QUADS); // left connector 02- up
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -3.5f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -3.5f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -3.5f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -3.5f, -7.6f);
	glEnd();
	glBegin(GL_QUADS); // left connector 02- down
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.0f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -4.0f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -4.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -4.0f, -7.6f);
	glEnd();
	glBegin(GL_QUADS); // left connector 02- left
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.0f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.2f, -4.0f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.2f, -3.5f, -3.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -3.5f, -7.6f);
	glEnd();
	glBegin(GL_QUADS); // left connector 02- right
	glNormal3f(1.0, .0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.0f, -4.0f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, -4.0f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-5.0f, -3.5f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.0f, -3.5f, -3.4f);
	glEnd();
	/*--------------------------------------------------------*/





	/*--------------------------------------------------------*/
	glBegin(GL_QUADS); // right connector 01- up
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -2.5f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -2.5f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.5f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.5f, -7.6f);
	glEnd();
	glBegin(GL_QUADS); // right connector 01- down
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -3.0f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -3.0f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -3.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -3.0f, -7.6f);
	glEnd();
	glBegin(GL_QUADS); // right connector 01- left
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -3.0f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -3.0f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -2.5f, -3.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -2.5f, -7.6f);
	glEnd();
	glBegin(GL_QUADS); // right connector 01- right
	glNormal3f(1.0, .0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.0f, -3.0f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -3.0f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -2.5f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.0f, -2.5f, -3.4f);
	glEnd();
	glBegin(GL_QUADS); // right connector 02- up
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -3.5f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -3.5f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -3.5f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -3.5f, -7.6f);
	glEnd();
	glBegin(GL_QUADS); // right connector 02- down
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -4.0f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -4.0f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -4.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -4.0f, -7.6f);
	glEnd();
	glBegin(GL_QUADS); // right connector 02- left
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.2f, -4.0f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -4.0f, -3.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -3.5f, -3.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.2f, -3.5f, -7.6f);
	glEnd();
	glBegin(GL_QUADS); // right connector 02- right
	glNormal3f(1.0, .0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(5.0f, -4.0f, -3.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f, -4.0f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, -3.5f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.0f, -3.5f, -3.4f);
	glEnd();
	/*--------------------------------------------------------*/


    /*--------------------------------------------------------*/
	glBegin(GL_QUADS); // back connector 01- front
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -3.0f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -3.0f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -2.5f, -7.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.5f, -7.4f);
	glEnd();

	glBegin(GL_QUADS); // back connector 01- back
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -3.0f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -3.0f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -2.5f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.5f, -7.6f);
	glEnd();

	glBegin(GL_QUADS); // back connector 01- up
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -2.5f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -2.5f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -2.5f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -2.5f, -7.6f);
	glEnd();

	glBegin(GL_QUADS); // back connector 01- down
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -3.0f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -3.0f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -3.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -3.0f, -7.6f);
	glEnd();


	glBegin(GL_QUADS); // back connector 02- front
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.0f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -4.0f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -3.5f, -7.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -3.5f, -7.4f);
	glEnd();

	glBegin(GL_QUADS); // back connector 02- back
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.0f, -7.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -4.0f, -7.6f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -3.5f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -3.5f, -7.6f);
	glEnd();

	glBegin(GL_QUADS); // back connector 01- up
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -3.5f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -3.5f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -3.5f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -3.5f, -7.6f);
	glEnd();

	glBegin(GL_QUADS); // back connector 01- down
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.2f, -4.0f, -7.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.2f, -4.0f, -7.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.2f, -4.0f, -7.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.2f, -4.0f, -7.6f);
	glEnd();

	/*--------------------------------------------------------*/


	/// ///
	/// ...
	glBindTexture(GL_TEXTURE_2D, _textureId_pl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.4f, -4.5f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.0f, -4.5f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-4.0f, -2.0f, -2.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.4f, -2.0f, -2.0f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// left back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.4f, -4.5f, -2.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.0f, -4.5f, -2.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-4.0f, -2.0f, -2.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.4f, -2.0f, -2.4f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side right
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.0f, -4.5f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.0f, -4.5f, -2.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-4.0f, -2.0f, -2.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.0f, -2.0f, -2.0f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side left
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.4f, -4.5f, -2.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.4f, -4.5f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-4.4f, -2.0f, -2.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.4f, -2.0f, -2.4f);
	glEnd();
	/*------------------------------------------------------*/
	// upper
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.4f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.0f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-4.0f, -2.0f, -2.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.4f, -2.0f, -2.4f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.7f, -1.0f, -1.8f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.7f, -1.0f, -1.8f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.7f, -1.0f, -2.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.7f, -1.0f, -2.6f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.4f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.0f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.7f, -1.0f, -1.8f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.7f, -1.0f, -1.8f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.4f, -2.0f, -2.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.0f, -2.0f, -2.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.7f, -1.0f, -2.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.7f, -1.0f, -2.6f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.0f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.0f, -2.0f, -2.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.7f, -1.0f, -2.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.7f, -1.0f, -1.8f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.4f, -2.0f, -2.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.4f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-4.7f, -1.0f, -1.8f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.7f, -1.0f, -2.6f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(1.0, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.7f, -1.0f, -1.8f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.7f, -1.0f, -1.8f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-4.2f, -0.5f, -2.2f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.7f, -1.0f, -2.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.7f, -1.0f, -2.6f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-4.2f, -0.5f, -2.2f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-4.7f, -1.0f, -2.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-4.7f, -1.0f, -1.8f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-4.2f, -0.5f, -2.2f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.7f, -1.0f, -1.8f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.7f, -1.0f, -2.6f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-4.2f, -0.5f, -2.2f);
	glEnd();

	/// ///
	/// ...
	glBindTexture(GL_TEXTURE_2D, _textureId_pl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.4f, -4.5f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.0f, -4.5f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.0f, -2.0f, -2.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.4f, -2.0f, -2.0f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// left back
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.4f, -4.5f, -2.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.0f, -4.5f, -2.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.0f, -2.0f, -2.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.4f, -2.0f, -2.4f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side right
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.0f, -4.5f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.0f, -4.5f, -2.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.0f, -2.0f, -2.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.0f, -2.0f, -2.0f);
	glEnd();
	/*-------------------------------------------------------------------*/
	// side left
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.4f, -4.5f, -2.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.4f, -4.5f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.4f, -2.0f, -2.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.4f, -2.0f, -2.4f);
	glEnd();
	/*------------------------------------------------------*/
	// upper
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.4f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.0f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.0f, -2.0f, -2.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.4f, -2.0f, -2.4f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.7f, -1.0f, -1.8f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.7f, -1.0f, -1.8f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.7f, -1.0f, -2.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.7f, -1.0f, -2.6f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.4f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.0f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.7f, -1.0f, -1.8f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.7f, -1.0f, -1.8f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.4f, -2.0f, -2.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.0f, -2.0f, -2.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.7f, -1.0f, -2.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.7f, -1.0f, -2.6f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.0f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.0f, -2.0f, -2.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.7f, -1.0f, -2.6f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.7f, -1.0f, -1.8f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.4f, -2.0f, -2.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.4f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.7f, -1.0f, -1.8f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(4.7f, -1.0f, -2.6f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(1.0, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.7f, -1.0f, -1.8f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.7f, -1.0f, -1.8f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(4.2f, -0.5f, -2.2f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.7f, -1.0f, -2.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.7f, -1.0f, -2.6f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(4.2f, -0.5f, -2.2f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(4.7f, -1.0f, -2.6f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.7f, -1.0f, -1.8f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(4.2f, -0.5f, -2.2f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.7f, -1.0f, -1.8f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.7f, -1.0f, -2.6f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(4.2f, -0.5f, -2.2f);
	glEnd();







	glBindTexture(GL_TEXTURE_2D, _textureId_sh_b);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//shrine
	//bottom block

	glColor3f(6.0f, 6.0f, 6.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.5f, -4.0f, -3.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.5f, -4.0f, -3.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.5f, -4.0f, -7.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5f, -4.0f, -7.0f);
	glEnd();


	glColor3f(6.0f, 6.0f, 6.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.5f, -4.5f, -3.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.5f, -4.5f, -3.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.5f, -4.0f, -3.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5f, -4.0f, -3.0f);
	glEnd();



	glColor3f(6.0f, 6.0f, 6.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.5f, -4.5f, -7.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.5f, -4.5f, -7.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.5f, -4.0f, -7.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5f, -4.0f, -7.0f);
	glEnd();

	glColor3f(6.0f, 6.0f, 6.0f);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.5f, -4.5f, -7.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.5f, -4.5f, -3.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.5f, -4.0f, -3.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5f, -4.0f, -7.0f);
	glEnd();



    glColor3f(6.0f, 6.0f, 6.0f);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.5f, -4.5f, -7.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.5f, -4.5f, -3.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.5f, -4.0f, -3.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.5f, -4.0f, -7.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureId_wl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glColor3f(0.4f, 0.5f, 0.7f);

    /*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(0.0, .0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, -4.0f, -3.3f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.9f, -4.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.9f, -3.0f, -3.3f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.2f, -3.0f, -3.3f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, -4.0f, -4.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.2f, -4.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.2f, -3.0f, -3.3f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.2f, -3.0f, -4.2f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.9f, -4.0f, -4.2f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.9f, -4.0f, -3.3f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.9f, -3.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.9f, -3.0f, -4.2f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, -3.0f, -3.3f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.9f, -3.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.9f, -3.0f, -4.2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.2f, -3.0f, -4.2f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.9f, -4.0f, -3.3f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -4.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -3.0f, -3.3f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.9f, -3.0f, -3.3f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.9f, -4.0f, -3.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -4.0f, -3.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -3.0f, -3.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.9f, -3.0f, -3.5f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.9f, -3.0f, -3.3f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -3.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -3.0f, -3.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.9f, -3.0f, -3.5f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -3.0f, -3.3f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -4.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -4.0f, -3.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -3.0f, -3.5f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/

	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(0.0, .0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.2f, -4.0f, -3.3f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.9f, -4.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.9f, -3.0f, -3.3f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.2f, -3.0f, -3.3f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.2f, -4.0f, -4.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.2f, -4.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.2f, -3.0f, -3.3f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.2f, -3.0f, -4.2f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.9f, -4.0f, -4.2f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.9f, -4.0f, -3.3f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.9f, -3.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.9f, -3.0f, -4.2f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.2f, -3.0f, -3.3f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.9f, -3.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.9f, -3.0f, -4.2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.2f, -3.0f, -4.2f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.9f, -4.0f, -3.3f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -4.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -3.0f, -3.3f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.9f, -3.0f, -3.3f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.9f, -4.0f, -3.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -4.0f, -3.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -3.0f, -3.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.9f, -3.0f, -3.5f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.9f, -3.0f, -3.3f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -3.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -3.0f, -3.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.9f, -3.0f, -3.5f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -3.0f, -3.3f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -4.0f, -3.3f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -4.0f, -3.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -3.0f, -3.5f);
	glEnd();
	/*/*//*/*//*/*//*/*/
	/*/*//*/*//*/*//*/*/



	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, -4.0f, -4.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.2f, -4.0f, -4.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.2f, -0.5f, -4.2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.2f, -0.5f, -4.2f);
	glEnd();


	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, -0.5f, -4.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.2f, -0.5f, -4.2f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.0f, 0.4f, -4.2f);
	glEnd();


	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, -4.0f, -6.8f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.2f, -4.0f, -6.8f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.2f, -0.5f, -6.8f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.2f, -0.5f, -6.8f);
	glEnd();


	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, -0.5f, -6.8f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.2f, -0.5f, -6.8f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.0f, 0.4f, -6.8f);
	glEnd();


	glColor3f(2.0f, 2.0f, 2.0f);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.2f, -4.0f, -4.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.2f, -4.0f, -6.8f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.2f, -0.5f, -6.8f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.2f, -0.5f, -4.2f);
	glEnd();

	glColor3f(2.0f, 2.0f, 2.0f);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.2f, -4.0f, -4.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.2f, -4.0f, -6.8f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-3.2f, -0.5f, -6.8f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.2f, -0.5f, -4.2f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureId_roof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(2.0f, 2.0f, 2.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.4f, -3.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.4f, -6.8f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.5f, -.6f, -6.8f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(3.5f, -.6f, -3.0f);
	glEnd();

	glColor3f(2.0f, 2.0f, 2.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.4f, -3.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.4f, -6.8f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.5f, -.6f, -6.8f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.5f, -.6f, -3.0f);
	glEnd();


	//door

	glBindTexture(GL_TEXTURE_2D, _textureId_door);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(2.0f, 2.0f, 2.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -4.0f, -4.19f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -4.0f, -4.19f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -4.19f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -4.19f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureId_window);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	// window right
	glColor3f(2.0f, 2.0f, 2.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.7f, -1.5f, -4.19f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5f, -1.5f, -4.19f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.5f, -0.8f, -4.19f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.7f, -0.8f, -4.19f);
	glEnd();

	// window left
	glColor3f(2.0f, 2.0f, 2.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.7f, -1.5f, -4.19f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.5f, -1.5f, -4.19f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.5f, -0.8f, -4.19f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.7f, -0.8f, -4.19f);
	glEnd();


	//glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-_ang, 0.0f, 1.0f, 0.0f);
	glScalef(_sca, _sca, _sca);

	for(int i = 0; i < 2; i++) {

		glPushMatrix();
		glRotatef(90 * i, 0, 1, 0);
		glTranslatef(0, 5, 2.0f / _sca);
		t3dDraw3D(STRS[i], 0, 0, 0.1f);
		glPopMatrix();
	}





	glutSwapBuffers();
}

/*-----------------------------*/
void timer(int value) {
/*
    if(timer_flag == 1)
    {
        angle += 1.0f;
        if (angle > 360)
        {
            angle -= 360;
        }

    }
    else
    {

    }

*/
	glutPostRedisplay();
	glutTimerFunc(25, timer, 0);
}

/*-----------------------------*/
void update(int value) {
	_ang += 1.5f;
	if (_ang > 360) {
		_ang -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 600);

	R = 1.0; G = 0.8; B = 0.5;

	glutCreateWindow("Shinto Shrine");
	initRendering();

	_sca = computeScale(STRS);

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutSpecialFunc(keyboardkey);
	cout<<angle<<endl;
	timer(0);

	glutTimerFunc(25, update, 0);

	glutMainLoop();
	return 0;
}
