/**
* HDU 4498
* simpson 积分
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 55;
vector<double> X;
void add(int a, int b, int c) {
    if(a == 0 && b == 0) return;
    if(a == 0) {
        double t = -c*1.0/b;
        if(t>=0&&t<=100)X.push_back(t); return;
    }
    LL deta = b*b-4LL*a*c;
    if(deta < 0) return;
    if(deta==0) {
        double t = -b/2.0/a;
        if(t>=0 && t<=100) X.push_back(t);
    }
    else {
        double t1=(-b+sqrt(deta))/(2.0*a);
        double t2=(-b-sqrt(deta))/(2.0*a);
        if(t1>=0&&t1<=100)X.push_back(t1);
        if(t2>=0&&t2<=100)X.push_back(t2);
    }
}
int A[N], B[N], C[N], n;
int best;
double F(double x) {
    return sqrt(1+(x*2.0*A[best]+B[best])*(x*2.0*A[best]+B[best]));
}
double simpson(double a, double b) {
    double c = a + (b-a)/2;
    return (F(a)+4*F(c)+F(b))*(b-a)/6;
}
double simpson(double a, double b, double eps, double A) {
    double c = a + (b-a)/2;
    double L = simpson(a, c), R = simpson(c, b);
    if(fabs(L+R-A) <= 15*eps) return L+R+(L+R-A)/15.0;
    return simpson(a, c, eps/2, L) + simpson(c, b, eps/2, R);
}
double simpson(double a, double b, double eps) {
    return simpson(a, b, 1e-8, simpson(a,b));
}
int get_best(double x) {
    int ret = 0; double mm = x*x*A[0]+x*B[0]+C[0];
    for(int i=1;i<n;++i) {
        double tt = x*x*A[i]+x*B[i]+C[i];
        if(tt<mm){ mm=tt, ret=i; }
    }
    return ret;
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d", &n);
        for(int i=0;i<n;++i) {
            int k,a,b;
            scanf("%d%d%d",&k,&a,&b);
            A[i]=k;
            B[i]=-2*a*k;
            C[i]=k*a*a+b;
        }
        A[n]=B[n]=0;C[n++]=100;
        X.clear();
        for(int i=0;i<n;++i)for(int j=i+1;j<n;++j)
            add(A[i]-A[j], B[i]-B[j], C[i]-C[j]);
        X.push_back(0);X.push_back(100);
        sort(X.begin(), X.end());
        double ans = 0;
        for(int i=0;i+1<X.size();++i) {
            double x1 = X[i], x2 = X[i+1];
            if(x2-x1<1e-8) continue;
            double mid = (x1+x2)/2;
            best = get_best(mid);
            ans += simpson(x1, x2, 1e-8);
        }
        printf("%.2f\n", ans);
    }
    return 0;
}
