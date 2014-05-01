#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 110010;
typedef long long LL;

struct node {
    node *c[2], *p, *mx;
    int sz, rev, val;

    void rz() {
        sz = c[0]->sz + 1 + c[1]->sz;
        if(c[0]->mx->val > c[1]->mx->val)
            mx = c[0]->mx;
        else mx = c[1]->mx;
        if(val > mx->val) mx = this;
    }
    void revIt() {
        swap(c[0], c[1]);
        rev ^= 1;
    }
    void down() {
        if(rev) {
            c[0]->revIt();
            c[1]->revIt();
            rev = 0;
        }
    }
    bool root() {
        return p->c[0] != this && p->c[1] != this;
    }
    bool d() {
        return p->c[1] == this;
    }
    void setc(int d, node *x) {
        //down();
        (c[d]=x)->p = this;
        rz();
    }
}null[N];

void rotate(node *x) {
    node *p = x->p;
    int d = x->d();
    p->setc(d, x->c[!d]);
    if(p->root())
        x->p = p->p;
    else
        p->p->setc(p->d(), x);
    x->setc(!d, p);
}

void push_down(node *x) {
    if(!x->root()) push_down(x->p);
    x->down();
}

void push_up(node *x) {
    x->rz();
    if(!x->root()) push_up(x->p);
}

void splay(node *x) {
    push_down(x);
    while(!x->root()) {
        if(x->p->root()) rotate(x);
        else if(x->p->d() == x->d())
            rotate(x->p), rotate(x);
        else rotate(x), rotate(x);
    }
}

void expose(node *x) {
    for(node *y=null;x!=null;y=x,x=x->p) {
        splay(x);
        x->setc(1, y);
    }
    null->p = null;
}

void make_root(node *x) {
    expose(x); splay(x);
    x->revIt();
}

void connect(node *x, node *y) {
    make_root(x);
    x->p = y;
}

void destroy(node *x, node *y) {
    expose(x); splay(y);
    if(y->p == x)
        y->p = null;
    else expose(y), splay(x), x->p = null;
}

int n, m;

int get_max(node *x, node *y) {
    make_root(x);
    expose(y); splay(y);
    return y->mx - null - n;
}

struct Edge {
    int x, y, w, id;
    bool operator < (const Edge e) const {
        return w < e.w;
    }
}edge[N], sedge[N];

int fa[N];
bool se[N];

int find(int x) {
    return fa[x] == x ? x : find(fa[x]);
}

int main() {
    freopen("tube.in", "r", stdin);
    freopen("tube.out", "w", stdout);

    null->p = null->c[0] = null->c[1] = null->mx = null;
    null->sz = null->rev = null->val = 0;

    while(scanf("%d%d",&n,&m)!=EOF) {
        if(n == 0 && m == 0) break;

        for(int i=1;i<=n;++i) {
            node *x = null + i;
            x->p = x->c[0] = x->c[1] = null; x->mx = x;
            x->sz = 1; x->rev = x->val = 0;
        }

        for(int i=1;i<=m;++i) {
            scanf("%d%d%d",&edge[i].x, &edge[i].y, &edge[i].w);
            edge[i].id = i;
            sedge[i] = edge[i];
            se[i] = false;
        }

        for(int i=1;i<=m;++i) {
            node *x = null + n + i;
            x->p = x->c[0] = x->c[1] = null; x->mx = x;
            x->sz = 1; x->rev = 0;
            x->val = edge[i].w;
        }

        LL ans = 0;
        for(int i=1;i<=n;++i) fa[i] = i;
        sort(sedge + 1, sedge + 1 + m);
        for(int i=1;i<=m;++i) {
            int x = sedge[i].x, y = sedge[i].y;
            if(find(x) != find(y)) {
                se[sedge[i].id] = true;

                connect(null+x, null+n+sedge[i].id);
                connect(null+y, null+n+sedge[i].id);

                fa[find(x)] = find(y);
                ans += sedge[i].w;
            }
        }
        cout << ans << endl;
        int q; scanf("%d", &q);
        while(q --) {
            int num, w;
            scanf("%d%d",&num, &w);
            if(se[num])
                ans -= edge[num].w - w;
            else {
                int x = edge[num].x, y = edge[num].y;
                int z = get_max(null+x, null+y);
                if(edge[z].w > w) {
                    se[z] = false;
                    se[num] = true;
                    ans -= edge[z].w - w;
                    destroy(null+edge[z].x, null+n+z);
                    destroy(null+edge[z].y, null+n+z);
                    connect(null+x, null+n+num);
                    connect(null+y, null+n+num);
                }
            }
            edge[num].w = w;
            null[num+n].val = w;
            push_up(null+num+n);
            cout << ans << endl;
        }
        puts("");
    }
    return 0;
}
/*
2 1
1 2 3
1
1 1
5 6
1 2 5
2 3 3
1 4 11
2 4 6
3 5 9
4 5 12
3
3 3
2 1
6 8
0 0
*/
