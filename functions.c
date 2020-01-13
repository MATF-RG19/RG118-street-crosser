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
float car_par = -16;
float car_par1 = 7;
int count = 0;
float z = 3;
int tmp = 0;
int tmp_par = 0;
int tmp_rot = 0;
int scale_par = 0;
int niz[ROAD_LENGTH];
int animation_ongoing = 0;
float water_par = 0;

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'w':
		/*animation_parameter += 0.75;*/
		if(z_parameter < 149.997087){
			if (!animation_ongoing) {
			 	
				animation_ongoing = 1;
				tmp_par = 0;
				scale_par = 0;
				translate_par = 0;
				rotation_parameter = 1;
				glutTimerFunc(TIMER_INTERVAL, on_timer, 0);
			   	
			}	
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
	if(id == 0 && tmp_par >= 15){
    	z_parameter += 0.075;
    }
    
    if(id == 1 && tmp_par >= 15){
    	z_parameter -= 0.075;
    }
    
    if(tmp_par >= 14){
    	translate_par += 1.42857143;
    }
    
    if(id == 0 || id == 1){
    	tmp_par += 1;
		scale_par += 2.85714286;
    }
	
	if(scale_par >= 35){
		scale_par = 35;
	}
	
	if(tmp_par == 35){
		animation_ongoing = 0; 
		curr_rotation = rotation_parameter;
	}

    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, id);
    }
    
}

static void on_timer_x(int id)
{
    
    if(id == 0 && tmp_par >= 15 && x_parameter < 4.5){
    	x_parameter += 0.075;
    }
    
    if(id == 1 && tmp_par >= 15 && x_parameter > -3){
    	x_parameter -= 0.075;
    }
    
    if(tmp_par >= 14){
    	translate_par += 1.42857143;
    }
    
    if(id == 0 || id == 1){
    	tmp_par += 1;
		scale_par += 2.85714286;
    }
	
	if(scale_par >= 35){
		scale_par = 35;
	}
	
	if(tmp_par == 35){
		animation_ongoing = 0;
		curr_rotation = rotation_parameter; 
	}

    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer_x, id);
    }
}

static void on_timer_car(int id){
	if(id == 0){
		car_par += 0.09;
		car_par1 += 0.07;
		water_par += 0.01;
	}

	if((int)car_par == 7){
		car_par = -10;
	}
	
	if((int)car_par1 == 10){
		car_par1 = -7;
	}
	
	glutPostRedisplay();

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
            1+0.4, 7, 5-z_parameter,  /*0.5 2 3*/
            -2+0.4, 0, -4-z_parameter,
            0, 1, 0
        );
        
    glutTimerFunc(TIMER_INTERVAL, on_timer_car, 0);

    
    
    z = 4.5;
    
    
    draw_break();
	draw_break();
    draw_break();
	draw_break();
	
   	determine_obstacle_layout();
   	
   	glPushMatrix();
    	draw_character();
	glPopMatrix();
    
	
    glutSwapBuffers();
}

void determine_obstacle_layout(){
	int i;
    srand(time(NULL));    
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
    		if((niz[i-1] == 2 || niz[i-2] == 2 ||
    			niz[i-1] == 3 || niz[i-4] == 2) && niz[i] == 2)
    				niz[i] = rand()%2;
    		
    	}
    	niz[ROAD_LENGTH-1] = 0;
   	}
   	tmp++;
    
    
    for(i = 0; i < ROAD_LENGTH; i++){
    	if(niz[i] == 0)
    		draw_break();
    	else if(niz[i] == 1){
    		if(i%2 == 1){
    			if(i%4==1)
    				draw_road_d1();
    			else
    				draw_road_d2();
    		}
    		else{
    			if(i%4==0)
    				draw_road_l1(niz[i-1], niz[i+1]);
    			else
    				draw_road_l2(niz[i-1], niz[i+1]);
    			
    		}	
    	}
    	else
    		draw_water();
    }
}

