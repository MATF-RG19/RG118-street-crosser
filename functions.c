#include "functions.h"
#include "gameover.h"

#define ROAD_LENGTH 100
#define TIMER_INTERVAL 1
#define PI 3.1415926535897

static int window_width = 0;
static int window_height = 0;
double z_parameter = 1.5;		/*kretanje karaktera i kamere unapred*/
double x_parameter = 0;			/*kretanje karaktera levo-desno*/
double translate_par = 0;		/*animacija skoka*/
int scale_par = 0;				/*animacija skoka*/
double rotation_parameter = 0;	/*animacija rotacije karaktera*/
double curr_rotation = 2;		/*animacija rotacije karaktera*/
double car_par = -10;			/*kretanje automobila vecom brzinom*/
double car_par1 = 8;			/*kretanje automobila sa manjom brzinom*/
double sink_par = 0;			/*animacija utapanja*/
double z = 4.5;					/*za iscrtavanje prepreka i odmaralista*/
int animation_par = 0;			/*glavni parametar skoka i pomeraja karaktera*/
int animation_ongoing = 0;		/*provera da li je animacija u toku*/
double island_par = 0;			/*animacija kretanja ostrvca na vodi*/
int check = 0;					/*za proveru postojanja prepreke*/
int count = 1;					/*brojac koliko je karakter otisao unapred*/
int count1 = 1;					/*kao count samo se uvecava po zavrsetku animacije
								  zbog provere da li je karakter skocio u vodu*/
int count_x = 5;				/*brojac koliko je karakter otisao levo-desno*/
int start_of_game = 0;			/*provera da li je prvo pokretanje igrice*/
int end_of_game = 0;			/*signal za kraj igrice*/
double obstacle[150][9];		/*sadrzi raspored drveca i kamenja*/
int terrain[ROAD_LENGTH];		/*niz koji sadrzi raspored puteva, vode, 	
								  odmaralista*/
int half_jump = 0;

void on_keyboard(unsigned char key, int x, int y)
{
	int i,j;
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'w':
    case 'W':
    
		if(z_parameter < 149.997087 && end_of_game == 0){
			if (!animation_ongoing) {
			 	
			 	check = obstacle_check('w');
				animation_ongoing = 1;
				animation_par = 0;
				scale_par = 0;
				translate_par = 0;
				rotation_parameter = 1;
				half_jump = 0;
				if(check == 0)
					count++;
				glutTimerFunc(TIMER_INTERVAL, on_timer, 0);
			   	
			}	
		}
        glutPostRedisplay();
		break;
	 case 's':
	 case 'S':
	 
	 	if(z_parameter > 0.00001  && end_of_game == 0){
			if (!animation_ongoing) {
				
				check = obstacle_check('s');
		        animation_ongoing = 1;
		        animation_par = 0;
		        scale_par = 0;
		        translate_par = 0;
		        rotation_parameter = 3;
		        half_jump = 0;
		        if(check == 0)
					count--;
		        glutTimerFunc(TIMER_INTERVAL, on_timer, 1);
		    }
		}
		glutPostRedisplay();
		break;
	case 'd':
	case 'D':
	
			if (!animation_ongoing && end_of_game == 0) {
	
				check = obstacle_check('d');
		        animation_ongoing = 1;
		        animation_par = 0;
		        scale_par = 0;
		        translate_par = 0;
		        rotation_parameter = 2;
		        if(check == 0)
					count_x++;
		        glutTimerFunc(TIMER_INTERVAL, on_timer_x, 0);
		        
		    }
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
	
			if (!animation_ongoing  && end_of_game == 0) {
				
				check = obstacle_check('a');
		        animation_ongoing = 1;
		        animation_par = 0;
		        scale_par = 0;
		        translate_par = 0;
		        rotation_parameter = 4;
		        if(check == 0)
					count_x--;
		        glutTimerFunc(TIMER_INTERVAL, on_timer_x, 1);
		        
		    }
		glutPostRedisplay();
		break;
	case 32:
	
		z_parameter = 1.5;
		x_parameter = 0;
		start_of_game = 0;
		animation_par = 0;
		scale_par = 0;
		translate_par = 0;
		sink_par = 0;
		check = 0;
		count = 1;
		count1 = 1; 
		count_x = 5;	
		z = 4.5;
		end_of_game = 0;
		for(i=0; i<150; i++){
			for(j=0; j<9;j++){
				obstacle[i][j] = 0.0;
			}
		}
		glutPostRedisplay();
		break;
	}    
}

