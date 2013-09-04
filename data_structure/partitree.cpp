#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
const int MAX_N = 100010;
const int MAX_M = 50010;

int n, m;
int nd[18][MAX_N], lft[18][MAX_N];
int a[MAX_N];
void build(int l, int r, int d) {
    if(l == r) return ;
    int mid = (l + r) >> 1;
    int s = l, t = mid + 1, cnt = t - s;
    for(int i=l;i<=r;++i) if(nd[d][i] < a[mid]) cnt --;
    for(int i=l;i<=r;++i) {
        if(nd[d][i] < a[mid]) nd[d+1][s ++] = nd[d][i];
        else if(nd[d][i] > a[mid]) nd[d+1][t ++] = nd[d][i];
        else {
            if(cnt > 0) nd[d+1][s ++] = nd[d][i];
            else        nd[d+1][t ++] = nd[d][i];
            cnt --;
        }
        lft[d][i] = s - 1;
    }
    build(l, mid, d+1);
    build(mid+1, r, d+1);
}
int get(int L, int R, int d, int l, int r, int k) {
    if( L == R ) return a[L];
    int mid = (L + R) >> 1;
    int s, ss, t, tt;
    if(l == L) s = 0;
    else    s = lft[d][l-1] - L + 1;
    ss = lft[d][r] - L + 1;
    t = l-1-L+1 - s;
    tt = r-L+1 - ss;
    int len = ss - s;
    if(len >= k) return get(L, mid, d+1, L+s, L+ss-1, k);
    else    return get(mid+1,R,d+1, mid+t+1, mid+tt,k-len);
}

int main () {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]), nd[0][i] = a[i];
    sort(a+1, a+1+n);
    build(1, n, 0);
    while(m --) {
        int l, r, k;
        scanf("%d%d%d",&l,&r,&k);
        printf("%d\n", get(1,n,0,l,r,k));
    }
    return 0;
}
