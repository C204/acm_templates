/*
*POJ 2187
*凸包+旋转卡壳
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int N = 50050;
const double eps = 1e-8;
int sig(double t) {return t<-eps?-1:t>eps;}
struct Point {
    double x, y;
    Point(){}
    Point(double _x,double _y){x=_x,y=_y;}
    void read(){scanf("%lf%lf",&x,&y);}
    void write(){printf("(%lf,%lf)\n",x,y);}
    Point operator-(Point p){return Point(x-p.x,y-p.y);}
    Point operator+(Point p){return Point(x+p.x,y+p.y);}
    Point operator*(double t){return Point(x*t,y*t);}
    Point operator/(double t){return Point(x/t,y/t);}
    bool operator==(Point p){return !sig(x-p.x)&&!sig(y-p.y);}
    double abs2() {return x*x+y*y;}
    bool operator<(Point p) const {
        if(!sig(y-p.y)) return x<p.x;
        return y < p.y;
    }
};
double cross(Point a, Point b) { return a.x*b.y-a.y*b.x; }
void graham(Point p[], int n, Point g[], int &top) {
    static Point s[N];
    for(int i=0;i<n;++i) s[i] = p[i];
    sort(s, s+n);
    top = 0;
    for(int i=0;i<n;++i) {
        while(top>=2 && sig(cross(s[i]-g[top-1], g[top-2]-g[top-1]))<=0)top--;
        g[top++] = s[i];
    }
    int up = top;
    for(int i=n-2;i>=0;--i) {
        while(top-up>=1 && sig(cross(s[i]-g[top-1], g[top-2]-g[top-1]))<=0)top--;
        g[top++] = s[i];
    }
    top--;
}
Point p[N], g[N];
int main () {
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;++i) p[i].read();
    int m;
    graham(p, n, g, m);
    //for(int i=0;i<m;++i) g[i].write();
    double ans = 0;
    for(int i=0,t=1;i<m;++i) {
        while(cross(g[t]-g[t+1],g[i]-g[i+1]) < 0)
            t = (t+1) % m;
        ans = max(ans, (g[i]-g[t]).abs2());
        ans = max(ans, (g[i+1]-g[t+1]).abs2());
    }
    printf("%.0f\n", ans);
    return 0;
}
