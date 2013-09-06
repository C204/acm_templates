/**
*HDU3966
*树链剖分
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#pragma comment(linker, "/STACK:36777216")
const int N = 50010;
vector<int> G[N];
int C[N], n;
int lowbit(int x) {return x&(-x);}
int sum(int x) {
    int ret = 0; for(;x<=n;x+=lowbit(x)) ret+=C[x];
    return ret;
}
void add(int x, int t) {
    for(;x;x-=lowbit(x)) C[x]+=t;
}
void add(int x, int y, int t) {
    if(x < y) swap(x, y);
    add(x, t); add(y-1, -t);
}
struct treeList {
    int size[N], dep[N], son[N], fa[N];
    int top[N], w[N], tim;
    void dfs(int u, int f=0) {
        size[u] = 1; fa[u] = f; son[u] = 0;
        dep[u]=f?dep[f]+1:0;
        for(int i=0,t=0;i<G[u].size();++i) {
            int v = G[u][i]; if(v==f) continue;
            dfs(v, u); size[u] += size[v];
            if(t<size[v]) t=size[son[u]=v];
        }
    }
    void dfs1(int u, int f=0) {
        top[u]=son[f]==u?top[f]:u;
        w[u] = ++tim;
        if(son[u]) dfs1(son[u], u);
        for(int i=0,t=0;i<G[u].size();++i) {
            int v = G[u][i]; if(v==f||v==son[u]) continue;
            dfs1(v, u);
        }
    }
    void init() { tim=0;dfs(1); dfs1(1);}
    int lca(int u, int v, void f(int, int, int), int k) {
        int tu = top[u], tv = top[v];
        if(tu == tv) {
            f(w[u], w[v], k);
            return dep[u]<dep[v]?u:v;
        }
        if(dep[tu]>dep[tv]) f(w[u], w[tu], k);
        else                f(w[v], w[tv], k);
        return dep[tu]>dep[tv]?lca(fa[tu], v, f, k):lca(u, fa[tv], f, k);
    }
}TL;
int a[N];
int main () {
    int m, q;
    while(scanf("%d%d%d",&n,&m,&q)!=EOF) {
        for(int i=1;i<=n;++i) scanf("%d", &a[i]), C[i]=0;
        for(int i=0;i<m;++i) {
            int u, v; scanf("%d%d",&u,&v);
            G[u].push_back(v); G[v].push_back(u);
        }
        TL.init();for(int i=1;i<=n;++i) add(TL.w[i], TL.w[i], a[i]);
        while(q--) {
            char cmd[4]; scanf("%s", cmd);
            if(cmd[0] != 'Q') {
                int l, r, k; scanf("%d%d%d",&l,&r,&k);
                if(cmd[0] == 'D') k = -k;
                TL.lca(l, r, add, k);
            }
            else {
                int x; scanf("%d", &x);
                printf("%d\n", sum(TL.w[x]));
            }
        }
        for(int i=1;i<=n;++i) G[i].clear();
    }
    return 0;
}
