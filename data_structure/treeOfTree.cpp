/**
*zoj 2112
*BIT套splay
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 50010;
struct Node {
    Node *ch[2], *p; int sz;
    int key, cnt;
    void init() {sz=cnt=1;p=ch[0]=ch[1]=NULL;}
    bool d() { return p->ch[1]==this; }
    void setc(int d, Node *x) { ch[d]=x;if(x)x->p=this; }
    void upd() {
        sz = cnt;
        if(ch[0]) sz += ch[0]->sz;
        if(ch[1]) sz += ch[1]->sz;
    }
    void relax() {}
}mem[N*22], *cur=mem, *root;
Node* maken(int key) {
    cur->init(); cur->key = key;
    return cur++;
}
void rot(Node *x) {
    Node *y=x->p, *z=y->p;
    y->relax();x->relax();
    int d=x->d();
    if(z) z->setc(y->d(), x);
    y->setc(d, x->ch[!d]); x->setc(!d, y); y->upd();
    if(!z) root=x, x->p=NULL;
}
void splay(Node *x, Node *f=NULL) {
    while(x->p!=f) rot(x); x->upd();
}
Node *find(int key) {
    Node *rt = root; int d;
    while(true) {
        if(rt->key == key) return rt;
        rt = rt->ch[key>rt->key];
        if(!rt) return NULL;
    }
}
void insert(int key) {
    if(!root) {
        root = maken(key);
        return ;
    }
    Node *x = find(key);
    if(x) { x->cnt++; splay(x); return; }
    x = maken(key);
    Node *rt = root; int d;
    while(rt->ch[d=x->key>rt->key]) rt = rt->ch[d];
    rt->setc(d, x); splay(x);
}
Node *next(Node *x) {
    if(!x->ch[1]) { while(x->d()) x=x->p; return x->p; }
    x=x->ch[1]; while(x->ch[0])x=x->ch[0]; return x;
}
Node *prev(Node *x) {
    if(!x->ch[0]) { while(!x->d()) x=x->p; return x->p; }
    x=x->ch[0]; while(x->ch[1])x=x->ch[1]; return x;
}
void erase(int key) {
    Node *x = find(key);
    if(x->cnt>1) { x->cnt--; splay(x); return; }
    Node *l=prev(x), *r=next(x);
    splay(l), splay(r, l);
    r->setc(0, NULL);r->upd();l->upd();
}
int rank(Node *x, int k) {
    if(!x) return 0;
    if(k<x->key) return rank(x->ch[0], k);
    int tm = x->ch[0]?x->ch[0]->sz:0;
    return tm+x->cnt+rank(x->ch[1], k);
}
Node* spt[N];
int a[N], n;
int lowbit(int x) {return x&(-x);}
int sum(int x, int K) {
    int ret=0;
    for(;x;x-=lowbit(x)) {
        root = spt[x];
        ret += rank(root, K)-1;
        spt[x] = root;
    }
    return ret;
}
void ins(int x, int ne) {
    for(;x<=n;x+=lowbit(x)) {
        root = spt[x];
        insert(ne);
        spt[x] = root;
    }
}
void del(int x, int old) {
    for(;x<=n;x+=lowbit(x)) {
        root = spt[x];
        erase(old);
        spt[x] = root;
    }
}
int main() {
    int T; scanf("%d", &T);
    while(T--) {
        int m; scanf("%d%d",&n,&m);
        cur = mem;
        for(int i=1;i<=n;++i) {
            root=spt[i]=NULL;
            insert(1000000001);
            insert(-1);
            spt[i]=root;
        }
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
    }
    return 0;
}
/**
2
5 3
3 2 1 4 7
Q 1 4 3
C 2 6
Q 2 5 3
5 3
3 2 1 4 7
Q 1 4 3
C 2 6
Q 2 5 3
*/
