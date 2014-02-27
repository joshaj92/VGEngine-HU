#include <stdio.h>
#include <stdlib.h>
#include<iostream>
//#include <Xil/Xlib.h>
//#include <Xil/Xutil.h>
//#include <Xil/Xos.h>
//#include <Xil/Xator.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glx.h>

HDC hDC = GetDC( hWnd );
Display #dpy;
XWindowAttributes winattr;
Window win;
#define RESL 0.05;

float transX = 0.0f;
float transY = 0.0f;
float transZ = 0.0f;
float rotX = 0.0f;
float rotY = 0.0f;
float rotZ = 0.0f;
void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);
void Initialize();
void display();
void Shoot();
void CamKeys(unsigned char);

void initialize()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
	glEnable (GL_LINE_SMOOTH);
	glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
}
void display()
{
	glClear (GL_COLOR_BUFFER_BIT);				
	glPushMatrix();								
	glRotatef(rotX,1.0,0.0,0.0);				
	glRotatef(rotY,0.0,1.0,0.0);				
	glRotatef(rotZ,0.0,0.0,1.0);				
	glTranslatef(transX, transY, transZ);						

	// Draw the positive side of the lines x,y,z
	glBegin(GL_LINES);
		glColor3f (0.0, 1.0, 0.0);			// Green for x axis
		glVertex3f(0,0,0);
		glVertex3f(10,0,0);
		glColor3f(1.0,0.0,0.0);				// Red for y axis
		glVertex3f(0,0,0);
		glVertex3f(0,10,0);
		glColor3f(0.0,0.0,1.0);				// Blue for z axis
		glVertex3f(0,0,0);	
		glVertex3f(0,0,10);
	glEnd();
	
	// Dotted lines for the negative sides of x,y,z
	glEnable(GL_LINE_STIPPLE);				// Enable line stipple to use a dotted pattern for the lines
	glLineStipple(5, 0x0101);				// Dotted stipple pattern for the lines
	glBegin(GL_LINES);				
		glColor3f (0.0, 1.0, 0.0);			// Green for x axis
		glVertex3f(-10,0,0);
		glVertex3f(0,0,0);
		glColor3f(1.0,0.0,0.0);				// Red for y axis
		glVertex3f(0,0,0);
		glVertex3f(0,-10,0);
		glColor3f(0.0,0.0,1.0);				// Blue for z axis
		glVertex3f(0,0,0);
		glVertex3f(0,0,-10);
	glEnd();

	glDisable(GL_LINE_STIPPLE);				
	glPopMatrix();
	glSwapBuffer(dpy,win);
	usleep(5000);							
}
void Shoot()
{
	float zz = z;
	XGetWindowAttributes(dpy, win, &winattr);
	glViewport (0, 0, winattr, width, winattr, height);
	glClearColor (0.5f, 0.5f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);				
	glPushMatrix();								
	glBegin(GL_QUADS);
		glColor3f(1.0, 0.0, 0.0);
	glEnd();
	while (zz > 0)
	{
		zz = zz - 0.2;
		glTranslate(0.0, 0.0, zz, 0.0);
		gluperspective(75, 0.0, 0.10, -zz);
	}
	
	glPopMatrix();
	glSwapBuffer(dpy,win);
}
void CamKeys (unsigned char key)
{
    switch(key) 
	{
		case 'a' :    // Rotate on x axis
			rotX -= 0.5f;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt (rotX, Y, 10.0 + Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
          break;
        case 'd' :	// Rotate on x axis (opposite)
			rotX +=  0.5f;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt (rotX, rotY, 10.0 + rotZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
          break;
        case 'w' :		// Rotate on y axis 
			rotY += 0.5f;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt (rotX, rotY, 10.0 + rotZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
          break;
        case 's' :	// Rotate on y axis (opposite)
			rotY -= 0.5f;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt (rotX, rotY, 10.0 + rotZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
          break;	
		case 'e':  // Roatae on z axis
			rotZ -= 0.5f;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt (rotX, rotY, 10.0 + rotZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		  break;
		case 'q':// Roatae on z axis (opposite)
			rotZ += 0.5f;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt (rotX, rotY, 10.0 + rotZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		  break;
		case 'j':
			Shoot();
			break;
    }
}

int main (int argc, char** argv)
{
	EnableOpenGL(hWnd, hDC, hRC);
	initialize();
	display();
	unsigned char key = 'x';
	while (key != 'z')
	{
		cin >> key;
		CamKeys(key);
	}
	cout << "First Person Shooter ended." << endl;
	DisableOpenGL(hWnd, hDC, hRC);
	return 0;
}

void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    // get the device context (DC)
    *hDC = GetDC( hWnd );

    // set the pixel format for the DC
    ZeroMemory( &pfd, sizeof( pfd ) );
    pfd.nSize = sizeof( pfd );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                  PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat( *hDC, &pfd );
    SetPixelFormat( *hDC, iFormat, &pfd );

    // create and enable the render context (RC)
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );
}
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent( NULL, NULL );
    wglDeleteContext( hRC );
    ReleaseDC( hWnd, hDC );
}
