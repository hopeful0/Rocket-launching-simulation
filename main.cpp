#include <iostream>
#include <math.h>

/**
* 火箭发射模拟程序
* 作者：hopeful
* 日期：2016/1/14
* 此程序用来近似模拟火箭发射的过程，其理论基础见《火箭发射浅析》。
*/

using namespace std;

//环境参数
double u1;//低速下阻力系数 1
double u2;//高速下阻力系数 1
double w;//星球自转角速度 rad/s
double R;//星球半径 m

//火箭属性
long m0;//发射质量 kg
long mr;//燃料质量 kg
double Ve;//喷气速度 m/s
double Vm;//燃料消耗速度 kg/s

//飞行参数
double h;//飞行高度 m
double v;//飞行速度 m/s
double t;//飞行时间 s

int main()
{
    void setparameter();
    void run();


}

void setparameter()
{

}

void run()
{

}
