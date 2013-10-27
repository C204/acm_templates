/**
* bzoj 1901
* 主席树
**/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int N = 10010;
const int M = N * 900;
const int C = 1000000000;
int n, tot, a[N], root[N], U[N], V[N];
int l[M], r[M], d[M];
void insert(int &x, int f, int t, int v, int s) {
    if(!x) x = ++ tot;
    d[x] += s;
    if(f == t) return;
    int mid = f+t>>1;
    if(v <= mid) insert(l[x], f, mid, v, s);
    else insert(r[x], mid+1, t, v, s);
}
void update(int x, int v, int s) {
    for(;x<=n;x+=x&-x)
        insert(root[x],0,C,v,s);
}
int getsum(int x) {
    int ret = 0;
    for(;x;x-=x&-x) ret += d[l[U[x]]];
    return ret;
}
void init(int x) {
    for(;x;x-=x&-x) {
        U[x] = root[x];
        V[x] = 0;
    }
}
void turnl(int x, int cnt) {
    for(;x;x-=x&-x) if(V[x]!=cnt){
        U[x] = l[U[x]];
        V[x] = cnt;
    }
}
void turnr(int x, int cnt) {
    for(;x;x-=x&-x) if(V[x]!=cnt){
        U[x] = r[U[x]];
        V[x] = cnt;
    }
}
int main () {
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) {
        scanf("%d", &a[i]);
        update(i, a[i], 1);
    }
    while(m --) {
        char op[3];int i, j, k;
        scanf("%s%d%d",op,&i,&j);
        if(op[0] == 'C') {
            update(i, a[i], -1);
            update(i, a[i]=j, 1);
        }
        else {
            scanf("%d", &k);
            init(j); init(i-1);
            int f = 0, t = C, cnt = 0;
            while(f < t) {
                ++ cnt;
                int mid = f+t>>1, cur = getsum(j)-getsum(i-1);
                if(k <= cur) {
                    t = mid;
                    turnl(j, cnt); turnl(i-1, cnt);
                }
                else {
                    f = mid+1;
                    k -= cur;
                    turnr(j, cnt); turnr(i-1, cnt);
                }
            }
            printf("%d\n", f);
        }
    }
    return 0;
}
