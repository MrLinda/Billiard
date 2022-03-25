#include<graphics.h>
#include<windows.h>
#include<cmath>
#include<conio.h>
#include<iostream>
#include"const.h"
#include"engine.cpp"

//��78.4762�� ���ǿ�1.8689��
//�ڿ� ��0.07532 ��0.06796
//�� 2.2627���뾶
int width, height, w, h, r;//����ڿ�������ࡢ���뾶

void initialize();//��ʼ��
void test(Frame&);//����
void run();//������


int main()
{
	initialize();
	run();
	_getch();
	closegraph();	
	return 0;
}

void test(Frame &frame)
{
	for (int i = 0; i < num_ball; i++)
	{
		frame.ball[i].pos = setpoint(-1, -1);
	}
	frame.ball[0].color = 0xFFFFFF;
	frame.ball[0].pos = setpoint(width / 3, height / 2);
	frame.ball[0].v.x = 0.05;
	frame.ball[0].v.y = 0.10;
	frame.ball[1].color = RED;
	frame.ball[1].pos = setpoint(width/3+0.05*1500+4,height/2+0.10*1500);
	frame.ball[1].v.x = 0.02;
	frame.ball[1].v.y = 0.04;
	frame.ball[2].pos = setpoint(width * 3 / 5-radius, height / 2);
	frame.ball[3].pos = setpoint(width * 3 / 5+2*radius, height / 2);
	frame.ball[4].pos = setpoint(width * 3 / 5 + 2 * radius, height / 2+3*radius);
}

void run()
{
	Frame frame;
	init_frame(frame);//��ʼ��֡
	test(frame);//�����ú���
	while (true)
	{
		for (int i = 0; i < 100; i++)
		{
			calculate(frame);//����
		}

		draw(frame);//��Ⱦ
		Sleep(delay);//����֡��
	}
}

void initialize()//��ʼ��
{
	height = 78.4762 * radius;
	width = 1.8689 * height;
	w = 0.07532 * width, h = 0.06796 * height;
	r = 2.2627 * radius;
	initgraph(width,height);
	draw_background();
}