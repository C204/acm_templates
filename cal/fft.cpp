/**
*http://codeforces.com/contest/286/problem/E
*FFT
*/
#include <algorithm>
#include <iostream>
#include <complex>
#include <cmath>
using namespace std;
const int N = 1 << 21;
const double PI = acos(-1.0);
struct FFT {
    #define re real()
    #define im imag()
    #define cp complex<double>
    cp s1[N], s2[N];
    void brc(cp y[], int l) {
        for(int i=1,j=l/2;i<l-1;i++) {
            if(i < j) swap(y[i], y[j]);
            int k = l/2;
            while (j >= k) j -= k, k >>= 1;
            if(j < k) j+=k;
        }
    }
    void fft(cp y[], int l, double on) {
        cp u, t;
        brc(y, l);
        for(int h=2;h<=l;h<<=1) {
            cp wn(cos(on*2*PI/h), sin(on*2*PI/h));
            for(int j=0;j<l;j+=h) {
                cp w(1, 0);
                for(int k=j;k<j+h/2;++k) {
                    u = y[k]; t = w*y[k+h/2];
                    y[k] = u + t;
                    y[k + h/2] = u - t;
                    w = w * wn;
                }
            }
        }
        if(on == -1) for(int i=0;i<l;++i) y[i] /= l;
    }
    void multiply (int a[], int b[], int ret[], int l) {
        for(int i=0;i<l;++i)
            s1[i] = a[i], s2[i] = b[i];
            fft(s1, l, 1); fft(s2, l, 1);
            for(int i=0;i<l;++i)
                s1[i] *= s2[i];
            fft(s1, l, -1);
            for(int i=0;i<l;++i)
                ret[i] = s1[i].re + 0.5;
    }
}fft;
int a[N], ret[N];
int main () {
    int n, m; cin >> n >> m;
    int l = 1;while(l < 2*m) l<<=1; a[0] = 1;
    for(int i=0,t;i<n;++i)cin >> t, a[t] = 1;
    fft.multiply(a, a, ret, l);
    for(int i=1;i<=m;++i) if(!a[i]&&ret[i]) { cout << "NO" << endl;return 0;}
    cout << "YES" << endl;
    int sz = 0;
    for(int i=1;i<=m;++i) if(ret[i] == 2) sz ++;
    cout << sz << endl;
    for(int i=1;i<=m;++i) if(ret[i] == 2) cout << i << " " ;
    cout << endl;
    return 0;
}

