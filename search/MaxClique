/**
*HDU 1530
*搜索 最大团
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;

LL a[55];
int n, ans;
void dfs(int d, LL cur, int c) {
    if(ans < c) ans = c;
    if(c+n-d<=ans) return;
    if( (a[d]&cur) == cur )
        dfs(d+1, cur|(1LL<<d), c+1);
    dfs(d+1, cur, c);
}
int main () {
    while(scanf("%d",&n)!=EOF) {
        if(n == 0) break;
        for(int i=0;i<n;++i) {
            a[i] = 0;
            for(int j=0,t;j<n;++j) {
                scanf("%d", &t);
                if(t) a[i] |= (1LL<<j);
            }
        }
        ans = 0; dfs(0, 0, 0);
        printf("%d\n", ans);
    }
    return 0;
}
/**
5
0 1 1 1 1
1 0 1 1 1
1 1 0 1 1
1 1 1 0 1
1 1 1 1 0
*/
