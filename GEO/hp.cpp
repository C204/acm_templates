/*
*POJ 3335
*POJ 1279
*POJ 1474
*halfplane
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int N = 1511;
const double eps = 1e-8;
int sig(double t) {return t<-eps?-1:t>eps;}
struct Point {
    double x, y;
    Point(){}
    Point(double _x,double _y){x=_x,y=_y;}
    void read(){scanf("%lf%lf",&x,&y);}
    void write(){printf("(%lf,%lf)\n",x,y);}
    Point operator-(Point p)const{return Point(x-p.x,y-p.y);}
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
Point isSS(Point a, Point b, Point c, Point d) {
    double l=cross(a-c,b-c), r = -cross(a-d, b-d);
    return (c*r+d*l)/(r+l);
}
struct Border{
    Point a, b; double ang;
    Border(){}
    Border(Point _a,Point _b){a=_a,b=_b,ang=atan2(b.y-a.y,b.x-a.x);}
    void set(Point _a,Point _b){a=_a,b=_b,ang=atan2(b.y-a.y,b.x-a.x);}
    bool operator==(Border d) const {return !sig(ang-d.ang);}
    bool operator<(Border d) const {
        if(sig(ang-d.ang)) return ang < d.ang;
        return cross(b-d.a, a-d.a) > 0;
    }
};
Point isSS(Border a, Border b) {return isSS(a.a, a.b, b.a, b.b);}
int halfplane(Border b[], int n, Point hp[]) {
    static Border q[N];
    sort(b, b+n); n = unique(b, b+n) - b;
    int l=0,r=0;
    for(int i=0;i<n;++i) {
        while(l+1<r&&sig(cross(b[i].b-b[i].a,isSS(q[r-1],q[r-2])-b[i].b))<0) r--;
        while(l+1<r&&sig(cross(b[i].b-b[i].a,isSS(q[l],q[l+1])-b[i].b))<0) l++;
        q[r++] = b[i];
    }
    while(l+2<r&&sig(cross(q[l].b-q[l].a,isSS(q[r-1],q[r-2])-q[l].b))<0) r--;
    q[r] = q[l];
    int tot = 0;
    for(int i=l;i<r;++i) hp[tot++]=isSS(q[i], q[i+1]);
    return tot;
}
double getArea(Point p[], int n) {
    if(n < 3) return 0;
    double ret = 0;p[n] = p[0];
    for(int i=0;i<n;++i) ret += cross(p[i], p[i+1]);
    return ret/2;
}
Point p[N], hp[N];
Border b[N];
int main() {
    int T; scanf("%d", &T);
    while(T --) {
        int n; scanf("%d",&n);
        for(int i=0;i<n;++i) p[i].read();
        if(getArea(p, n) < 0)
            reverse(p, p+n); p[n]=p[0];
        for(int i=0;i<n;++i) b[i].set(p[i], p[i+1]);
        int tot = halfplane(b, n, hp);
        double ans = getArea(hp, tot);
        printf("%.2f\n", ans);
    }
    return 0;
}
