/**
*zoj 2112
*BIT套treap
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 50010;
const int INF = ~0U>>1;
#define sz(x) (x?x->size:0)
#define key(x) (x?x->key:INF)
struct Node {
    Node*c[2];
    int value, key, size, cnt;
    Node(){}
    Node(int v,Node*n=NULL) {
        value=v;key=rand()-1;cnt=size=1;
        c[0]=c[1]=n;
    }
    void upd() { size=cnt+sz(c[0])+sz(c[1]);}
};
void rot(Node *&t, bool d) {
    Node *c=t->c[d];
    t->c[d]=c->c[!d];
    c->c[!d]=t;
    t->upd();c->upd();
    t=c;
}
void insert(Node *&t, int x) {
    if(!t){t=new Node(x); return;}
    if(x==t->value) {t->cnt++; t->upd(); return;}
    bool d=x>t->value;
    insert(t->c[d], x);
    if(t->c[d]->key<t->key) rot(t, d);
    else  t->upd();
}
void erase(Node *&t, int x) {
    if(!t) return;
    if(t->value==x) {
        if(t->cnt>1) { t->cnt--; t->upd(); return; }
        bool d=key(t->c[1])<key(t->c[0]);
        if(!t->c[d]) {
            delete t; t=NULL; return;
        }
        rot(t, d);
        erase(t->c[!d], x);
    }
    else {
        bool d=x>t->value;
        erase(t->c[d], x);
    }
    t->upd();
}
int select(Node *t, int k) {
    if(k>sz(t)) return -INF;
    int r=sz(t->c[0]);
    if(k==r) return t->value;
    if(k<r) return select(t->c[0], k);
    return select(t->c[1], k-r-1);
}
int rank(Node *t, int x) {
    if(!t) return 0;
    int r=sz(t->c[0]);
    if(x<t->value) return rank(t->c[0],x);
    return r+t->cnt+rank(t->c[1],x);
}
void del(Node *&x) {
    if(x->c[0]) del(x->c[0]);
    if(x->c[1]) del(x->c[1]);
    delete x;
}
Node* tp[N];
int a[N], n;
int lowbit(int x) {return x&(-x);}
int sum(int x, int K) {
    int ret=0;
    for(;x;x-=lowbit(x)) ret += rank(tp[x], K);
    return ret;
}
void ins(int x, int ne) {
    for(;x<=n;x+=lowbit(x)) insert(tp[x], ne);
}
void del(int x, int old) {
    for(;x<=n;x+=lowbit(x)) erase(tp[x], old);
}
int main() {
    int T; scanf("%d", &T);
    while(T--) {
        int m; scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) tp[i] = NULL;
        for(int i=1;i<=n;++i) scanf("%d",&a[i]), ins(i, a[i]);
        char cmd[3];
        while(m--) {
            scanf("%s", cmd);
            if(cmd[0]=='Q') {
                int l, r, k; scanf("%d%d%d",&l,&r,&k);
                int low=0, high=1000000000;
                while(low<high-1) {
                    int mid = low+high>>1;
                    if(sum(r, mid)-sum(l-1, mid)<k) low=mid;
                    else high = mid;
                }
                printf("%d\n", high);
            }
            else {
                int x, v; scanf("%d%d",&x,&v);
                ins(x, v);del(x, a[x]); a[x] = v;
            }
        }
        for(int i=1;i<=n;++i) del(tp[i]);
    }
    return 0;
}
