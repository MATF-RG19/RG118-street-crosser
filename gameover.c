#include "gameover.h"
#include "functions.h"


void game_over(){ /*ispisivanje teksta pri kraju igrice*/

	glPushMatrix(); /*tintovanje pozadine kako bi se tekst bolje video*/
		glColor4f(0, 0, 0, 0.5);
		glTranslatef(0, 2, -z_parameter);
		glScalef(30, 0.3, 30);
	 	glutSolidCube(1);
	glPopMatrix();

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();

	glDisable( GL_DEPTH_TEST ); 
	  
	int len, i;
	char buf[300];
	glColor4f( 1, 0, 0, 1 );
	glRasterPos3f(-1, -0.1, 0);
	sprintf( buf, ".");  
	  
	for (i = 0; i < 1; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buf[i]);
	}
	
	glColor4f( 1, 1, 1, 1 );
	
	glRasterPos3f(-0.15, 0, 0);
	sprintf( buf, "GAME OVER");  
	  
	for (i = 0; i < 9; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buf[i]);
	}
	 
	glRasterPos3f(-0.13, -0.1, 0);
	sprintf( buf, "Your score: %d", count-1);  
	len = (int)strlen(buf);
	  
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buf[i]);
	}
	  
	glRasterPos3f(-0.4, -0.2, 0);
	sprintf( buf, "Press SPACE to start a new game!");  
	  
	for (i = 0; i < 32; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buf[i]);
	}
	 
	glEnable( GL_DEPTH_TEST );
	 
	glPopMatrix();
	
}
