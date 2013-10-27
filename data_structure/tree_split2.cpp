/**
*acdreamoj1031
*树分治
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

const int N = 2010;
const int INF = 1<<30;
vector<int> G[N];
int vis[N], core, corecnt;
int sons[N], n, k;
void coredfs(int u, int v) {
    sons[u] = 1;
    for(int i=0;i<G[u].size();++i) {
        int go = G[u][i];
        if(go==v || vis[go]) continue;
        coredfs(go, u);
        sons[u] += sons[go];
    }
}
void coreedit(int u, int v, int cnt) {
    int ret = 1;
    for(int i=0;i<G[u].size();++i) {
        int go = G[u][i];
        if(go==v || vis[go]) continue;
        coreedit(go, u, cnt);
        ret=max(ret, sons[go]);
    }
    ret = max(ret, cnt-sons[u]);
    if(ret<corecnt) {
        core=u;
        corecnt=ret;
    }
}
void Qcore(int u) {
    corecnt = INF;
    coredfs(u, 0);
    coreedit(u, 0, sons[u]);
}
int sz[N], W[N], tim;
void dfs(int u, int f=0) {
    sz[u] = 1; W[++tim] = u;
    for(int i=0;i<G[u].size();++i) {
        int v = G[u][i];
        if(v == f || vis[v]) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}
int a[N], dp[N][N], ans[N];
void calc(int u) {
    tim = 0; dfs(u);
    int m = tim;
    for(int i=1;i<=m;++i) dp[m+1][i] = INF;
    dp[m+1][0] = 0;
    for(int i=m;i>=1;--i) {
        int id = W[i];
        for(int j=0;j<=m;++j) {
            dp[i][j] = dp[i+sz[id]][j];
            if(j) dp[i][j] = min(dp[i][j], dp[i+1][j-1]+a[id]);
        }
    }
    for(int i=1;i<=m;++i) ans[i] = min(ans[i], dp[1][i]);
}
void divide(int u) {
    Qcore(u);
    calc(u=core);
    vis[u]=1;
    for(int i=0;i<G[u].size();++i) {
        int g = G[u][i];
        if(!vis[g]) divide(g);
    }
}
int main () {
    scanf("%d", &n);
    for(int i=1;i<=n;++i) G[i].clear();
    for(int i=1;i<=n;++i) scanf("%d", &a[i]);
    for(int i=1;i<n;++i) {
        int u, v; scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    memset(vis, 0, sizeof vis);
    for(int i=1;i<=n;++i) ans[i] = INF;
    divide(1);
    printf("%d", ans[1]);
    for(int i=2;i<=n;++i) printf(" %d", ans[i]);
    puts("");
    return 0;
}
