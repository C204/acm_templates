/**
* hdu 2295
* 二分 支配集，DLX重复覆盖
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 55;
#define DD(i, x) for(Node *i=x->D;i!=x;i=i->D)
#define UU(i, x) for(Node *i=x->U;i!=x;i=i->U)
#define LL(i, x) for(Node *i=x->L;i!=x;i=i->L)
#define RR(i, x) for(Node *i=x->R;i!=x;i=i->R)
struct Node {
    int H, C;
    Node *U, *D, *L, *R;
}mem[N*N], *cur;
Node *C[N], *H[N];
int SZ[N];
void remove(Node *x) {
    DD(a, x) {
        a->R->L = a->L;
        a->L->R = a->R;
    }
}
void resume(Node *x) {
    DD(a, x)
        a->R->L = a->L->R = a;
}
int K;
int h() {
    bool hash[N]={0};
    int ret = 0;
    RR(a, mem) if(!hash[a->C]) {
        ret ++;
        DD(i, a) RR(j, i) hash[j->C] = 1;
    }
    return ret;
}
bool Dance(int k) {
    if(mem->R == mem) return true;
    if(k + h() > K) return false;
    int sz = N; Node *c; // sz设为INF
    RR(i, mem) if(sz > SZ[i->C])
        sz = SZ[i->C], c = i;
    DD(a, c) {
        remove(a);
        RR(b, a) remove(b), SZ[b->C]--;
        if(Dance(k+1)) return true;
        LL(b, a) resume(b), SZ[b->C]++;
        resume(a);
    }
    return false;
}
void Link(int h, int c) {
    cur->H = h; cur->C = c;
    if(!H[h]) H[h]=cur->L=cur->R=cur;
    else {
        cur->R = H[h]->R; H[h]->R = cur;
        cur->R->L = cur; cur->L = H[h];
    }
    if(!C[c]) C[c]=cur->U=cur->D=cur, SZ[c]=0;
    else {
        cur->D = C[c]->D; C[c]->D = cur;
        cur->D->U = cur; cur->U = C[c];
        SZ[c]++;
    }
    cur++;
}
int n, m;
double px[N], py[N], rx[N], ry[N];
void InitG(double R) {
    cur=mem; memset(C, 0, sizeof C); memset(H, 0, sizeof H);
    for(int i=0;i<=n;++i) Link(0, i);
    for(int i=1;i<=m;++i)
        for(int j=1;j<=n;++j) if( (rx[i]-px[j])*(rx[i]-px[j])+(ry[i]-py[j])*(ry[i]-py[j]) <= R*R )
            Link(i, j);
}
int main () {
    int T;scanf("%d", &T);
    while(T --) {
        scanf("%d%d%d", &n, &m, &K);
        for(int i=1;i<=n;++i) scanf("%lf%lf", &px[i], &py[i]);
        for(int i=1;i<=m;++i) scanf("%lf%lf", &rx[i], &ry[i]);
        double low=0, high=3044;
        while(high - low > 1e-7) {
            double mid = (low + high) / 2;
            InitG(mid);
            if( Dance(0) )   high = mid;
            else             low = mid;
        }
        printf("%.6f\n", low);
    }
    return 0;
}
