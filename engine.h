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

void draw(Frame);//渲染
void calculate(Frame&);//计算
void draw_ball(Ball);//渲染单个球
void init_frame(Frame&);//初始化帧
double distance(Point,Point);//两点距离
Point setpoint(double,double);//返回Point类型
void draw_background();//画背景
//extern 
