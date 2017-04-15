#include <iostream>
#define FOR(n) for(int i=0;i<n;i++)
#define ioopt ios_base::sync_with_stdio(0);cin.tie(0);
//Don't use macros below if U R using ioopt!!
/*#define RI(n) scanf("%d",&n)
#define RUI(n) scanf("%u",&n)
#define RS(n) scanf("%s",&n)
#define RC(n) scanf("%c",&n)
#define PI(n) printf("%d",n)
#define PIln(n) printf("%d\n",n)
#define PIb(n) printf("%d ",n)
#define PS(n) printf("%s",n)
#define PSln(n) printf("%s\n",n)*/
using namespace std;
int main(){ioopt
    int n,maxm;
    while(cin>>n){
        maxm=0;
        int w[n];
        FOR(n){
            cin>>w[i];
            maxm+=w[i];
        }
        if(maxm%2){//maxm here==msum;
            cout<<"NO"<<'\n';
            continue;
        }
        maxm/=2;
        bool dp[maxm+1];
        dp[0]=1;
        FOR(maxm)dp[i+1]=0;
        FOR(n){
            for(int m=maxm;m>=0;m--){
                if(m>=w[i]){
                    if(dp[m-w[i]]||dp[m])dp[m]=1;
                }
            }
        }
        if(dp[maxm])cout<<"YES"<<'\n';
        else cout<<"NO"<<'\n';
    }
    return 0;
}
