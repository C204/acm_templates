/**
*POJ 1741
*树分治
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int N = 10010;
const int INF = ~0U>>1;
vector<pair<int, int> > G[N];
int vis[N], ans, listot, core, corecnt;
int lis[N], sons[N], n, k;

void coredfs(int u, int v) {
    sons[u] = 1;
    for(int i=0;i<G[u].size();++i) {
        int go = G[u][i].first;
        if(go==v || vis[go]) continue;
        coredfs(go, u);
        sons[u] += sons[go];
    }
}
void coreedit(int u, int v, int cnt) {
    int ret = 1;
    for(int i=0;i<G[u].size();++i) {
        int go = G[u][i].first;
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
void rushDis(int u, int len, int v) {
    lis[listot++] = len;
    for(int i=0;i<G[u].size();++i) {
        int g=G[u][i].first;
        if(g!=v && !vis[g]) rushDis(g, len+G[u][i].second, u);
    }
}
int calc(int u, int len) {
    int ret = 0;
    listot = 0;
    rushDis(u, len, 0);
    sort(lis, lis+listot);
    int head=0, tail=listot-1;
    while(head<tail) {
        while(head<tail&&lis[head]+lis[tail]>k)tail--;
        ret += tail-head;
        head++;
    }
    return ret;
}
void dfs(int u) {
    Qcore(u);
    ans+=calc(u=core, 0);
    vis[u]=1;
    for(int i=0;i<G[u].size();++i) {
        int g = G[u][i].first;
        if(!vis[g]) {
            ans-=calc(g, G[u][i].second);
            dfs(g);
        }
    }
}
int main () {
    while(scanf("%d%d",&n,&k)!=EOF) {
        if(!n || !k) break;
        for(int i=1;i<=n;++i) G[i].clear();
        for(int i=1;i<n;++i) {
            int u, v, l; scanf("%d%d%d",&u,&v,&l);
            G[u].push_back(make_pair(v, l));
            G[v].push_back(make_pair(u, l));
        }
        memset(vis, 0, sizeof vis);
        ans = 0;
        dfs(1);
        printf("%d\n", ans);
    }
    return 0;
}
