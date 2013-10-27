/**
* hdu 4746
* gcd cnt
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 500050;

int sum[20][N];
bool isp[N];
int pr[N], miu[N], cn[N];
void init() {
    miu[1] = 1; cn[1] = 0;
    memset(isp, 1, sizeof isp);
    for(int i=2;i<N;++i) {
        if(isp[i]){
            pr[i] = i; miu[i] = -1;
            for(int j=i+i;j<N;j+=i) isp[j] = 0, pr[j] = i;
        }
        else {
            if( (i/pr[i])%pr[i]==0 ) miu[i] = 0;
            else miu[i] = -miu[i/pr[i]];
        }
        cn[i] = cn[i/pr[i]] + 1;
    }
    for(int i=1;i<N;++i) {
        int l = cn[i];
        for(int j=i;j<N;j+=i) sum[l][j] += miu[j/i];
    }
    for(int i=0;i<20;++i) {
        for(int j=1;j<N;++j) sum[i][j] += sum[i][j-1];
        if(i)for(int j=1;j<N;++j) sum[i][j] += sum[i-1][j];
    }
}
int main () {
    init();
    int q;
    scanf("%d", &q);
    while(q--) {
        int n, m, p;scanf("%d%d%d",&n,&m,&p);
        if( p>18 || (1<<p)>min(n,m) ) {
            cout << (long long)n * m << endl;
            continue;
        }
        int *sm = sum[p]; long long ans = 0;
        for(int i=1,last;i<=n&&i<=m;i=last+1) {
            last = min( n/(n/i), m/(m/i) );
            ans += (long long)(n/i)*(m/i)*(sm[last]-sm[i-1]);
        }
        cout << ans << endl;
    }
    return 0;
}
