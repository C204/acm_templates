/**
* HDU3487
* http://codeforces.com/contest/295/problem/E
* splay
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int INF = 1LL<<30;
const int N = 300020;

struct Node {
    Node *ch[2], *p; int sz;
    int key, rev;
    void init() {sz=1;p=ch[0]=ch[1]=NULL;rev=0;}
    bool d() { return p->ch[1]==this; }
    void setc(int d, Node *x) { ch[d]=x;if(x)x->p=this; }
    //void addIt(int ad) {key+=ad;add+=ad;mx+=ad;}
    void upd() {
        sz = 1;
        if(ch[0]) sz += ch[0]->sz;
        if(ch[1]) sz += ch[1]->sz;
    }
    void relax() {
        if(rev) {
            swap(ch[0], ch[1]); rev = 0;
            if(ch[0]) ch[0]->rev ^= 1;
            if(ch[1]) ch[1]->rev ^= 1;
        }
    }
}mem[N], *cur=mem, *root;
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
//  while(x->p!=f)
//      if(x->p->p!=f) x->d()==x->p->d()?rot(x->p):rot(x);rot(x);
//  x->upd();
}
Node *next(Node *x) {
    if(!x->ch[1]) { while(x->d()) x=x->p; return x->p; }
    x=x->ch[1]; while(x->ch[0])x=x->ch[0]; return x;
}
Node *prev(Node *x) {
    if(!x->ch[0]) { while(!x->d()) x=x->p; return x->p; }
    x=x->ch[0]; while(x->ch[1])x=x->ch[1]; return x;
}
void insert(Node *x) {
    Node *rt = root; int d;
    while(rt->ch[d=x->key>rt->key]) rt = rt->ch[d];
    rt->setc(d, x); splay(x);
}
void erase(Node *x) {
    Node *l=prev(x), *r=next(x);
    splay(l), splay(r, l);
    r->setc(0, NULL);r->upd();l->upd();
}
Node *find(int key) {
    Node *x=root;
    while(1) {
        if(x->key==key||!x->ch[key>x->key]) return x;
        x=x->ch[key>x->key];
    }
}
Node *select(int k) {
    Node *x=root;
    while(true) {
        x->relax();
        int tmp = x->ch[0]?x->ch[0]->sz:0;
        if(k == tmp) break;
        if(k < tmp) x = x->ch[0];
        else x = x->ch[1], k-=tmp+1;
    }
    return x;
}
int a[N], ac;
void display(Node *x=root) {
    x->relax();
    if(x->ch[0]) display(x->ch[0]);
    a[ac++] = x->key;
    if(x->ch[1]) display(x->ch[1]);
}
Node *build(int l, int r) {
    if(l > r)  return NULL;
    int m = (l + r) >> 1;
    Node *x = maken(m);
    x->setc(0, build(l, m-1));
    x->setc(1, build(m+1, r));
    x->upd();
    return x;
}
int main() {
    int n, m;
    while(scanf("%d%d",&n,&m)!=EOF) {
        if(n<0&&m<0) break;
        cur = mem; root = build(0, n+1);
        char cmd[8];
        while(m--) {
            int l, r;
            scanf("%s%d%d",cmd,&l,&r);
            Node *L = select(l-1), *R = select(r+1);
            splay(L); splay(R, L); Node *want = R->ch[0];
            if(cmd[0] == 'C') {
                int pos; scanf("%d",&pos);
                R->setc(0,NULL);R->upd(); L->upd();
                L = select(pos); R = select(pos+1);
                splay(L); splay(R, L);
                R->setc(0,want); R->upd(); L->upd();
            }
            else
                if(want)want->rev ^= 1;
        }
        ac=0; display();
        for(int i=1;i<n;++i) printf("%d ", a[i]);
        printf("%d\n", a[n]);
    }
    return 0;
}
