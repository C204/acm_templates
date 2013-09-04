#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const double eps = 1e-6;
const int N = 110;
double a[N][N];
int n;
int Guass() {
    int h = 0, rank = n;
    for(int i=0;i<n&&h<n;++i,++h) {
        int maxone = i;
        for(int j=i+1;j<n;++j)
            if(fabs(a[maxone][h]) < fabs(a[j][h])) maxone = j;
        if(i != maxone) for(int j=h;j<n;++j)
            swap(a[i][j], a[maxone][j]);
        if( fabs(a[i][h]) < eps ) {
            rank --; --i;
            continue;
        }
        for(int j=i+1;j<n;++j) {
            double t = a[j][h] / a[i][h];
            for(int k=h;k<n;++k)
                a[j][k] -= a[i][k] * t;
        }
    }
    return rank;
}
int main () {
    cin >> n;
    for(int i=0;i<n;++i)
    for(int j=0;j<n;++j) {
        cin >> a[i][j];
        if( !a[i][j] ) continue;
        if(i < j) a[i][j] = rand();
        else  a[i][j] = -rand();
    }
    cout << Guass()/2 << endl;
    return 0;
}
