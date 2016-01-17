#include <iostream>
#include <fstream>
#include <math.h>

/**
* �������ģ�����
* ���ߣ�hopeful
* ���ڣ�2016/1/14
* �˳�����������ģ��������Ĺ��̣������ۻ��������������ǳ������
*/

using namespace std;

//��������
const double hv = 850.75;//�����ٽ��ٶ� m/s
const double G = 6.754e-11;//�������� N��m^2/kg^2

//��������
double u1;//����������ϵ�� 1
double u2;//����������ϵ�� 1
double w;//������ת���ٶ� rad/s
double R;//����뾶 m
double M;//�������� kg

//�������
long m0;//�������� kg
long mr;//ȼ������ kg
double ve;//�����ٶ� m/s
double vm;//ȼ�������ٶ� kg/s

//���в���
double h;//���и߶� m
double v;//�����ٶ� m/s
double t;//����ʱ�� s

//ģ�����
double dt;//ʱ�䲽��

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
    cout << "==================ִ��==================" << endl;
    cout << "1.���û������" << endl;
    cout << "2.���û�������" << endl;
    cout << "3.����ģ�����" << endl;
    cout << "4.������" << endl;
    cout << "5.�˳�ģ��" << endl;
    cout << "========================================" << endl;
    cout << "���������ִ�й��ܣ�";
}

void setenvparameter()
{
    cout << "�밴����ʾ�������²�����" << endl;
    cout << "���������������ϵ����" << endl;
    cin >> u1;
    cout << "���������������ϵ����" << endl;
    cin >> u2;
    cout << "����������뾶(m|����Ϊ0������������" << endl;
    cin >> R;
    cout << "��������������(kg)��" << endl;
    cin >> M;
    cout << "������������ת�ٶ�(rad/s)��" << endl;
    cin >> w;
}


void setrocketparameter()
{
    cout << "�밴����ʾ�������²�����" << endl;
    cout << "����������������(Kg|����)��" << endl;
    cin >> m0;
    cout << "��������ȼ������(Kg|����)��" << endl;
    cin >> mr;
    cout << "�������������ٶ�(m/s)��" << endl;
    cin >> ve;
    cout << "��������ȼ�������ٶ�(kg/s)��" << endl;
    cin >> vm;
}

void setsimulationparameter()
{
    cout << "�밴����ʾ�������²�����" << endl;
    cout << "������ģ��ʱ�䲽����" << endl;
    cin >> dt;

}

void outparameter(ofstream *out)
{
    *out << "����������\n�����ٽ��ٶ� m/s��" <<hv<<"\n�������� N��m^2/kg^2��"<<G<<"\n";
    *out << "����������\n����������ϵ�� 1��" <<u1<<"\n����������ϵ�� 1��"<<u2<<"\n������ת���ٶ� rad/s��"<<w<<"\n����뾶 m��"<<R<<"\n�������� kg��"<<M<<"\n";
    *out << "������ԣ�\n�������� kg��" <<m0<<"\nȼ������ kg��"<<mr<<"\n�����ٶ� m/s��"<<ve<<"\nȼ�������ٶ� kg/s��"<<vm<<"\n";
    *out << "ģ�������\nʱ�䲽����" <<dt<<"\n";
    *out << "==================================\n";
}

void run()
{
    ofstream out("D:\data.rls");
    if(!out.is_open())
        cout << "�ļ���ʧ�ܣ���ֻ��ʾ����̨�����" << endl;
    else
        outparameter(&out);
    h=0;v=0;t=0;
    double rr = mr;//ȼ��ʣ���� kg
    double a = 0;//���ٶ� m/s^2
    double vh = w * R;//ˮƽ�ٶ� m/s
    double sh = 0;//ˮƽλ�� m
    cout << "===========================================" << endl;
    if(vh==0)
    {
        cout << "ʱ��(s)|����(kg)|���ٶ�(m/s^2)|�ٶ�(m/s)|�߶�(m)" << endl;
        out << "ʱ��(s)|����(kg)|���ٶ�(m/s^2)|�ٶ�(m/s)|�߶�(m)\n";
    }
    else
    {
        cout << "ʱ��(s)|����(kg)|��ֱ���ٶ�(m/s^2)|ˮƽ���ٶ�(m/s^2)|��ֱ�ٶ�(m/s)|ˮƽ�ٶ�(m/s)|��ֱλ��(m)|ˮƽλ��(m)" << endl;
        out << "ʱ��(s)|����(kg)|��ֱ���ٶ�(m/s^2)|ˮƽ���ٶ�(m/s^2)|��ֱ�ٶ�(m/s)|ˮƽ�ٶ�(m/s)|��ֱλ��(m)|ˮƽλ��(m)\n";
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
            double av=0,ah=0;//�ּ��ٶ� m/s^2
            double alpha,beta;//v����ֱ����нǣ�R'����ֱ����н�
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
