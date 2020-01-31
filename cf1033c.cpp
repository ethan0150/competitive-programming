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
int n,a[MAXN]={0},r;
bitset<MAXN> t,dp;
vector<int> G[MAXN];
void dfs(int v){
	t[v]=1;
	for(int u:G[v]){
		if(t[u]==0)dfs(u);
		dp[v]=dp[u]&dp[v];
	}
	dp[v]=!dp[v];
	return;
}
void genDAG(){
	FOR(n){
		for(int j=i;j<n;j+=a[i])if(a[j]>a[i])G[i].push_back(j);
		for(int j=i;j>=0;j-=a[i])if(a[j]>a[i])G[i].push_back(j);
		if(G[i].size()==0){
			t[i]=1;
			dp[i]=0;
		}
	}
	return;
}
int main(){ioopt
	t.reset();
	dp.set();
	cin>>n;
	FOR(n){
		cin>>a[i];
		if(a[i]==1)r=i;
	}
	genDAG();
	if(t[r]==0)dfs(r);
	FOR(n){
		if(dp[i])cout<<'A';
		else cout<<'B';
	}
	cout<<'\n';
    return 0;
}