void on_timer(int id)  /*kretanje karaktera i kamere napred-nazad*/
{

	if(id == 0 && animation_par >= 15 && check == 0
	   && end_of_game == 0){
    	z_parameter += 0.075;
    }
    
    if(id == 1 && animation_par >= 15 && check == 0){
    	z_parameter -= 0.075;
    }
    
    if(animation_par >= 14){
    	translate_par += 1.42857143;
    }
    
    if(id == 0 || id == 1){
    	animation_par += 1;
		scale_par += 2.85714286;
    }
	
	if(scale_par >= 35){
		scale_par = 35;
	}
	
	if(animation_par == 35){
		animation_ongoing = 0; 
		curr_rotation = rotation_parameter;
		if(id == 0 && check == 0)
			count1++;
		else if(id == 1 && check == 0)
			count1--;
		half_jump = 0;
	}
	
	if(animation_par == 20){
		half_jump = 1;
	}

    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, id);
    }
    
}

void on_timer_x(int id)  /*kretanje karaktera levo-desno*/
{
    
    if(id == 0 && animation_par >= 15 && x_parameter < 4.5001
       && check == 0 ){
    	x_parameter += 0.075;
    }
    
    if(id == 1 && animation_par >= 15 
   	   && x_parameter > -3 && check == 0){
    	x_parameter -= 0.075;
    }
    
    if(animation_par >= 14){
    	translate_par += 1.42857143;
    }
    
    if(id == 0 || id == 1){
    	animation_par += 1;
		scale_par += 2.85714286;
    }
	
	if(scale_par >= 35){
		scale_par = 35;
	}
	
	if(animation_par == 35){
		animation_ongoing = 0;
		curr_rotation = rotation_parameter; 
	}

    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer_x, id);
    }
}

void on_timer_car(int id){  /*kretanje automobila i ostrvca*/
	
	if(id == 0){
		car_par += 0.1;
		car_par1 += 0.08;
		island_par += 0.01;
	}

	if((int)car_par == 9){
		car_par = -10;
	}
	
	if((int)car_par1 == 10){
		car_par1 = -9;
	}
	
	glutPostRedisplay();

}

