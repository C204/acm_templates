/**
* ZOJ 2334
* 左偏树
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 100010;

#define dis(a) (a?a->dis:-1)
struct Node {
    int s, dis;
    Node *l, *r;
    Node(int _s) {s=_s;l=r=NULL;dis=0;}
    void ini(){l=r=NULL;dis=0;}
    ~Node() { delete l; delete r; }
}*king[N];
Node *merge(Node *a, Node *b) {
    if(!a) return b;
    if(!b) return a;
    if(a->s < b->s) swap(a, b);
    a->r = merge(a->r, b);
    if( dis(a->l) < dis(a->r) )
        swap(a->l, a->r);
    a->dis = dis(a->r) + 1;
    return a;
}
int fa[N];
int getfa(int x) {
    return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
int main () {
    int n;
    while(scanf("%d",&n)!=EOF) {
        for(int i=1;i<=n;++i) {
            int t; scanf("%d",&t);
            king[i] = new Node(t);
            fa[i] = i;
        }
        int m; scanf("%d", &m);
        while(m --) {
            int a, b; scanf("%d%d",&a,&b);
            int ca=getfa(a), cb=getfa(b);
            if(ca==cb) puts("-1");
            else {
                Node *x = merge(king[ca]->l, king[ca]->r);
                Node *y = merge(king[cb]->l, king[cb]->r);
                king[ca]->ini(); king[cb]->ini();
                king[ca]->s /= 2;king[cb]->s /= 2;
                if(ca>cb) swap(ca, cb);
                fa[cb]=ca;
                king[ca]=merge(merge(x, y), merge(king[ca], king[cb]));
                printf("%d\n", king[ca]->s);
            }
        }
        for(int i=1;i<=n;++i) if(fa[i]==i) delete king[i];
    }
    return 0;
}
