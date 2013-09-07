/*
* HDU 1724
* simpson 积分
*/
#include<cstdio>
#include<cmath>

double a,b,l,r;
// simpson公式用到的函数
double F(double x) {
  return sqrt(b*b*(1-x*x/(a*a)));
}
// 三点simpson法。这里要求F是一个全局函数
double simpson(double a, double b) {
  double c = a + (b-a)/2;
  return (F(a)+4*F(c)+F(b))*(b-a)/6;
}

// 自适应Simpson公式（递归过程）。已知整个区间[a,b]上的三点simpson值A
double asr(double a, double b, double eps, double A) {
  double c = a + (b-a)/2;
  double L = simpson(a, c), R = simpson(c, b);
  if(fabs(L+R-A) <= 15*eps) return L+R+(L+R-A)/15.0;
  return asr(a, c, eps/2, L) + asr(c, b, eps/2, R);
}

double solve() {
    return asr(l,r,1e-4,simpson(l,r))*2;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        double ans;
        scanf("%lf%lf%lf%lf",&a,&b,&l,&r);
        ans=solve();
        printf("%.3lf\n",ans);
  }
  return 0;
}
