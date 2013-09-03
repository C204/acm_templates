/**
*http://61.187.179.132/JudgeOnline/problem.php?id=1061
*志愿者招募
*单纯形( 考虑对偶更好做
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)
const int MAX_R = 1010, MAX_C = 10010;
const double INF = 1e100;
const double eps = 1e-8;

double a[MAX_R][MAX_C];
struct Simplex {
    int n, m;
    int db[MAX_R], dn[MAX_C], next[MAX_C];
    void pivot(int l, int e) {
        swap(db[l], dn[e]);
        int t = MAX_C-1; double tm = -a[l][e]; a[l][e] = -1;
        rep(i,0,m) if(abs(a[l][i]/=tm)>eps) t=next[t]=i; next[t]=-1;
        rep(i,0,n) if(i!=l && abs(tm=a[i][e])>eps) {
            a[i][e] = 0;
            for(int j=next[MAX_C-1];j!=-1;j=next[j])a[i][j]+=tm*a[l][j];
        }
    }
    void solve() {
        double tmax, t;int l,e;
        while(1) {
            l = e = 0, tmax = -INF;
            for(e=m;e;--e) if(a[0][e]>eps) break; if(!e) return;
            rep(i,1,n) if(a[i][e]<-eps&&(t=a[i][0]/a[i][e])>tmax)tmax=t,l=i;
            if(!l) return;
            pivot(l, e);
        }
    }
    bool ini() {
        double tmin=INF; int l=0;
        rep(i,1,n) if(a[i][0]<tmin) tmin=a[i][0],l=i;
        if(tmin>eps) return true;
        memcpy(a[n+1], a[0], sizeof a[0]); ++m;
        rep(i,1,m) dn[i]=i; rep(i,1,n) db[i]=m+i;
        memset(a[0], 0, sizeof a[0]);
        a[0][m]=-1;rep(i,1,n)a[i][m]=1;pivot(l,m);solve();
        if(a[0][0]<-eps) return false;
        memset(a[0], 0, sizeof a[0]);
        rep(i,1,m) if(dn[i]==m) {
            rep(j,1,n)a[j][i]=a[j][m];
            dn[i]=dn[m--]; break;
        }
        rep(i,1,m)if(dn[i]<=m)a[0][i]+=a[n+1][dn[i]];
        rep(i,1,n)if(db[i]<=m)rep(j,0,m)
            a[0][j]+=a[i][j]*a[n+1][db[i]];
        return true;
    }
}sim;

int main () {
    int n, m;
    scanf("%d%d",&m,&n);
    sim.n = m; sim.m = n;
    rep(i,1,m) scanf("%lf",&a[i][0]),a[i][0]=-a[i][0];
    rep(j,1,n) {
        int s,t,c; scanf("%d%d%d",&s,&t,&c);
        rep(i,s,t)a[i][j] = 1;
        a[0][j]=-c;
    }
    sim.ini(); sim.solve();
    printf("%.0f\n",-a[0][0]+eps);
    return 0;
}
