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
    cout << "==================ִ��==================" << endl;
    cout << "1.���û������" << endl;
    cout << "2.���û�������" << endl;
    cout << "3.������" << endl;
    cout << "4.�˳�ģ��" << endl;
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
    cout << "����������뾶(m)��" << endl;
    cin >> R;
    cout << "��������������(kg)��" << endl;
    cin >> M;
    cout << "������������ת�ٶ�(m/s)��" << endl;
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

void run()
{
    ofstream out("D:\data.rls");
    if(!out.is_open())
        cout << "�ļ���ʧ�ܣ���ֻ��ʾ����̨�����" << endl;
    else
        out << "";
    h=0;v=0;t=0;
    double rr = mr;//ȼ��ʣ���� kg
    double a = 0;//���ٶ� m/s^2
    double vh = w * R;//ˮƽ�ٶ� m/s
    double sh = 0;//ˮƽλ�� m
    cout << "===========================================" << endl;
    if(vh==0)
        cout << "ʱ��|����|���ٶ�|�ٶ�|�߶�" << endl;
    else
        cout << "ʱ��|����|���ٶ�(��ֱ)|���ٶ�(ˮƽ)|�ٶ�(��ֱ)|�ٶ�(ˮƽ)|��ֱλ��|ˮƽλ��" << endl;
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
            double av=0,ah=0;//�ּ��ٶ� m/s^2
            double alpha,beta;//v����ֱ����нǣ�R'����ֱ����н�
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