void draw_road_d1(){

	glPushMatrix();
		glColor3f (0.2, 0.2, 0.2);
		glTranslatef(0, 0, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();
	
	
	glPushMatrix();
		glColor3f(0.36, 0.2, 0.09);
		glTranslatef(car_par, 0.1, z);
		glScalef(3, 0.2, 0.75);
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

void draw_road_l1(int x, int y){

	glPushMatrix();
		if(x != 1 && x == y)
			glColor3f (0.2, 0.2, 0.2);
		else
			glColor3f (0.25, 0.25, 0.25);
		glTranslatef(0, 0, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();
	
	
	glPushMatrix();
		glColor3f(0.36, 0.2, 0.09);
		glTranslatef(-car_par1, 0.1, z);
		glScalef(3, 0.2, 0.75);
		glutSolidCube(1);
	glPopMatrix();
	
	
	z -= 1.5;
}

void draw_road_d2(){

	glPushMatrix();
		glColor3f (0.2, 0.2, 0.2);
		glTranslatef(0, 0, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();
	
	
	glPushMatrix();
		glColor3f(0.36, 0.2, 0.09);
		glTranslatef(1*car_par, 0.1, z);
		glScalef(3, 0.2, 0.75);
		glutSolidCube(1);
	glPopMatrix();
	
	
	z -= 1.5;
}

void draw_road_l2(int x, int y){

	glPushMatrix();
		if(x != 1 && x == y)
			glColor3f (0.2, 0.2, 0.2);
		else
			glColor3f (0.25, 0.25, 0.25);
		glTranslatef(0, 0, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();
	
	
	glPushMatrix();
		glColor3f(0.36, 0.2, 0.09);
		glTranslatef(-car_par1, 0.1, z);
		glScalef(3, 0.2, 0.75);
		glutSolidCube(1);
	glPopMatrix();
	
	
	z -= 1.5;
}

void draw_break(){
	srand(z);
	
	glPushMatrix();
		glColor3f (0.2, 0.6, 0.2);
		glTranslatef(0, 0.1, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();
	
	float array[8] = {-7.5, -6, -4.5, -3, -1.5, 1.5, 3, 4.5};
	
	int i = 0;
	
	for(i = 0; i < 8; i++){
		if(rand()%2 == 1){
			glPushMatrix();
				glTranslatef(array[i], 0.6, z);
				int r = rand()%3;
				if(r == 1)
					draw_tree_1();
				else if(r == 2)
					draw_tree_2();
				else{
					glScalef(0.8, 0.7, 0.8);	
					draw_stone();
				}
			glPopMatrix();
		}
	}
	
	
	
	z -= 1.5;
}

void draw_water(){
	
	glPushMatrix();
		glColor3f (0.1, 0.74, 0.8);
		glTranslatef(0, 0, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.36, 0.2, 0.09);
		glTranslatef(-3.5*sin(water_par), 0.1, z);
		glScalef(3, 0.2, 0.75);
		glutSolidCube(1);
	glPopMatrix();

	
	z -= 1.5;

}

void draw_character(){

	glPushMatrix();
	glTranslatef(0,0+sin(PI*translate_par/30),0);
    glTranslatef(0+x_parameter,0.8-0.35*sin(PI*scale_par/35),1.5-z_parameter);
 			
    		if(rotation_parameter != curr_rotation){
    			if(curr_rotation == 1)
    				glRotatef(90, 0, 1, 0);
    			if(curr_rotation == 3)
    				glRotatef(-90, 0, 1, 0);
    			if(curr_rotation == 4)
    				glRotatef(180, 0, 1, 0);
    			if((rotation_parameter == 1 && curr_rotation == 4) || 
    			   (rotation_parameter == 4 && curr_rotation == 3) ||
    			   (rotation_parameter == 3 && curr_rotation == 2) || 
    			   (rotation_parameter == 2 && curr_rotation == 1)){
    			   
    			    glRotatef(-90*tmp_par/35, 0, 1, 0);
    			    
    			   	
    			}
    			if((rotation_parameter == 1 && curr_rotation == 3) ||
    			   (rotation_parameter == 4 && curr_rotation == 2) || 
    			   (rotation_parameter == 3 && curr_rotation == 1)){
    			   	
    			    glRotatef(180*tmp_par/35, 0, 1, 0);
    			    
					
    			}
    			
    			if(rotation_parameter == 2 && curr_rotation == 4){
    				glRotatef(-180*tmp_par/35, 0, 1, 0);
    			}
    			
    			if((rotation_parameter == 3 && curr_rotation == 4) || 
    			   (rotation_parameter == 2 && curr_rotation == 3) ||
    			   (rotation_parameter == 1 && curr_rotation == 2) || 
    			   (rotation_parameter == 4 && curr_rotation == 1)){
    			   	
    			   	glRotatef(90*tmp_par/35, 0, 1, 0);
    			   	
    			}
    		}

		else{
			if(curr_rotation == 1)
    				glRotatef(90, 0, 1, 0);
    		if(curr_rotation == 3)
    				glRotatef(-90, 0, 1, 0);
    		if(curr_rotation == 4)
    				glRotatef(180	, 0, 1, 0);
		
		}
    	glScalef(0.7, 0.7-0.35*sin(PI*scale_par/35), 0.75+0.15*sin(PI*scale_par/35));

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

	glPopMatrix();

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

void draw_tree_1(){

	glPushMatrix();
    	glColor3f(0.32, 0.44, 0.21);
		glTranslatef(0, 0.5-0.2 + 0.19, 0);
		glScalef(1 - 0.26, 1 - 0.4 + 0.37, 1 - 0.26); 
    	glutSolidCube(1);
  	glPopMatrix();
  	glPushMatrix();
  		glColor3f(0.36, 0.2, 0.09);
		glTranslatef( 0, -0.24, 0);
		glScalef(1 - 0.62, 1 - 0.52, 1 - 0.59);
		glutSolidCube(1);
	glPopMatrix();

}

void draw_tree_2(){

	glPushMatrix();
    	glColor3f(0.32, 0.44, 0.21);
		glTranslatef(0, 0.5-0.2-0.2 + 0.19, 0);
		glScalef(1 - 0.26, 1 - 0.4 + 0.37-0.1-0.3, 1 - 0.26); 
    	glutSolidCube(1);
  	glPopMatrix();
  	glPushMatrix();
  		glColor3f(0.36, 0.2, 0.09);
		glTranslatef( 0, -0.24, 0);
		glScalef(1 - 0.62, 1 - 0.52, 1 - 0.59);
		glutSolidCube(1);
	glPopMatrix();

}

void draw_stone(){

	glPushMatrix();
    	glColor3f(0.4, 0.4, 0.4);
		glTranslatef( 0, 0, 0);
		glScalef(1 - 0.1, 1 - 0.25, 1 - 0.1);
    	glutSolidCube(1);
  	glPopMatrix();
  	glPushMatrix();
  		glColor3f(0.4, 0.4, 0.4);
		glTranslatef( -0.07 - 0.09, -0.09, 0.08);
		glScalef(1 + 0.05 - 0.2, 1 -0.43, 1 + 0.04);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
  		glColor3f(0.4, 0.4, 0.4);
		glTranslatef( -0.17, 0.43, 0);
		glScalef(1 - 0.43, 1 - 0.879999, 1 - 0.71);
		glutSolidCube(1);
	glPopMatrix();
	
		

}






