#include "functions.h"

static int window_width = 0;
static int window_height = 0;

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}

void on_reshape(int width, int height)
{
    window_width = width;
    window_height = height;
}

void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, window_width, window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            60,
            window_width/(float)window_height,
            0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            0.5, 2, 3,
            0, 0, 0,
            0, 1, 0
        );

	glColor3f (0, 1, 0);
	glBegin(GL_POLYGON);
		glVertex3f (-4, 0.2, 3);
		glVertex3f (4, 0.2, 3);
		glVertex3f (4, 0.2, 0.5);
		glVertex3f (-4, 0.2, 0.5);
	glEnd();

	glColor3f (0.3, 0.3, 0.3);
	glBegin(GL_POLYGON);
		glVertex3f (-6, 0, 0.5);
		glVertex3f (6, 0, 0.5);
		glVertex3f (6, 0, -1);
		glVertex3f (-6, 0, -1);
	glEnd();

	glColor3f (1, 1, 1);
	glLineStipple(7, 0x000F); 
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
		glVertex3f(-5,0.1,-0.23);
		glVertex3f(5,0.1,-0.23);
	glEnd();
	
    glutSwapBuffers();
}
