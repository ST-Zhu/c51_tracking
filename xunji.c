#include <reg52.h>

#define uint unsigned int
#define uchar unsigned char
#define CYCLE 31	//31步调整一次（PWM周期）

sbit ENA=P1^0;
sbit IN1=P1^1;
sbit IN2=P1^2;
sbit IN3=P1^3;
sbit IN4=P1^4;
sbit ENB=P1^5;

sbit L1=P2^0;
sbit L2=P2^1;
sbit R2=P2^2;
sbit R1=P2^3;
sbit L3=P2^4;
sbit R3=P2^5;

uchar count_R,count_L;		//计数数
uchar PWM_R,PWM_L;		//所占空间比

void init()
{
	TMOD=0x01;
	TH0=(65536-100)/256;
	TL0=(65536-100)%256;
	EA=1;
	ET0=1;
	TR0=1;		//开定时器0
	
	ENA=1;
	ENB=1;	//初始化小车状态
}

void zhixing()
{
	PWM_R=8;
	PWM_L=8;
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=1;
}

void youzhuan_2()
{
	PWM_R=18;
	PWM_L=23;
	IN1=1;
	IN2=0;
	IN3=0;
	IN4=1;
}

void youzhuan_3()
{
	PWM_R=30;
	PWM_L=18;
	IN1=1;
	IN2=0;
	IN3=1;
	IN4=0;
}

void youzhuan_1()
{
	PWM_R=0;
	PWM_L=20;
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=1;
}

void zuozhuan_2()
{
	PWM_R=23;
	PWM_L=18;
	IN1=0;
	IN2=1;
	IN3=1;
	IN4=0;
}

void zuozhuan_3()
{
	PWM_R=18;
	PWM_L=30;
	IN1=1;
	IN2=0;
	IN3=1;
	IN4=0;
}

void zuozhuan_1()
{
	PWM_R=20;
	PWM_L=0;
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=1;
}

void houtui()
{
	PWM_R=8;
	PWM_L=8;
	IN1=1;
	IN2=0;
	IN3=1;
	IN4=0;
}

void xuanji()
{
	if((L1==0)&&(L2==0)&&(L3==0)&&(R3==0)&&(R2==0)&&(R1==0)) zhixing();

	if((L3==1)&&(R3==0)&&(R2==0)&&(R1==0)) youzhuan_3();
	if((L2==1)&&(L3==0)&&(R3==0)&&(R2==0)&&(R1==0)) youzhuan_2();
	if((L1==1)&&(L2==0)&&(L3==0)&&(R3==0)&&(R2==0)&&(R1==0)) youzhuan_1();
	
	if((L1==0)&&(L2==0)&&(L3==0)&&(R3==1)) zuozhuan_3();
	if((L1==0)&&(L2==0)&&(L3==0)&&(R1==0)&&(R2==1)) zuozhuan_2();
	if((L1==0)&&(L2==0)&&(L3==0)&&(R3==0)&&(R2==0)&&(R1==1)) zuozhuan_1();
	
	if((L1==1)&&(L2==1)&&(L3==1)&&(R3==1)&&(R2==1)&&(R1==1)) houtui();
}

void main()
{
	init();
	while(1)
	{
		xuanji();
	}
}

void timer0() interrupt 1 //定时器0中断（100us）
{
	count_R++;
	count_L++;
	
	if(count_R<=PWM_R)
		ENA=1;
  else
		ENA=0;
	if(count_R==CYCLE)
	{
		ENA=~ENA;
		count_R=0;
	}
	
	if(count_L<=PWM_L)
		ENB=1;
  else
		ENB=0;
	if(count_L==CYCLE)
	{
		ENB=~ENB;
		count_L=0;
	}								//PWM调速
	
	TH0=(65536-100)/256;
	TL0=(65536-100)%256;		//装初值
}
