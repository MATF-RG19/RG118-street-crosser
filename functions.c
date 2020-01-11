#include "functions.h"

#define ROAD_LENGTH 100
#define TIMER_INTERVAL 1
#define PI 3.14

static int window_width = 0;
static int window_height = 0;
float z_parameter = 0;
float x_parameter = 0;
float camera_par = 0;
float translate_par = 0;
float rotation_parameter = 0;
float curr_rotation = 2;
float z = 3;
int tmp = 0;
int tmp_par = 0;
int scale_par = 0;
int niz[ROAD_LENGTH];
int animation_ongoing = 0;

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'w':
		/*animation_parameter += 0.75;*/
		if (!animation_ongoing) {
            animation_ongoing = 1;
            tmp_par = 0;
            scale_par = 0;
            translate_par = 0;
            rotation_parameter = 1;
            glutTimerFunc(TIMER_INTERVAL, on_timer, 0);
        }
        glutPostRedisplay();
		break;
	 case 's':
	 	if(z_parameter > -0.01){
			if (!animation_ongoing) {
		        animation_ongoing = 1;
		        tmp_par = 0;
		        scale_par = 0;
		        translate_par = 0;
		        rotation_parameter = 3;
		        glutTimerFunc(TIMER_INTERVAL, on_timer, 1);
		    }
		}
		glutPostRedisplay();
		break;
	case 'd':
			if (!animation_ongoing) {
		        animation_ongoing = 1;
		        tmp_par = 0;
		        scale_par = 0;
		        translate_par = 0;
		        rotation_parameter = 2;
		        glutTimerFunc(TIMER_INTERVAL, on_timer_x, 0);
		    }
		glutPostRedisplay();
		break;
	case 'a':
			if (!animation_ongoing) {
		        animation_ongoing = 1;
		        tmp_par = 0;
		        scale_par = 0;
		        translate_par = 0;
		        rotation_parameter = 4;
		        glutTimerFunc(TIMER_INTERVAL, on_timer_x, 1);
		    }
		glutPostRedisplay();
		break;
	case 't':
	 	camera_par += 0.1;
		glutPostRedisplay();
		break;
	case 'r':
		z_parameter = 0;
		tmp = 0;
		glutPostRedisplay();
		break;
	}    
}

static void on_timer(int id)
{
	if(id == 0 && tmp_par >= 25){
    	z_parameter += 0.06;
    	
    }
    if(id == 1 && tmp_par >= 25){
    	z_parameter -= 0.06;
    }
    
    if(tmp_par >= 20){
    	translate_par += 1;
    }
    
    if(id == 0 || id == 1){
    	tmp_par += 1;
		scale_par += 2;
    }
	
	if(scale_par >= 50){
		scale_par = 50;
	}
	
	if(tmp_par == 50){
		animation_ongoing = 0;
	}

    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, id);
    }
}

