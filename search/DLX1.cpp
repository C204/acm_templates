/**
* sjtu 1106
* soduku, 精确覆盖DLX
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1010;
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
    x->L->R = x->R;
    x->R->L = x->L;
    DD(a, x) RR(b, a) {
        b->U->D = b->D;
        b->D->U = b->U;
        SZ[b->C] --;
    }
}
void resume(Node *x) {
    x->L->R = x->R->L = x;
    UU(a, x) LL(b, a) {
        b->U->D = b->D->U = b;
        SZ[b->C] ++;
    }
}
int ans;
void Dance(int k) {
    if(mem->R == mem) {
        ans ++; return ;
    }
    int sz = N; Node *c;
    RR(i, mem) if(sz > SZ[i->C])
        sz = SZ[i->C], c = i;
    remove(c);
    DD(a, c) {
        RR(b, a) remove(C[b->C]);
        Dance(k+1); if(ans>1) return;
        LL(b, a) resume(C[b->C]);
    }
    resume(c);
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
void place(int i, int j, int k) {
    int x, y[4];
    x = (i*9 + j)*9 + k;
    y[0] = i*9 + j + 1;
    y[1] = 81 + i*9 + k;
    y[2] = 162 + j*9 + k;
    y[3] = 243 + (i/3*3+j/3)*9 + k;
    for(int t=0;t<4;++t) Link(x, y[t]);
}
int a[100];
void InitG() {
    cur=mem; memset(C, 0, sizeof C); memset(H, 0, sizeof H);
    int n = 729, m = 324; ans = 0;
    for(int i=0;i<=m;++i) Link(0, i);
    for(int i=0;i<81;++i) {
        if(a[i]) place(i/9, i%9, a[i]);
        else for(int j=1;j<=9;++j) place(i/9, i%9, j);
    }
}
int main () {
    int T;cin >> T;
    while(T --) {
        for(int i=0;i<81;++i)cin >> a[i];
        InitG();
        Dance(0);
        if(ans == 1) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}
