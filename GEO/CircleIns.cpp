/**
* HDU 3264
* 圆交
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

struct Point {
    double x, y;
    Point(double _x=0, double _y=0) {x=_x,y=_y;}
    void read() { scanf("%lf%lf",&x,&y); }
    void write() { cout<<x<<" "<<y<<endl; }
    Point operator-(Point p){return Point(x-p.x,y-p.y);}
    Point operator+(Point p){return Point(x+p.x,y+p.y);}
    Point operator*(double p){return Point(x*p,y*p);}
    Point operator/(double p){return Point(x/p,y/p);}
    Point rot() { return Point(-y, x); }
    double abs() { return sqrt(x*x + y*y); }
    double dot(Point p) { return x*p.x+y*p.y; }
    double atan() { return atan2(y, x); }
};
const double eps = 1e-8;
const double PI = acos(-1.0);
int sig(double t) {return t<-eps?-1:t>eps;}
const int N = 22;
double ins(Point p1, double r1, Point p2, double r2) {
    double R = max(r1, r2), r = min(r1, r2);
    double d = (p1-p2).abs();
    if( R+r+eps <= d ) return 0;
    if( R-r >= d+eps ) return r*r*PI;
    double a = acos((R*R+d*d-r*r)/(2*R*d));
    double b = acos((r*r+d*d-R*R)/(2*r*d));
    return a*R*R+b*r*r-R*d*sin(a);
}
Point p[N];double r[N]; int n;
double get(int c, double low, double high) {
    while(low + eps < high) {
        double mid = ( low + high ) / 2;
        int flag = 1;
        for(int i=0;i<n&&flag;++i) if(i!=c) {
            double area = ins(p[c], mid, p[i], r[i]);
            if( area + eps < r[i]*r[i]*PI/2 ) flag = 0;
        }
        if(flag) high = mid;
        else low = mid;
    }
    return low;
}
int main () {
    int T;
    scanf("%d", &T);
    while(T --) {
        scanf("%d", &n);
        for(int i=0;i<n;++i) p[i].read(), scanf("%lf",&r[i]);
        if(n == 1) {
            printf("%.4f\n", r[0]/sqrt(2));
            continue;
        }
        double ans = 1e100;
        for(int i=0;i<n;++i) ans = min(ans, get(i, r[i], 60000));
        printf("%.4f\n", ans);
    }
    return 0;
}
