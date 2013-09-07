/**
* POJ 2420
* 模拟退火
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 128
#define EPS 0.1
using namespace std;
int n;
double x[N], y[N];
double f(double a, double b)
{
    int i;
    double ans = 0;
    for (i=0; i<n; i++)
        ans += sqrt((a-x[i])*(a-x[i]) + (b-y[i])*(b-y[i]));
    return ans;
}
int main()
{
    double ans, step, temp, a, b, ta, tb;
    int i;
    bool flag;
    while (scanf("%d", &n) == 1)
    {
        for (i=0; i<n; i++)
            scanf("%lf%lf", &x[i], &y[i]);
        a = x[0];
        b = y[0];
        ans = f(a, b);
        step = 128;
        while (step > EPS) {
            for(int i=0;i<50;++i) {
                double ang = rand();
                temp = f(a+step*cos(ang), b+step*sin(ang));
                if(temp < ans) {
                    a += step*cos(ang);
                    b += step*sin(ang);
                    ans = temp;
                }
            }
            step *= 0.8;
        }
        printf("%.0f\n", ans);
    }
    return 0;
}
