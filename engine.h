#pragma once
#include<graphics.h>
#include"const.h"

typedef struct Point
{
	double x, y;
};

typedef struct Speed
{
	double x, y;
};

typedef struct Ball
{
	COLORREF color;
	Point pos;
	Speed v;
	double rad;
};

typedef struct Frame
{
	Ball ball[num_ball];
};

void draw(Frame);//��Ⱦ
void calculate(Frame&);//����
void draw_ball(Ball);//��Ⱦ������
void init_frame(Frame&);//��ʼ��֡
double distance(Point,Point);//�������
Point setpoint(double,double);//����Point����
void draw_background();//������
//extern 