static void on_timer_x(int id)
{
    
    if(id == 0 && tmp_par >= 25 && x_parameter < 4.5){
    	x_parameter += 0.06;
    }
    
    if(id == 1 && tmp_par >= 25 && x_parameter > -3){
    	x_parameter -= 0.06;
    }
    
    if(tmp_par >= 20){
    	translate_par += 1;
    }
    
    if(id == 0 || id == 1){
    	tmp_par += 1;
		scale_par += 2;
    }
	
	if(scale_par >= 50){
		scale_par = 50;
	}
	
	if(tmp_par == 50){
		animation_ongoing = 0;
	}

    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer_x, id);
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
    /*gluPerspective(
            60,
            window_width/(float)window_height,
            0.1, 100);*/
    
    glOrtho(-5, 5, -5, 5, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            1, 10-camera_par, 5-z_parameter,  /*0.5 2 3*/
            0, 0, -4-z_parameter,
            0, 1, 0
        );
        
    srand(time(NULL));
    
    z = 4.5;
    
    draw_break();
	draw_break();
    draw_break();
	draw_break();
	
   	determine_obstacle_layout();
   	
   	glPushMatrix();
    	
    	glTranslatef(0,0+sin(PI*translate_par/30),0);
    	glTranslatef(0+x_parameter,0.8-0.35*sin(PI*scale_par/50),1.5-z_parameter);
 
    		if(rotation_parameter != curr_rotation){
    			if((rotation_parameter == 1 && curr_rotation == 4) || (rotation_parameter == 4 && curr_rotation == 3) ||
    			   (rotation_parameter == 3 && curr_rotation == 2) || (rotation_parameter == 2 && curr_rotation == 1))
    			   glRotatef(-90, 0, 1, 0);
    			else if((rotation_parameter == 2 && curr_rotation == 4) || (rotation_parameter == 1 && curr_rotation == 3) ||
    			   (rotation_parameter == 4 && curr_rotation == 2) || (rotation_parameter == 3 && curr_rotation == 1))
    			   glRotatef(180, 0, 1, 0);
    			else if((rotation_parameter == 3 && curr_rotation == 4) || (rotation_parameter == 2 && curr_rotation == 3) ||
    			   (rotation_parameter == 1 && curr_rotation == 2) || (rotation_parameter == 4 && curr_rotation == 1))
    			   glRotatef(90, 0, 1, 0);
    		}
    		

    	glScalef(0.7, 0.7-0.35*sin(PI*scale_par/50), 0.65+0.15*sin(PI*scale_par/50));
    	draw_character();
	glPopMatrix();
    
	
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

	glPushMatrix(); /*telo*/
		glColor3f(0,0,0);
		glScalef(1, 1-0.2, 1 -0.2);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*kosa*/
		glColor3f(0,0,0);
		glTranslatef( 0.65, 0.4-0.05, 0);
		glScalef(1 - 0.69, 1 - 0.909999, 1 - 0.68);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*gornji deo glave*/
		glColor3f(0.5,0.5,0.5);
		glTranslatef( 0.74, 0.21, 0);
		glScalef(1 - 0.52, 1 - 0.7 - 0.1, 1 - 0.56);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*glava usta*/
		glColor3f(0.5,0.5,0.5);
		glTranslatef( 0.74-0.07, 0.21-0.12, 0);
		glScalef(1 - 0.52, 0.05, 1 - 0.56);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*glava brada*/
		glColor3f(0.5,0.5,0.5);
		glTranslatef( 0.74-0.02, 0.21-0.17, 0);
		glScalef(1 - 0.52-0.02, 0.05, 1 - 0.56);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*zubi*/
		glColor3f(0.8,0.8,0.8);
		glTranslatef( 0.72+0.2, 0.04+0.05, 0);
		glScalef(1 - 0.50-0.46, 0.05, 1 - 0.56-0.08);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*desno oko beonjaca*/
		glColor3f(0.9,0.9,0.9);
		glTranslatef( 0.69, 0.2, 0.25);
		glScalef(1 - 0.849999, 1 - 0.849999, 1 - 0.949999);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*desno oko zenica*/
		glColor3f(0,0,0);
		glTranslatef( 0.69, 0.2, 0.26);
		glScalef(1 - 0.949999, 1 - 0.949999, 1 - 0.949999);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*levo oko beonjaca*/
		glColor3f(0.9,0.9,0.9);
		glTranslatef( 0.69, 0.2, -0.25);
		glScalef(1 - 0.849999, 1 - 0.849999, 1 - 0.949999);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*levo oko zenica*/
		glColor3f(0,0,0);
		glTranslatef( 0.69, 0.2, -0.26);
		glScalef(1 - 0.949999, 1 - 0.949999, 1 - 0.949999);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*desno uvo*/
		glColor3f(0.5,0.5,0.5);
		glTranslatef( 0.54, 0.12, -0.25);
		glScalef(1 - 0.909999, 1 - 0.68, 1 - 0.949999);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*levo uvo*/
		glColor3f(0.5,0.5,0.5);
		glTranslatef( 0.54, 0.12, 0.25);
		glScalef(1 - 0.909999, 1 - 0.68, 1 - 0.949999);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef( 0.29, -0.43, 0.22);
		draw_leg();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef( 0.29, -0.43, -0.22);
		draw_leg();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef( -0.29, -0.43, 0.22);
		draw_leg();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef( -0.29, -0.43, -0.22);
		draw_leg();
	glPopMatrix();
	
	glPushMatrix(); /*rep*/
		glColor3f(0.5,0.5,0.5);
		glTranslatef( -0.54, -0.34, 0);
		glScalef(1 - 0.919999, 1 - 0.5, 1 - 0.889999);
		
		glutSolidCube(1);
	glPopMatrix();
	/*glPushMatrix();
		glColor3f(0.5,0.5,0.5);
		glTranslatef( x_par, y_par, z_par);
		glScalef(1 + x_scale_par, 1 + y_scale_par, 1 + z_scale_par);
		
		glutSolidCube(1);
	glPopMatrix();*/



}

void draw_leg(){
	
	glPushMatrix();
		glColor3f(0.5,0.5,0.5);
		
		glScalef(1 - 0.73, 1 - 0.939999, 1 - 0.73);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
	
		glTranslatef( 0, -0.27, 0);
		glColor3f(0.5,0.5,0.5);
		
		glScalef(0.2 - 0.08, 0.6, 0.2 - 0.08);
		
		glutSolidCube(1);
	glPopMatrix();


}






