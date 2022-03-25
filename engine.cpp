#include"engine.h"
#include<cmath>


void draw(Frame frame)
{
	//画背景
	draw_background();

	//画球
	for (int i = 0; i < num_ball; i++)
	{
		draw_ball(frame.ball[i]);
	}

}

void calculate(Frame& frame)
{
	//上下左右四条边界
	int boundary[4] = { h + radius,height - h - radius,w + radius,width - w - radius };
	//6个袋坐标
	Point hole[6] = { setpoint(w,h),setpoint(width / 2,h), setpoint(width - w,h), setpoint(w,height - h),setpoint(width / 2,height - h), setpoint(width - w,height - h) };

	//球间碰撞处理
	for (int i = 0; i < num_ball; i++)
	{
		for (int j = i; j < num_ball; j++)
		{
			double dist = distance(frame.ball[i].pos, frame.ball[j].pos);
			if (dist < frame.ball[i].rad + frame.ball[j].rad)
			{
				/*
				double co, si;
				Speed v[2];
				co = abs(frame.ball[i].pos.x - frame.ball[j].pos.x) / dist;
				si = abs(frame.ball[i].pos.y - frame.ball[j].pos.y) / dist;
				v[0].x = frame.ball[i].v.x * co + frame.ball[i].v.y * si;
				v[0].y = frame.ball[i].v.x * si + frame.ball[i].v.y * co;
				v[1].x = frame.ball[j].v.x * co + frame.ball[j].v.y * si;
				v[1].y = frame.ball[j].v.x * si + frame.ball[j].v.y * co;
				*/
				Speed p = frame.ball[i].v;
				frame.ball[i].v = frame.ball[j].v;
				frame.ball[j].v = p;
			}
		}
	}


	//开始运算
	for (int i = 0; i < num_ball; i++)
	{
		if (frame.ball[i].pos.x < 0 && frame.ball[i].pos.y < 0) continue;//球不存在时忽略
		Ball next = frame.ball[i];
		next.pos.x += next.v.x;
		next.pos.y += next.v.y;
		next.v.x /= 1.00002;
		next.v.y /= 1.00002;

		//进袋处理
		bool flag = false;//是否进袋
		if (next.rad < radius)
		{
			flag = true;
			if (next.rad > 1)
			{
				next.rad /= 1.0025;
			}
			else
			{
				next.pos = setpoint(-1, -1);
			}
			frame.ball[i] = next;
		}
		if (!flag)
			for (int j = 0; j < 6; j++)
			{
				if (distance(next.pos, hole[j]) < r)
				{
					next.pos = hole[j];
					next.rad /= 1.0025;
					next.v.x = 0;
					next.v.y = 0;
					frame.ball[i] = next;
					flag = true;
					break;
				}
			};
		if (flag) continue;


		//边界碰撞处理
		if (next.pos.x > boundary[3])
		{
			next.pos.x = 2 * boundary[3] - next.pos.x;
			next.v.x = -next.v.x;
		}
		if (next.pos.y > boundary[1])
		{
			next.pos.y = 2 * boundary[1] - next.pos.y;
			next.v.y = -next.v.y;
		}
		if (next.pos.x < boundary[2])
		{
			next.pos.x = 2 * boundary[2] - next.pos.x;
			next.v.x = -next.v.x;
		}
		if (next.pos.y < boundary[0])
		{
			next.pos.y = 2 * boundary[0] - next.pos.y;
			next.v.y = -next.v.y;
		}
		//修改帧中球的参数
		frame.ball[i] = next;
	}
}

void init_frame(Frame& frame)//初始化
{
	for (int i = 0; i < num_ball; i++)
	{
		frame.ball[i].rad = radius;
		frame.ball[i].v.x = 0;
		frame.ball[i].v.y = 0;
	}
}

Point setpoint(double x, double y)//略
{
	Point p;
	p.x = x;
	p.y = y;
	return p;
}

double distance(Point a, Point b)//两点距离
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void draw_ball(Ball ball)//略
{
	if (ball.pos.x < 0 && ball.pos.y < 0) return;
	setfillcolor(ball.color);
	fillcircle(ball.pos.x, ball.pos.y, ball.rad);
}

void draw_background()//画背景图
{
	setlinecolor(0xFFFFFF);
	setfillcolor(0x2277AA);
	fillrectangle(0, 0, width, height);//外框

	setlinecolor(0x088A08);
	setfillcolor(0x088A08);
	fillrectangle(w, h, width - w, height - h);//内框

	setlinecolor(0xFFFFFF);
	setfillcolor(0x088A08);
	fillcircle(w, h, r);
	fillcircle(width / 2, h, r);
	fillcircle(width - w, h, r);
	fillcircle(w, height - h, r);
	fillcircle(width / 2, height - h, r);
	fillcircle(width - w, height - h, r);//袋

}