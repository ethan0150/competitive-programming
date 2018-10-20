#include <bits/stdc++.h>
#define FOR(n) for(int i=0;i<n;i++)
#define JFOR(n) for(int j=0;j<n;j++)
#define KFOR(n) for(int k=0;k<n;k++)
#define ioopt ios_base::sync_with_stdio(0);cin.tie(0);
#define F e.first
#define S e.second
#define f ans.first
#define s ans.second
//Don't use macros below if U R using ioopt!!
#define RI(n) scanf("%d",&n)
#define RUI(n) scanf("%u",&n)
#define RS(n) scanf("%s",&n)
#define RC(n) scanf("%c",&n)
#define PI(n) printf("%d",n)
#define PIln(n) printf("%d\n",n)
#define PIb(n) printf("%d ",n)
#define PS(n) printf("%s",n)
#define PSln(n) printf("%s\n",n)
#define PC(n) printf("%c",n)
using namespace std;
typedef pair<int,int> pii;
typedef unsigned long long ull;
bool t[40][40],m[40][40];
int N,M;
char in;
pii ans;
void ff(pii e){
    t[F][S]=1;
    short ob=0;
    if(F-1>=0){
        if(m[F-1][S]){
            if(!t[F-1][S])ff(make_pair(F-1,S));
        }
        else ob++;
    }
    if(F+1<=N-1){
        if(m[F+1][S]){
            if(!t[F+1][S])ff(make_pair(F+1,S));
        }
        else ob++;
    }
    if(S-1>=0){
        if(m[F][S-1]){
            if(!t[F][S-1])ff(make_pair(F,S-1));
        }
        else ob++;
    }
    if(S+1<=M-1){
        if(m[F][S+1]){
            if(!t[F][S+1])ff(make_pair(F,S+1));
        }
        else ob++;
    }
    if(ob==3)ans=e;
    return;
}
pii ent(){
    FOR(M-2){
        if(m[0][i+1])return make_pair(0,i+1);
        if(m[N-1][i+1])return make_pair(N-1,i+1);
    }
    FOR(N-2){
        if(m[i+1][0])return make_pair(i+1,0);
        if(m[i+1][M-1])return make_pair(i+1,M-1);
    }
}
int main(){//ioopt
    while(cin>>N>>M){
        FOR(N){
            JFOR(M){
                cin>>in;
                if(in=='#')m[i][j]=0;
                else m[i][j]=1;
                t[i][j]=0;
            }
        }
        ff(ent());
        cout<<ans.first+1<<' '<<ans.second+1<<'\n';
    }
    return 0;
}

