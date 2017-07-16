#include <bits/stdc++.h>
#define FOR(n) for(int i=0;i<n;i++)
#define JFOR(n) for(int j=0;j<n;j++)
#define KFOR(n) for(int k=0;k<n;k++)
#define ioopt ios_base::sync_with_stdio(0);cin.tie(0);
#define X first
#define Y second
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
#define MAXN 10000
#define MAXC 50000
using namespace std;
typedef unsigned short us;
typedef pair<unsigned short,unsigned short> pss;
bool arr[MAXN][MAXN];
us a,b,c,ans;
pss pos[MAXC];
void flood(us x,us y){
    arr[x][y]=0;
    for(short i=x-2;i<=x+2;i++){
        if(i<0||i>9999)continue;
        for(short j=y-2;j<=y+2;j++){
            if((x==i&&y==j)||j<0||j>9999)continue;
            if(arr[i][j]){
                flood(i,j);
            }
        }
    }
    return;
}
int main(){ioopt
    while(cin>>a>>b>>c){
        ans=0;memset(arr,0,sizeof(bool)*100000000);
        FOR(c){
            cin>>pos[i].X>>pos[i].Y;
            pos[i].X--;pos[i].Y--;
            arr[pos[i].X][pos[i].Y]=1;
        }
        FOR(c){
            if(arr[pos[i].X][pos[i].Y]){
                flood(pos[i].X,pos[i].Y);
                ans++;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
