/*
* POJ 3575
* 线段圆交
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const double eps = 1e-8;
const double PI = acos(-1.0);
int sig(double x) { return x<-eps?-1:x>eps; }
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
    double operator/(Point p){
        if(sig(p.x)) return x/p.x;
        if(sig(p.y)) return y/p.y;
    }
    double abs() { return hypot(x, y); }
    double dot(Point p) { return x*p.x+y*p.y; }
    double atan() { return atan2(y, x); }
    double dis(Point a, Point b) {
        Point e = (a-b).rot();
        return fabs( e.dot(a-*this)/e.abs() );
    }
};
double cross(Point a, Point b) { return a.x*b.y-a.y*b.x; }
Point isSS(Point a, Point b, Point c, Point d) {
    double l=cross(a-c,b-c), r=-cross(a-d,b-d);
    return (d*l+c*r)/(l+r);
}
void CL_ins(double r, Point a, Point b, Point ret[], int &num) {
    num = 0; Point c = b - a;
    ret[num++] = a;
    double A = c.x*c.x+c.y*c.y;
    double B = 2*( a.x*c.x+a.y*c.y );
    double C = a.x*a.x+a.y*a.y-r*r;
    double deta = B*B - 4*A*C;
    if( sig(deta)==0 ) {
        double t = -B / (2*A);
        if( sig(t)>0 && sig(1-t)>0 ) ret[num++] = a+c*t;
    }
    else if( sig(deta) > 0 )  {
        double t = ( -B - sqrt(deta) ) / (2*A);
        if( sig(t)>0 && sig(1-t)>0 ) ret[num++] = a+c*t;
        t = ( -B + sqrt(deta) ) / (2*A);
        if( sig(t)>0 && sig(1-t)>0 ) ret[num++] = a+c*t;
    }
    ret[num++] = b;
}
double CT_ins(double r, Point a, Point b) {
    static Point ret[4]; int num; double res = 0;
    CL_ins(r, a, b, ret, num);
    for(int i=0;i<num-1;++i) {
        double l1 = ret[i].abs(), l2 = ret[i+1].abs();
        if( sig(l1-r)>0 || sig(l2-r)>0 ) {
            double al = acos(ret[i].dot(ret[i+1])/l1/l2);
            res += al*r*r/2;
        }
        else res += fabs(cross(ret[i], ret[i+1]))/2;
    }
    return fabs(res);
}
const int N = 55;
Point p[N];
int main () {
    double r; int n;
    while(scanf("%lf%d",&r,&n)!=EOF) {
        for(int i=0;i<n;++i) p[i].read();p[n] = p[0];
        double ans = 0;
        for(int i=0;i<n;++i) {
            if( cross(p[i], p[i+1])>0 ) ans += CT_ins(r, p[i], p[i+1]);
            else ans -= CT_ins(r, p[i], p[i+1]);
        }
        printf("%.2f\n", fabs(ans));
    }
    return 0;
}
