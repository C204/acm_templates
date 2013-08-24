/*
*POJ 1743
*HASH
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

typedef unsigned long long LL;
const int N = 21313;
const int P = 99991;
int a[N], n;

struct Map {
    int H[N], E[N], cnt;
    LL v[N]; int ret[N];
    void clear() {
        memset(H, -1, sizeof H);
        cnt = 0;
    }
    int &operator[](LL t) {
        int p = t % N;
        for(int i=H[p];i!=-1;i=E[i]) {
            if(v[i] == t) return ret[i];
        }
        v[cnt] = t; ret[cnt] = -1; E[cnt] = H[p]; H[p] = cnt;
        return ret[cnt++];
    }
    bool count(LL t) {
        int p = t % N;
        for(int i=H[p];i!=-1;i=E[i]) {
            if(v[i] == t) return true;
        }
        return false;
    }
}M;

bool check(int m) {
    M.clear();
    LL t = 1, p = 0;
    for(int i=0;i<m;++i) {
        t = t * P;
        p = p * P + a[i];
    }
    M[p] = 0;
    for(int i=m;i<n;++i) {
        p = p * P + a[i] - t * a[i-m];
        int &x = M[p];
        if(x >= 0) {
            if(i-m >= m+x) return true;
        }
        else x = i-m+1;
    }
    return false;
}

int main () {
    while(scanf("%d",&n)!=EOF) {
        if(!n) break;
        for(int i=0;i<n;++i) {
            scanf("%d", &a[i]);
            if(i) a[i-1] = a[i]-a[i-1]+90;
        }n--;
        int low = 1, high = n;
        while (low < high) {
            int mid = low+high+1 >> 1;
            if(check(mid)) low = mid;
            else high = mid-1;
        }
        if(low<4) puts("0");
        else  printf("%d\n", low+1);
    }
    return 0;
}
