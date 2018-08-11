#include <bits/stdc++.h>
#define FOR(n) for(int i=0;i<n;i++)
#define JFOR(n) for(int j=0;j<n;j++)
#define KFOR(n) for(int k=0;k<n;k++)
#define ioopt ios_base::sync_with_stdio(0);cin.tie(0);
#define F first
#define S second
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

#define MAXN 100000
using namespace std;
typedef pair<int,int> pii;
typedef unsigned long long ull;
bitset<MAXN> isp;
int n;
void build(){
    isp.set();
    isp[0]=0,isp[1]=0;
    FOR(318){
        if(isp[i]){
            for(int j=i*2;j<MAXN;j+=i)isp[j]=0;
        }
    }
}
int main(){//ioopt
    build();
    while(cin>>n){
        if(n==0)break;
        int ans=0;
        FOR(n/2+1){
            if(isp[i]&&isp[n-i])ans++;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
