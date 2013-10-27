/**
* hdu 4757
* 主席树
**/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int N = 100010;
const int M = 2000020;
vector<int> G[N];
int up[N][20], L[N], n;
int root[N], U[M][2], V[M], cur;
int maken() {
    memset(U[cur], 0, sizeof U[cur]);
    V[cur] = 0;
    return cur++;
}
void insert(int x, int y, int val) {
    x = root[x], y = root[y];
    for(int i=0;i<16;++i) {
        int c = val >> (16-i-1) & 1;
        if( !U[x][c] )
            U[x][c] = maken(), U[x][!c] = U[y][!c], V[U[x][c]] = V[U[y][c]];
        x = U[x][c], y = U[y][c];
        ++ V[x];
    }
}
int a[N];
int query(int x, int y, int z, int val) {
    int ans = 0, res = a[z] ^ val;
    x = root[x], y = root[y], z = root[z];
    for(int i=0;i<16;++i) {
        int c = !(val>>(16-i-1)&1);
        if(V[ U[x][c] ]+V[ U[y][c] ]-2*V[ U[z][c] ])
            ans |= 1<<(16-i-1);
        else c = !c;
        x = U[x][c], y = U[y][c], z = U[z][c];
    }
    return max(ans, res);
}
void dfs(int x, int fa) {
    up[x][0]=fa, L[x]=L[fa]+1;
    root[x] = maken();
    insert(x, fa, a[x]);
    for(int i=0;i<G[x].size();++i)
        if(G[x][i] != fa)
            dfs(G[x][i], x);
}
void initLCA() {
    for(int i=1;i<=16;++i)
        for(int x=1;x<=n;++x)
            up[x][i] = up[ up[x][i-1] ][i-1];
}
int LCA(int x, int y) {
    if(L[x] > L[y]) swap(x, y);
    for(int i=16;i>=0;--i) if(L[y]-L[x]>=1<<i)
        y = up[y][i];
    if(x == y) return x;
    for(int i=16;i>=0;--i) if(up[x][i]&&up[x][i]!=up[y][i])
        x=up[x][i], y=up[y][i];
    return up[x][0];
}
int main() {
    int m;
    while(scanf("%d%d",&n,&m)!=EOF) {
        for(int i=1;i<=n;++i) scanf("%d", &a[i]);
        for(int i=1;i<n;++i) {
            int x, y;scanf("%d%d",&x,&y);
            G[x].push_back(y);
            G[y].push_back(x);
        }
        cur = 1; dfs(1, 0); initLCA();
        while(m --) {
            int x, y, w;
            scanf("%d%d%d",&x,&y,&w);
            int z = LCA(x, y);
            //cout << "z " << z << endl;
            printf("%d\n", query(x, y, z, w));
        }
        for(int i=1;i<=n;++i) G[i].clear();
    }
    return 0;
}
/*
3 2
1 2 2
1 2 2 3
1 3 1
2 3 2
*/
