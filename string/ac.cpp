/**
*HDU 2222
*AC自动机
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int N = 10010;
struct node {
    int next[26], end, fail;
    int &operator[](int t) {return next[t];}
    void clear() { memset(next, 0, sizeof next), end=0, fail=0; }
}no[N*50];
int no_cnt;
void clear() { no[0].clear(); no_cnt = 1; }
int maken() { no[no_cnt].clear(); return no_cnt++; }
void insert(char *s, int rt=0) {
    if(!*s) { no[rt].end++; return; }
    int c = *s-'a';
    if(!no[rt][c]) no[rt][c] = maken();
    insert(s+1, no[rt][c]);
}
int Q[N];
void bfs() {
    int f=0,r=0;
    for(int i=0;i<26;++i) if(no[0][i]) Q[r++]=no[0][i];
    while(f!=r) {
        int x = Q[f++];
        for(int i=0;i<26;++i) if( no[x][i] ) {
            int y = no[x][i], p = no[x].fail;
            while(p && !no[p][i]) p = no[p].fail;
            no[y].fail=no[p][i];
            Q[r++]=y;
        }
    }
}
int work(char *s) {
    int p = 0, ans = 0;
    for(;*s;s++) {
        int c = *s - 'a';
        while(p && !no[p][c]) p = no[p].fail; p = no[p][c];
        for(int i=p;i&&no[i].end!=-1;i=no[i].fail) {
            if(no[i].end>0)ans+=no[i].end;
            no[i].end = -1;
        }
    }
    return ans;
}
char s[N*100];
int main () {
    int T; scanf("%d", &T);
    while(T--) {
        clear();
        int m; scanf("%d", &m);
        while(m--) { scanf("%s", s); insert(s);}
        bfs();
        scanf("%s", s);
        printf("%d\n", work(s));
    }
    return 0;
}