void on_timer_sink(int id){ /*animacija utapanja*/
	if(id == 0 && fabs(sink_par-1) > 0.0001){
		sink_par += 0.05;
	}

	if(fabs(sink_par-1) < 0.0001){
		sink_par = 1;
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
    
    glOrtho(-5, 5, -5, 5, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            1.4, 7, 5-z_parameter,  
            -1.6, 0, -4-z_parameter,
            0, 1, 0
        );
        
    glutTimerFunc(TIMER_INTERVAL, on_timer_car, 0);
    
    z = 4.5;
    
    draw_break();
	draw_break();
	draw_break();	
	
   	determine_obstacle_layout();
   	
   	if(count > 1){ /*provera da li su karaktera udarila kola*/
   	
		if((obstacle[count-1][1] == 1 || obstacle[count1-1][1] == 1)
		   && half_jump == 0 && fabs(car_par1-x_parameter+0.4) < 1){
			end_of_game = 1;
		}
		if((obstacle[count-1][1] == 2 || obstacle[count1-1][1] == 2) 
		   && half_jump == 0 && fabs(-car_par1-x_parameter-0.4) < 1){
			end_of_game = 1;
		}
		if((obstacle[count-1][1] == 3 || obstacle[count1-1][1] == 3)
		   && half_jump == 0 && fabs(car_par-x_parameter+0.4) < 1){
			end_of_game = 1;
		}
		if((obstacle[count-1][1] == 4 || obstacle[count1-1][1] == 4)
		   && half_jump == 0 && fabs(-car_par-x_parameter-0.4) < 1){
			end_of_game = 1;
		}
		if(end_of_game == 1)
			game_over();
		
	}
	
	if(fabs(sink_par-1) < 0.0001){
		sink_par = 1;
		end_of_game = 1;
		game_over();
	}
	
    draw_character();
	
    glutSwapBuffers();
}

void determine_obstacle_layout(){
	int i;
    srand(time(NULL));    
    if(start_of_game == 0){				    /*pravljenje niza na osvnovu*/
    	for(i = 0; i < ROAD_LENGTH; i++){ 	/*koga ce se iscrtavati prepreke i*/
    		terrain[i] = rand()%3;			/*dodatne provere kako ne bi bilo*/
    		if(i > 2){					  	/*previse uzastopno istih prepreka*/
    			if(terrain[i-1] == terrain[i-2] && terrain[i-1] == 1)
    				terrain[i] = 0;
    			if(terrain[i-1] == terrain[i-2] && terrain[i-1] == 0)
    				terrain[i] = 1;
    			if(terrain[i-1] == 1 && terrain[i] == 2)
    				terrain[i] = rand()%2;
    			if(terrain[i-1] == 2 && terrain[i] == 1)
    				terrain[i] = 0;
    		}
    	}
    	
    	for(i = 0; i < ROAD_LENGTH; i++){	/*dodatno uredjivanje*/
    										/*rasporeda prepreka*/	
    		if(terrain[i-1] == 1 && terrain[i] == 2)
    				terrain[i] = rand()%2;
    		if((terrain[i-1] == 2 || terrain[i-2] == 2 ||
    			terrain[i-3] == 2 || terrain[i-4] == 2) && terrain[i] == 2)
    				terrain[i] = rand()%2;
    	}
    	terrain[0] = 0;
    	terrain[1] = 0;
    	terrain[ROAD_LENGTH-1] = 0;
    	
   	}
   	
   	if(start_of_game < 2) 
   		start_of_game++;
    
    
    for(i = 0; i < ROAD_LENGTH; i++){		/*iscrtavanje prepreka*/
    	if(terrain[i] == 0)					/*i odmaralista na osnovu*/
    		draw_break();					/*prethodno generisanog niza*/
    	else if(terrain[i] == 1){
    		if(i%2 == 1){
    			if(i%4==1){					/*dodatna podela puteva kako*/
    				draw_road_d1();			/*bih mogao da imam razlicite*/
    			}							/*boje automobila i brzine*/
    			else{						/*kretanja*/
    				draw_road_d2();
    			}
    		}
    		else{
    			if(i%4==0){
    				draw_road_l1(terrain[i-1], terrain[i+1]);
    			}
    			else{
    				draw_road_l2(terrain[i-1], terrain[i+1]);	
    			}
    			
    		}	
    	}
    	else
    		draw_water();
    }
}

int obstacle_check(char c){
    	
   	check = 0;
   	int k = 0;
   	for(k = 2; k < 9; k++){								/*u zavisnosti od toga u*/
   		if((int)x_parameter == (int)obstacle[count][k] 	/*kom smeru igrac pokusava*/
   			&& (int)x_parameter != 0 && c == 'w'){		/*da pomeri karaktera*/
   			check = 1;									/*proveravam da li se*/
    	}												/*tu nalazi neka prepreka*/
    	if((int)x_parameter == (int)obstacle[count-2][k] 
   			&& (int)x_parameter != 0 && c == 's'){
   			check = 1;
    	} 
    	
    	if((int)obstacle[count-1][count_x-1] != 0 
   		   && c == 'a'){
   			check = 1;
    	}
    	
    	if((int)obstacle[count-1][count_x+1] != 0 
   			&& c == 'd'){
   			check = 1;
    	}
    	
    }
  	return check;
  	
}

void draw_road_d1(){ 

	if(start_of_game == 1){
		obstacle[-1*(int)(z/1.5)][1] = 1;
	}

	glPushMatrix(); /*put*/
		glColor3f (0.2, 0.2, 0.2);
		glTranslatef(0, 0, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();
	
	
	glPushMatrix(); /*automobil*/
		glTranslatef(1*car_par1, 0.4, z);
		glRotatef(180, 0, 1, 0);
		glScalef(1, 1, 1);
		draw_car(0);
	glPopMatrix();
	
	z -= 1.5;
}

void draw_road_l1(int x, int y){

	if(start_of_game == 1)
		obstacle[-1*(int)(z/1.5)][1] = 2;

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
		glTranslatef(-car_par1, 0.4, z);
		glScalef(1, 1, 1);
		draw_car(1);
	glPopMatrix();
	
	z -= 1.5;
}

void draw_road_d2(){

	if(start_of_game == 1)
		obstacle[-1*(int)(z/1.5)][1] = 3;

	glPushMatrix();
		glColor3f (0.2, 0.2, 0.2);
		glTranslatef(0, 0, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(1*car_par, 0.4, z);
		glRotatef(180, 0, 1, 0);
		glScalef(1, 1, 1);
		draw_car(2);
	glPopMatrix();
	
	
	z -= 1.5;
}

void draw_road_l2(int x, int y){

	if(start_of_game == 1)
		obstacle[-1*(int)(z/1.5)][1] = 4;

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
		glTranslatef(-car_par, 0.4, z);
		glScalef(1, 1, 1);
		draw_car(3);
	glPopMatrix();
	
	z -= 1.5;
}

void draw_break(){
	srand(z);
	
	glPushMatrix(); /*trava*/
		glColor3f (0.2, 0.6, 0.2);
		glTranslatef(0, 0.1, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();
	
	double array[9] = {-7.5, -6, -4.5, -3, -1.5, 0, 1.5, 3, 4.5};
	
	int i = 0;
	
		
	for(i = 0; i < 9; i++){ /*nasumicno crtanje drveca i kamenja*/
		if(rand()%2 == 1 && i != 5){
			glPushMatrix();
				glTranslatef(array[i], 0.6, z);
				int r = rand()%3;
				if(r == 1){
					if(start_of_game == 1 && (int)z <= 0)
						obstacle[-1*(int)(z/1.5)][i] = array[i];   
					draw_tree_1();
				}
				else if(r == 2){
					if(start_of_game == 1 && (int)z <= 0)
						obstacle[-1*(int)(z/1.5)][i] = array[i];   

					draw_tree_2();
				}
				else{
					if(start_of_game == 1 && (int)z <= 0)
						obstacle[-1*(int)(z/1.5)][i] = array[i];
					glScalef(0.8, 0.7, 0.8);	
					draw_stone();
				}
			glPopMatrix();
		}
		else{
			obstacle[-1*(int)(z/1.5)][i] = 0;
		}
	}
	
	z -= 1.5;
}

void draw_water(){
	if(start_of_game == 1){
		obstacle[-1*(int)(z/1.5)][0] = 2;
	}
	glPushMatrix(); /*voda*/
		glColor3f (0.1, 0.74, 0.8);
		glTranslatef(0, 0, z);
		glScalef(30, 0.2, 1.5);
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*ostrvce*/
		glColor3f(0.36, 0.2, 0.09);
		glTranslatef(-3.5*sin(island_par), 0.1, z);
		glScalef(3, 0.2, 0.75);
		glutSolidCube(1);
		
	glPopMatrix();

	z -= 1.5;

}

void draw_character(){



	glPushMatrix();
	if(obstacle[count1-1][0] == 2 
		&& (x_parameter >= -3.5*sin(island_par)-1.8
	    && x_parameter <= -3.5*sin(island_par)+1.8) ){ 
	    											  /*provera da li je*/
	    											  /*karakter skocio na*/
		/*x_parameter = -3.5*sin(island_par);*/       /*ostrvce ili u vodu*/
		if(rotation_parameter == 1)
			on_keyboard('w', 0, 0);
		else if(rotation_parameter == 3)
			on_keyboard('s', 0, 0);
	}
	else if(obstacle[count1-1][0] == 2
		&& ((x_parameter < -3.5*sin(island_par)-1.8
		|| x_parameter > -3.5*sin(island_par)+1.8) || (fabs(sink_par-0) > 0.0001))){
		
		
		glutTimerFunc(TIMER_INTERVAL, on_timer_sink, 0);
		glTranslatef(0, -sink_par, 0);
	
	}
	
	glTranslatef(0,0+sin(PI*translate_par/30),0);
    glTranslatef(0+x_parameter,0.8-0.35*sin(PI*scale_par/35),1.5-z_parameter);
    
 			
    if(rotation_parameter != curr_rotation){		/*rotiranje karaktera*/
    												/*morao sam da pamtim*/
   		if(curr_rotation == 1)						/*koja mu je prethodna rotacija*/
   			glRotatef(90, 0, 1, 0);					/*bila da bih znao kako da*/
 		if(curr_rotation == 3)						/*ga pravilno zarotiram*/
 			glRotatef(-90, 0, 1, 0);
    	if(curr_rotation == 4)
    		glRotatef(180, 0, 1, 0);
    	if((rotation_parameter == 1 && curr_rotation == 4) || 
   		   (rotation_parameter == 4 && curr_rotation == 3) ||
  		   (rotation_parameter == 3 && curr_rotation == 2) || 
    	   (rotation_parameter == 2 && curr_rotation == 1)){
    			   
  			    glRotatef(-90*animation_par/35, 0, 1, 0);
    			       			   	
   		}
    	if((rotation_parameter == 1 && curr_rotation == 3) ||
    	   (rotation_parameter == 4 && curr_rotation == 2) || 
   		   (rotation_parameter == 3 && curr_rotation == 1)){
    			   	
  			    glRotatef(180*animation_par/35, 0, 1, 0);
    			    			
   		}
    			
    	if(rotation_parameter == 2 && curr_rotation == 4){
    	
    			glRotatef(-180*animation_par/35, 0, 1, 0);
    			
   		}
    			
    	if((rotation_parameter == 3 && curr_rotation == 4) || 
    	   (rotation_parameter == 2 && curr_rotation == 3) ||
    	   (rotation_parameter == 1 && curr_rotation == 2) || 
   		   (rotation_parameter == 4 && curr_rotation == 1)){
    			   	
   			   	glRotatef(90*animation_par/35, 0, 1, 0);
    			   	
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
    	glColor3f(0.29, 0.38, 0.18);
		glTranslatef(0, 0.5-0.2 + 0.19 - 0.475, 0);
		glScalef(1 - 0.26, 0.19, 1 - 0.26); 
    	glutSolidCube(1);
  	glPopMatrix();
  	glPushMatrix();
    	glColor3f(0.32, 0.44, 0.21);
		glTranslatef(0, 0.5-0.2 + 0.38 - 0.475, 0);
		glScalef(1 - 0.26, 0.19, 1 - 0.26); 
    	glutSolidCube(1);
  	glPopMatrix();
  	glPushMatrix();
    	glColor3f(0.29, 0.38, 0.18);
		glTranslatef(0, 0.5-0.2 + 0.57 - 0.475, 0);
		glScalef(1 - 0.26, 0.19, 1 - 0.26); 
    	glutSolidCube(1);
  	glPopMatrix();
  	glPushMatrix();
    	glColor3f(0.32, 0.44, 0.21);
		glTranslatef(0, 0.5-0.2 + 0.76 - 0.475, 0);
		glScalef(1 - 0.26, 0.19, 1 - 0.26); 
    	glutSolidCube(1);
  	glPopMatrix();
  	glPushMatrix();
    	glColor3f(0.29, 0.38, 0.18);
		glTranslatef(0, 0.5-0.2 + 0.95 - 0.475, 0);
		glScalef(1 - 0.26, 0.19, 1 - 0.26); 
    	glutSolidCube(1);
  	glPopMatrix();
  	glPushMatrix();
    	glColor3f(0.32, 0.44, 0.21);
		glTranslatef(0, 0.5-0.2 + 1.14 - 0.475, 0);
		glScalef(1 - 0.26, 0.19, 1 - 0.26); 
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

void draw_car(int road){
	glPushMatrix();
		glColor3f(0.5,0.5,0.5);
		glTranslatef( 0, 0, 0);
		glScalef(2 , 0.2 - 0.12, 1);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*karoserija*/
		if(road == 0)
			glColor3f(0.6,0.6,0);
		else if(road == 1)
			glColor3f(0,0,0.6);
		else if(road == 2)
			glColor3f(0,0.6,0);
		else
			glColor3f(0.4,0,0.6);
		glTranslatef( 0, 0.21, 0);
		glScalef(2, 0.2 + 0.14, 1);
		
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef( 0.24, 0.57, 0);
		glScalef(1, 0.5 - 0.12, 0.7 - 0.05);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef( 0.1, 0.57, 0);
		glScalef(1 -0.41, 0.5 - 0.25, 0.7 - 0.04);
		glutSolidCube(1);
	glPopMatrix();
		
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef( 0.1 + 0.48, 0.57, 0);
		glScalef(1 -0.41 - 0.4, 0.5 - 0.25, 0.7 - 0.04);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef( 0.1 + 0.14, 0.57, 0);
		glScalef(1 -0.41 + 0.42, 0.5 - 0.25, 0.7 - 0.04 - 0.08);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); /*traka*/
		if(road == 0)
			glColor3f(0.5,0.5,0);
		else if(road == 1)
			glColor3f(0,0,0.45);
		else if(road == 2)
			glColor3f(0,0.45,0);
		else
			glColor3f(0.3,0,0.5);
		glTranslatef( 0, 0.21, 0 - 0.01);
		glScalef(2 + 0.01, 0.2 + 0.14 + 0.01, 1 - 0.7);
		
		glutSolidCube(1);
	glPopMatrix();
		
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef( 0 - 0.969999, 0.21 + 0.02, 0 + 0.01 - 0.34);
		glScalef(2 + 0.01 - 1.939999, 0.2 + 0.14 + 0.01 - 0.22, 1 - 0.7 - 0.15);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef( 0 - 0.969999, 0.21 + 0.02, 0 - 0.01 + 0.34);
		glScalef(2 + 0.01 - 1.939999, 0.2 + 0.14 + 0.01 - 0.22, 1 - 0.7 - 0.15);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef( 0 - 0.64, 0.21 - 0.22, 0 - 0.01 + 0.42);
		glScalef(2 + 0.01 - 1.669999, 0.2 + 0.14 + 0.01 - 0.02, 1 - 0.7 - 0.07);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef( 0 - 0.64, 0.21 - 0.22, 0 + 0.01 - 0.42);
		glScalef(2 + 0.01 - 1.669999, 0.2 + 0.14 + 0.01 - 0.02, 1 - 0.7 - 0.07);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef( 0 + 0.64, 0.21 - 0.22, 0 + 0.01 - 0.42);
		glScalef(2 + 0.01 - 1.669999, 0.2 + 0.14 + 0.01 - 0.02, 1 - 0.7 - 0.07);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef( 0 + 0.64, 0.21 - 0.22, 0 - 0.01 + 0.42);
		glScalef(2 + 0.01 - 1.669999, 0.2 + 0.14 + 0.01 - 0.02, 1 - 0.7 - 0.07);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.5,0.5,0.5);
		glTranslatef(0.64, -0.01, 0.42);
		glScalef(2 - 1.859999, 0.2 - 0.06, 1 - 0.78);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.5,0.5,0.5);
		glTranslatef(-0.64, -0.01, 0.42);
		glScalef(2 - 1.859999, 0.2 - 0.06, 1 - 0.78);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.5,0.5,0.5);
		glTranslatef(0.64, -0.01, -0.42);
		glScalef(2 - 1.859999, 0.2 - 0.06, 1 - 0.78);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.5,0.5,0.5);
		glTranslatef(-0.64, -0.01, -0.42);
		glScalef(2 - 1.859999, 0.2 - 0.06, 1 - 0.78);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.8,0.0,0.0);
		glTranslatef( 0 + 0.979999, 0.21 + 0.01, 0 - 0.01 + 0.38);
		glScalef(2 + 0.01 - 1.939999, 0.2 + 0.14 + 0.01 - 0.18, 1 - 0.7 - 0.19);
		
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.8,0.0,0.0);
		glTranslatef( 0 + 0.979999, 0.21 + 0.01, 0 + 0.01 - 0.38);
		glScalef(2 + 0.01 - 1.939999, 0.2 + 0.14 + 0.01 - 0.18, 1 - 0.7 - 0.19);
		
		glutSolidCube(1);
	glPopMatrix();

}






