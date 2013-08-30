/**
*POJ 1811
*miller_rabin && pollard-rho
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

typedef long long LL;

LL gcd(LL a, LL b) {return b==0?a:gcd(b,a%b);}
LL mul_mod(LL x, LL y, LL n) {
    LL ret = 0;
    while(y) {
        if(y&1) ret = (ret + x) % n;
        y>>=1; x=(x+x)%n;
    }
    return ret;
}
LL pow_mod(LL x, LL y, LL n) {
    LL ret = 1;
    while(y) {
        if(y&1) ret = mul_mod(ret, x, n);
        y>>=1; x = mul_mod(x, x, n);
    }
    return ret;
}
bool witness(LL a, LL n) {
    LL t = n-1, x, y;
    while(t % 2 == 0) t>>=1;
    x = y = pow_mod(a, t, n);
    for(t<<=1;t<n;t<<=1) {
        x=mul_mod(x,x,n);
        if(x==1&&y!=1&&y!=n-1) return 1;
        y = x;
    }
    return x!=1;
}
bool miller_rabin(LL n, int s=10) {
    if(n==2||n==3||n==5) return 1;
    if(n%2==0||n%3==0||n%5==0) return 0;
    while(s --) if( witness(rand()%(n-1)+1, n) ) return 0;
    return 1;
}
LL f(LL x, LL c, LL n) { return (mul_mod(x, x, n) + c) % n; }
LL pollard(LL n, LL c) {
    LL x = rand()%(n-1)+1, y = x;
    LL cnt = 1, next = 2;
    while(1) {
        x = f(x, c, n);
        LL d = gcd(y-x+n, n);
        if(d!=1 && d!=n) return d;
        if(x==y) return n;
        if(++cnt==next) y = x, next<<=1;
    }
}
vector<LL> fac;
void findfac(LL n) {
    if(miller_rabin(n)) { fac.push_back(n); return; }
    LL p = n;
    if(n%2==0)p=2;
    else if(n%3==0)p=3;
    else if(n%5==0)p=5;
    while(p==n) p=pollard(p, rand()%(n-1)+1);
    findfac(p); findfac(n/p);
}
int main () {
    int T; cin>>T;
    while(T --) {
        LL n; cin>>n;
        fac.clear();
        findfac(n);
        sort(fac.begin(), fac.end());
        if(fac[0] == n) cout<<"Prime"<<endl;
        else cout<<fac[0]<<endl;
    }
    return 0;
}
