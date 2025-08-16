#include<iostream>
#include <math.h>
#include <cmath>
using namespace std;

double f1(double M)
{
    double a = pow(M, 2);
    double b = pow((5.76*a)/(2*(2.8*a - 0.4)) , 3.5);
    double c = (2*1.4*a - 0.4)/(2.4);
    return b*c;
}

double f2(double M)
{
    double a = pow(M, 2);
    double b = sqrt(6);
    double c = atan(sqrt((a - 1)/6));
    double d = atan(sqrt((a - 1)));
    return (b*c - d) * 180 / M_PI;
}

double f6(double theta, double beta, double M)
{
    double a = beta - theta;
    return M*sin(a*M_PI/180);
}

double f4(double Mn2)
{
    return sqrt((1 + 0.2*Mn2*Mn2)/(1.4*Mn2*Mn2 - 0.2));;
}

double f5(double theta, double beta)
{
    double a = 2*(tan(theta*M_PI/180) + (1/tan(beta*M_PI/180)));
    double b = sin(2*beta*M_PI/180);
    double c = tan(theta*M_PI/180)*(1.4 + cos(2*beta*M_PI/180));
    return sqrt(fabs(a/(b - c)));
}

int main(){
    double P04, P4, P3, a, b, c, gamma, M, d, e, a1, b1, error, theta;
    cout<<"Theta = ";
    cin >> theta;
    cout<<"P04 = ";
    cin >> P04;
    cout<<"P3 = ";
    cin >> P3;
    e = P04/P3;
    a1 = 0;
    b1 = 10;
    do{
        a = a1;
        b = b1;
        c = (a + b)/2;
        M = f1(c);
        if ((f1(c) - e)*(f1(a) - e) < 0)
        {
            b1 = c;
        }
        else if((f1(c) - e)*(f1(b) - e) < 0)
        {
            a1 = c;
        }  
        error = fabs((1 - e/M)*100);    
    }while (error >= pow(10, -10));

    cout << "M3 = " << c << endl;

    double V3, V2;
    V3 = f2(c);
    V2 = V3 - theta;
    a1 = 1;
    b1 = 5;
    do{
        a = a1;
        b = b1;
        M = (a + b)/2;
        c = f2(M);
        if ((f2(M) - V2)*(f2(a) - V2) < 0)
        {
            b1 = M;
        }
        else if((f2(M) - V2)*(f2(b) - V2) < 0)
        {
            a1 = M;
        }  
        error = fabs((1 - c/V2));   
    }while (error >= 0.01);

    double M2;
    M2 = M;
    cout << "M2 = " << M2 << endl;

    double beta, d1, d2, d3, e1, e2, e3, l1, l2, l3, g1, g2, g3;

    a1 = theta/2;
    b1 = 90;

    do{
        a = a1;
        b = b1;
        e1 = f5(theta/2, a);
        g1 = e1*sin(a*M_PI/180);  
        l1 = f4(g1);
        d1 = f6(theta/2, a, M2);
        
        e2 = f5(theta/2, b);
        g2 = e2*sin(b*M_PI/180);  
        l2 = f4(g2);
        d2 = f6(theta/2, b, M2);

        c = (a + b)/2;
        
        e3 = f5(theta/2, c);
        g3 = e3*sin(c*M_PI/180);  
        l3 = f4(g3);
        d3 = f6(theta/2, c, M2);
        
        if ((l3 - d3)*(l1 - d1) < 0)
        {
            b1 = c;
        }
        else if ((l3 - d3)*(l2 - d2) < 0)
        {
            a1 = c;
        }

        error = fabs(l3 - d3);

    }while (error >= pow(10, -10));

    cout << "beta = " << c << endl;
    cout << "Mn2 = " << l3 << endl;
    cout << "Mn1 = " << g3 << endl;
    cout << "M1 = " << e3 << endl;
    
    return 0;
}