/**
* POJ 2104
* 主席树
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 100010;
const int M = N * 20;
int root[N], tot;
int l[M], r[M], d[M];

void insert(int x, int &y, int f, int t, int v) {
    d[ y=++tot ] = d[x] + 1;
    if (f == t) return;
    int mid = f + t >> 1;
    if( v <= mid ) {
        r[y] = r[x];
        insert(l[x], l[y], f, mid, v);
    }
    else {
        l[y] = l[x];
        insert(r[x], r[y], mid+1, t, v);
    }
}
int query(int x, int y, int f, int t, int v) {
    if(f == t) return f;
    int mid = f + t >> 1;
    int s = d[l[y]] - d[l[x]];
    if(v <= s)
        return query(l[x], l[y], f, mid, v);
    return query(r[x], r[y], mid+1, t, v-s);
}

int a[N], sa[N], n;
int main () {
    int q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i) scanf("%d", &a[i]), sa[i] = a[i];
    sort(sa+1, sa+1+n);
    int m = unique(sa+1, sa+1+n)-sa-1;
    for(int i=1;i<=n;++i) {
        int s = lower_bound(sa+1,sa+1+m,a[i])-sa;
        insert(root[i-1], root[i], 1, m, s);
    }
    while(q--) {
        int i, j, k;
        scanf("%d%d%d",&i,&j,&k);
        printf("%d\n",sa[ query(root[i-1], root[j], 1, m, k) ]);
    }
    return 0;
}
