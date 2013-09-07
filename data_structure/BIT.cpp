#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 100010;

struct BIT {
        int C[N+N], n;
        void init(int _n=N+N-1) {
                n = _n;
                fill(C, C+1+n, 0);
        }
        int lowbit(int x) {return x & (-x);}
        void insert(int x) {
                int xx = x;
                for(;x<=n;x+=lowbit(x)) C[x] ++;
        }
        void remove(int x) {
                for(;x<=n;x+=lowbit(x)) C[x] --;
        }
        int rank(int x) {
                int ret = 0;
                for(;x;x-=lowbit(x)) ret += C[x];
                return ret;
        }
        int count(int x) {
                return rank(x) - rank(x-1);
        }
        int size() {
                return rank(n);
        }
}TurnL, TurnR;
int w[N], L[N], R[N], p[N];
int X[N], xc;
int c2[N], c7[N];
vector<pair<int,int> > Q[N];

void dfs(int u, int d=0) {
        for(int i=0;i<Q[u].size();++i) {
                int x = Q[u][i].first;
                x = lower_bound(X, X+xc, x) - X + 1;
                if(TurnL.count(x) || TurnR.count(x)) {
                        c2[Q[u][i].second] = -1;
                }
                else {
                        int ll = TurnL.rank(x);
                        int rr = TurnR.rank(x);
                        c7[ Q[u][i].second ] = rr;
                        c2[ Q[u][i].second ] = d + 2*(ll + rr);
                }
        }
        int t = lower_bound(X, X+xc, w[u]) - X + 1;
        if(L[u]) {
                TurnL.insert(t);
                dfs(L[u], d+1);
                TurnL.remove(t);
        }
        if(R[u]) {
                TurnR.insert(t);
                dfs(R[u], d+1);
                TurnR.remove(t);
        }
}

int main () {
        int T;
        scanf("%d", &T);
        while(T --) {
                int n, m;
                xc = 0;
                scanf("%d", &n);
                for(int i=1;i<=n;++i) {
                        scanf("%d", &w[i]);
                        L[i] = R[i] = p[i] = 0;
                        X[xc++] = w[i];
                }
                scanf("%d", &m);
                for(int i=1;i<=m;++i) {
                        int u, a, b;
                        scanf("%d%d%d", &u, &a, &b);
                        L[u] = a; R[u] = b;
                        p[a] = p[b] = u;
                }
                for(int i=1;i<=n;++i) Q[i].clear();
                int q;scanf("%d", &q);
                for(int i=0;i<q;++i) {
                        int v, x;
                        scanf("%d%d",&v,&x);
                        Q[v].push_back(make_pair(x, i));
                        X[xc++] = x;
                }
                sort(X, X+xc);
                xc = unique(X, X+xc) - X;
                TurnL.init(xc); TurnR.init(xc);
                int root = 1; while(p[root]) root = p[root];
                dfs(root);
                for(int i=0;i<q;++i) {
                        if(c2[i] == -1) printf("0\n");
                        else {
                                printf("%d %d\n", c7[i], c2[i]);
                        }
                }
        }
        return 0;
}
