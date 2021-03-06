#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#define TIMER_INTERVAL 1

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

double extern z_parameter;
int extern count;

void on_reshape(int width, int height); 
void on_display(void);
void on_keyboard(unsigned char key, int x, int y);
void on_timer(int id);
void on_timer_x(int id);
void on_timer_car(int id);
void on_timer_sink(int id);
void determine_obstacle_layout();
int obstacle_check(char c);
void draw_road_d1(void);
void draw_road_l1(int x, int y);
void draw_road_d2(void);
void draw_road_l2(int x, int y);
void draw_break(void);
void draw_water(void);
void draw_character(void);
void draw_leg(void);
void draw_tree_1(void);
void draw_tree_2(void);
void draw_stone(void);
void draw_car(int road);

#endif
