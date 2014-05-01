#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
LL exgcd(LL a, LL b, LL &x, LL &y) {
    if( !b ) {
        x = 1; y = 0;
        return a;
    }
    LL ret = exgcd(b, a%b, y, x);
    y -= (a / b) * x;
    return ret;
}
bool CRT(LL b1, LL c1, LL b2, LL c2, LL &b, LL &c) {
    LL x1, x2;
    LL g = exgcd(c1, c2, x1, x2);
    if( (b1 - b2) % g )  return false;
    c = c1 / g * c2;
    b = (c1/g*x1*b2 + c2/g*x2*b1) %c;
    return true;
}
int main () {
    int n;
    while( cin >> n ) {
        LL b, c, bb, cc;
        cin >> c >> b;
        n--;
        while(n--) {
            cin >> cc >> bb;
            CRT(b, c, bb, cc, b, c);
        }
        b = b%c; if(b<=0) b+=c;
        cout << b << endl;
    }
    return 0;
}
