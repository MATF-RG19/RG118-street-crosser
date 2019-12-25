#include "functions.h"

#define ROAD_LENGTH 100

static int window_width = 0;
static int window_height = 0;
float animation_parameter = 0;
float z = 3;
int tmp = 0;
int niz[ROAD_LENGTH];

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'w':
		animation_parameter += 0.75;
		glutPostRedisplay();
		break;
	 case 's':
		animation_parameter -= 0.75;
		glutPostRedisplay();
		break;
	case 'r':
		animation_parameter = 0;
		tmp = 0;
		glutPostRedisplay();
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
            0.5, 3, 3-animation_parameter,  /*0.5 2 3*/
            0, 0, 0-animation_parameter,
            0, 1, 0
        );
        
    srand(time(NULL));
    
    z = 3;
    
    draw_break();
	draw_break();
	
   	determine_obstacle_layout();
   	
   	draw_character();
    
	
    glutSwapBuffers();
}

void determine_obstacle_layout(){
	int i;
    
    if(tmp == 0){
    	for(i = 0; i < ROAD_LENGTH; i++){
    		niz[i] = rand()%3;
    		if(i > 2){
    			if(niz[i-1] == niz[i-2] && niz[i-1] == 1)
    				niz[i] = 0;
    			if(niz[i-1] == niz[i-2] && niz[i-1] == 0)
    				niz[i] = 1;
    			if(niz[i-1] == 2)
    				niz[i] = 0;
    			if(niz[i-1] == 1 && niz[i] == 2)
    				niz[i] = rand()%2;
    			if(niz[i-1] == 2 && niz[i] == 1)
    				niz[i] = 0;
    		}
    	}
    	
    	for(i = 0; i < ROAD_LENGTH; i++){
    		if(niz[i-1] == 2)
    				niz[i] = 0;
    		if(niz[i-1] == 1 && niz[i] == 2)
    				niz[i] = rand()%2;
    		
    	}
    	niz[ROAD_LENGTH-1] = 0;	
   	}
   	tmp++;
    
    for(i = 0; i < ROAD_LENGTH; i++){
    	
    	if(niz[i] == 0)
    		draw_break();
    	else if(niz[i] == 1)
    		draw_road();
    	else
    		draw_water();
    }
}

void draw_road(){

	glPushMatrix();
		glColor3f (0.2, 0.2, 0.2);
		glTranslatef(0, 0, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();
	
	/*glPushMatrix();
		glColor3f (1, 1, 1);
		glLineStipple(7, 0x000F); 
		glEnable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
			glVertex3f(-5,0.1, z);
			glVertex3f(5,0.1, z);
		glEnd();
	glPopMatrix();*/
	
	z -= 1.5;
}

void draw_break(){
	
	glPushMatrix();
		glColor3f (0.2, 0.6, 0.2);
		glTranslatef(0, 0.1, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();

	
	z -= 1.5;
}

void draw_water(){
	
	glPushMatrix();
		glColor3f (0.1, 0.74, 0.8);
		glTranslatef(0, 0, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();

	
	z -= 1.5;

}

void draw_character(){
	
	glPushMatrix();
		glColor3f (0, 0, 0);
		glTranslatef(0, 0.35, 0.75+0.375-animation_parameter);
		glutSolidCube(0.3);
	glPopMatrix();

}






