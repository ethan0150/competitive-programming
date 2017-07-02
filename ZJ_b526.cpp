#include <bits/stdc++.h>
#define FOR(n) for(int i=0;i<n;i++)
#define JFOR(n) for(int j=0;j<n;j++)
#define KFOR(n) for(int k=0;k<n;k++)
#define ioopt ios_base::sync_with_stdio(0);cin.tie(0);
#define t first
#define a second    //1:start 0:end
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
#define MAXM 1000000
using namespace std;
typedef pair<int,bool> pib;
int m,n,input,ans,last,cnt;
pib event[2*MAXM];
int main(){ioopt
    while(cin>>n){
        ans=0;last=1;cnt=0;
        FOR(MAXM)event[i]=make_pair(INT_MAX,0);
        cin>>m;
        FOR(m){
            cin>>event[2*i].t;
            event[2*i].a=1;
            cin>>event[2*i+1].t;
            event[2*i+1].t++;
        }
        sort(event,event+2*m);
        FOR(2*m){
            if(event[i].t!=last){
                if(cnt%2==0)ans+=(event[i].t-last);
                last=event[i].t;
            }
            if(event[i].a)cnt++;
            else cnt--;
        }
        ans+=n-event[2*m-1].t+1;
        cout<<ans<<'\n';
    }
    cout.flush();
    return 0;
}
