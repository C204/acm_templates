/**
* ZOJ 3254
* babystep加循环节
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;
typedef unsigned long long LL;
map<LL, LL> hash;
LL gcd(LL a, LL b) { return b==0?a:gcd(b, a%b);}
int babyStep(LL a, LL b, LL c) {
    if( b == 1 || (b==0 && c==1) )  return 0;
    if( b >= c) return -1;
    LL t = 1, g, ext = 1;
    for(int i=0;i<64;++i) {
        if(b == t) return i;
        t = t*a % c;
    }
    int num = 0;
    while( (g = gcd(a, c)) != 1 ) {
        if( b % g )  return -1;
        c /= g; b /= g;
        ext = ext * a / g % c;
        num ++;
    }
    hash.clear();
    LL m = sqrt(c * 1.0);
    while(m*m < c) m++;
    t = 1;
    for(int i=0;i<m;++i) hash[t*b%c] = i, t = t*a%c;
    for(LL i=1;i<=m+1;++i) {
        ext = ext*t%c;
        if( hash.count(ext) )
            return i*m - hash[ ext ] + num;
    }
    return -1;
}

LL phi(LL p) {
    LL ans = p;
    for(LL i=2;i*i<=p;++i) if(p % i == 0) {
        ans -= ans / i;
        while(p%i == 0) p/=i;
    }
    if(p != 1) ans -= ans / p;
    return ans;
}

LL pow(LL a, LL b, LL c) {
    LL ans = 1;
    while(b) {
        if(b & 1) ans = ans * a %c;
        a = a*a%c; b >>= 1;
    }
    return ans;
}

LL getCir(LL a, LL c, LL p, LL an, LL t) {
    LL ret = p;
    for(LL i=2;i*i<=p;++i) if(p%i == 0) {
        while(p%i==0) p /= i;
        while( ret%i==0 && pow(a, an+ret/i, c) == t )
            ret /= i;
    }
    if(p != 1) {
        if( pow( a, an + ret/p , c ) == t )
            ret /= p;
    }
    return ret;
}

int main () {
    LL a, b, c, M;
    while(cin >> a >> c >> b >> M) {
        a %= c; b %= c;
        LL p = phi(c), t = 1;
        LL f = babyStep(a, b, c);
        if( f == -1 || f > M ) {
            cout << 0 << endl;
            continue;
        }
        if( pow(a, p+f, c) != b ) {
            cout << 1 << endl;
            continue;
        }
        LL cir = getCir(a, c, p, f, b);
        LL ans = 1ULL + (M-f) / cir;
        cout << ans << endl;
    }
    return 0;
}
