#include <iostream>
#include <limits.h>
#define w first
#define v second
#define FOR(n) for(int i=0;i<n;i++)
using namespace std;
typedef pair<int,int> pii;
int main()
{
    int maxn,maxw,ans=0;
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>maxn>>maxw;
    pii item[maxn];
    int dp[maxw+1];
    dp[0]=0;
    FOR(maxw)dp[i+1]=INT_MIN;
    FOR(maxn)cin>>item[i].w>>item[i].v;
    FOR(maxn){
        for(int m=maxw;m>=0;m--){
            if(m>=item[i].w)dp[m]=max(dp[m],dp[m-item[i].w]+item[i].v);
            if(i==maxn-1&&dp[m]>ans)ans=dp[m];
        }
    }
    cout<<ans<<'\n';
    return 0;
}
