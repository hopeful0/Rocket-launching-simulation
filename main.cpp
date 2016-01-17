#include <iostream>
#include <fstream>
#include <math.h>

/**
* 火箭发射模拟程序
* 作者：hopeful
* 日期：2016/1/14
* 此程序用来近似模拟火箭发射的过程，其理论基础见《火箭发射浅析》。
*/

using namespace std;

//环境常量
const double hv = 850.75;//高速临界速度 m/s
const double G = 6.754e-11;//引力常量 N·m^2/kg^2

//环境参数
double u1;//低速下阻力系数 1
double u2;//高速下阻力系数 1
double w;//星球自转角速度 rad/s
double R;//星球半径 m
double M;//星球质量 kg

//火箭属性
long m0;//发射质量 kg
long mr;//燃料质量 kg
double ve;//喷气速度 m/s
double vm;//燃料消耗速度 kg/s

//飞行参数
double h;//飞行高度 m
double v;//飞行速度 m/s
double t;//飞行时间 s

//模拟参数
double dt;//时间步长

int main()
{
    void printfun();
    void setrocketparameter();
    void setenvparameter();
    void setsimulationparameter();
    void run();
    setenvparameter();
    setrocketparameter();
    setsimulationparameter();
    while(1)
    {
        int i;
        printfun();
        cin >> i;
        switch(i)
        {
            case 1: setrocketparameter(); break;
            case 2: setenvparameter(); break;
            case 3: run(); break;
            case 4: return 0;
        }
    }
}

void printfun()
{
    cout << "==================执行==================" << endl;
    cout << "1.设置火箭参数" << endl;
    cout << "2.设置环境参数" << endl;
    cout << "3.发射火箭" << endl;
    cout << "4.退出模拟" << endl;
    cout << "========================================" << endl;
    cout << "输入序号以执行功能：";
}

void setenvparameter()
{
    cout << "请按照提示输入以下参数！" << endl;
    cout << "请输入低速下阻力系数：" << endl;
    cin >> u1;
    cout << "请输入高速下阻力系数：" << endl;
    cin >> u2;
    cout << "请输入星球半径(m)：" << endl;
    cin >> R;
    cout << "请输入星球质量(kg)：" << endl;
    cin >> M;
    cout << "请输入星球自转速度(m/s)：" << endl;
    cin >> w;
}


void setrocketparameter()
{
    cout << "请按照提示输入以下参数！" << endl;
    cout << "请输入火箭发射质量(Kg|整数)：" << endl;
    cin >> m0;
    cout << "请输入火箭燃料质量(Kg|整数)：" << endl;
    cin >> mr;
    cout << "请输入火箭喷气速度(m/s)：" << endl;
    cin >> ve;
    cout << "请输入火箭燃料消耗速度(kg/s)：" << endl;
    cin >> vm;
}

void setsimulationparameter()
{
    cout << "请按照提示输入以下参数！" << endl;
    cout << "请输入模拟时间步长：" << endl;
    cin >> dt;

}

void run()
{
    ofstream out("D:\data.rls");
    if(!out.is_open())
        cout << "文件打开失败！将只显示控制台结果！" << endl;
    else
        out << "";
    h=0;v=0;t=0;
    double rr = mr;//燃料剩余量 kg
    double a = 0;//加速度 m/s^2
    double vh = w * R;//水平速度 m/s
    double sh = 0;//水平位移 m
    cout << "===========================================" << endl;
    if(vh==0)
        cout << "时间|质量|加速度|速度|高度" << endl;
    else
        cout << "时间|质量|加速度(竖直)|加速度(水平)|速度(竖直)|速度(水平)|竖直位移|水平位移" << endl;
    while(mr>0)
    {
        t+=dt;
        if(vh==0)
        {
            if(v>=hv)
                a=(vm*ve-u2*pow(v,2)-G*M*(m0+rr)/pow(R+h,2))/(m0+rr);
            else
                a=(vm*ve-u1*v-G*M*(m0+rr)/pow(R+h,2))/(m0+rr);
            v+=a*dt;
            h+=v*dt;
            cout << t << "|" << m0+rr << "|" << a << "|" << v << "|" << h << endl;
        }
        else
        {
            double av=0,ah=0;//分加速度 m/s^2
            double alpha,beta;//v与竖直方向夹角，R'与竖直方向夹角
            alpha = atan(vh / v);
            beta = atan(sh / (R+h));
            if(v>=hv)
            {
                av=(vm*ve*cos(alpha)-u2*pow(v*cos(alpha),2)-G*M*(m0+rr)/(pow(R+h,2)+pow(sh,2))*cos(beta))/(m0+rr);
                ah=(vm*ve*sin(alpha)-u2*pow(v*sin(alpha),2)-G*M*(m0+rr)/(pow(R+h,2)+pow(sh,2))*sin(beta))/(m0+rr);
            }
            else
            {
                av=(vm*ve*cos(alpha)-u1*v*cos(alpha)-G*M*(m0+rr)/(pow(R+h,2)+pow(sh,2))*cos(beta))/(m0+rr);
                ah=(vm*ve*sin(alpha)-u1*v*sin(alpha)-G*M*(m0+rr)/(pow(R+h,2)+pow(sh,2))*sin(beta))/(m0+rr);
            }
            v+=av*dt;
            vh+=ah*dt;
            h+=v*dt;
            sh+=vh*dt;
            cout << t << "|" << m0+rr << "|" << av << "|" << ah << "|" << v << "|" << vh << "|" << h << "|" << sh << endl;
        }
        rr -= vm * dt;
    }
    if(out.is_open())
    {
        out.close();
    }
    return;
}
