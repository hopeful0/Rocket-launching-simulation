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
    void outparameter(ofstream *out);
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
            case 3: setsimulationparameter(); break;
            case 4: run(); break;
            case 5: return 0;
        }
    }
}

void printfun()
{
    cout << "==================执行==================" << endl;
    cout << "1.设置火箭参数" << endl;
    cout << "2.设置环境参数" << endl;
    cout << "3.设置模拟参数" << endl;
    cout << "4.发射火箭" << endl;
    cout << "5.退出模拟" << endl;
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
    cout << "请输入星球半径(m|不能为0，否则会出错）：" << endl;
    cin >> R;
    cout << "请输入星球质量(kg)：" << endl;
    cin >> M;
    cout << "请输入星球自转速度(rad/s)：" << endl;
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

void outparameter(ofstream *out)
{
    *out << "环境常量：\n高速临界速度 m/s：" <<hv<<"\n引力常量 N·m^2/kg^2："<<G<<"\n";
    *out << "环境参数：\n低速下阻力系数 1：" <<u1<<"\n高速下阻力系数 1："<<u2<<"\n星球自转角速度 rad/s："<<w<<"\n星球半径 m："<<R<<"\n星球质量 kg："<<M<<"\n";
    *out << "火箭属性：\n发射质量 kg：" <<m0<<"\n燃料质量 kg："<<mr<<"\n喷气速度 m/s："<<ve<<"\n燃料消耗速度 kg/s："<<vm<<"\n";
    *out << "模拟参数：\n时间步长：" <<dt<<"\n";
    *out << "==================================\n";
}

void run()
{
    ofstream out("D:\data.rls");
    if(!out.is_open())
        cout << "文件打开失败！将只显示控制台结果！" << endl;
    else
        outparameter(&out);
    h=0;v=0;t=0;
    double rr = mr;//燃料剩余量 kg
    double a = 0;//加速度 m/s^2
    double vh = w * R;//水平速度 m/s
    double sh = 0;//水平位移 m
    cout << "===========================================" << endl;
    if(vh==0)
    {
        cout << "时间(s)|质量(kg)|加速度(m/s^2)|速度(m/s)|高度(m)" << endl;
        out << "时间(s)|质量(kg)|加速度(m/s^2)|速度(m/s)|高度(m)\n";
    }
    else
    {
        cout << "时间(s)|质量(kg)|竖直加速度(m/s^2)|水平加速度(m/s^2)|竖直速度(m/s)|水平速度(m/s)|竖直位移(m)|水平位移(m)" << endl;
        out << "时间(s)|质量(kg)|竖直加速度(m/s^2)|水平加速度(m/s^2)|竖直速度(m/s)|水平速度(m/s)|竖直位移(m)|水平位移(m)\n";
    }
    while(rr>0)
    {
        t+=dt;
        rr -= vm * dt;
        if(vh==0)
        {
            if(v>=hv)
                a=(vm*ve-u2*pow(v,2)-G*M*(m0-mr+rr)/pow(R+h,2))/(m0-mr+rr);
            else
                a=(vm*ve-u1*v-G*M*(m0-mr+rr)/pow(R+h,2))/(m0-mr+rr);
            v+=a*dt;
            h+=v*dt;
            cout << t << "|" << m0-mr+rr << "|" << a << "|" << v << "|" << h << endl;
            out <<  t << "|" << m0-mr+rr << "|" << a << "|" << v << "|" << h << "\n";
        }
        else
        {
            double av=0,ah=0;//分加速度 m/s^2
            double alpha,beta;//v与竖直方向夹角，R'与竖直方向夹角
            alpha = atan(vh / v);
            beta = atan(sh / (R+h));
            if(v>=hv)
            {
                av=(vm*ve*cos(alpha)-u2*pow(v*cos(alpha),2)-G*M*(m0-mr+rr)/(pow(R+h,2)+pow(sh,2))*cos(beta))/(m0-mr+rr);
                ah=(vm*ve*sin(alpha)-u2*pow(v*sin(alpha),2)-G*M*(m0-mr+rr)/(pow(R+h,2)+pow(sh,2))*sin(beta))/(m0-mr+rr);
            }
            else
            {
                av=(vm*ve*cos(alpha)-u1*v*cos(alpha)-G*M*(m0-mr+rr)/(pow(R+h,2)+pow(sh,2))*cos(beta))/(m0-mr+rr);
                ah=(vm*ve*sin(alpha)-u1*v*sin(alpha)-G*M*(m0-mr+rr)/(pow(R+h,2)+pow(sh,2))*sin(beta))/(m0-mr+rr);
            }
            v+=av*dt;
            vh+=ah*dt;
            h+=v*dt;
            sh+=vh*dt;
            cout << t << "|" << m0-mr+rr << "|" << av << "|" << ah << "|" << v << "|" << vh << "|" << h << "|" << sh << endl;
            out << t << "|" << m0-mr+rr << "|" << av << "|" << ah << "|" << v << "|" << vh << "|" << h << "|" << sh << "\n";
        }

    }
    if(out.is_open())
    {
        out.close();
    }
    return;
}
