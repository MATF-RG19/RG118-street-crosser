#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void on_reshape(int width, int height); 
void on_display(void);
void on_keyboard(unsigned char key, int x, int y);
void draw_road();
void draw_break();
void draw_water();
void determine_obstacle_layout();
void draw_character();

#endif
