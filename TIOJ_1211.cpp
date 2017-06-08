#include <bits/stdc++.h>
#define FOR(n) for(int i=0;i<n;i++)
#define JFOR(n) for(int j=0;j<n;j++)
#define KFOR(n) for(int k=0;k<n;k++)
#define ioopt ios_base::sync_with_stdio(0);cin.tie(0);
#define W first
#define N second    //N:neighbor,W:weight
#define MAXN 10000
#define MAXM 1000000
using namespace std;
int n,m,p[MAXN],ans,in1,in2;
bool notCon;
vector<int> adj[MAXN];
bitset<MAXN> vis;
struct Edge{
    int v,u,w;
}E[MAXM];
void dfs(int x){
    for(int u:adj[x]){
        if(!vis[u]){
            vis[u]=1;
            dfs(u);
        }
    }
}

void init(){
    notCon=0;
    FOR(n)adj[i].clear();
    vis.set();
    vis.flip();
    memset(E,0,sizeof(Edge)*MAXM);
    ans=0;
    FOR(n){
        p[i]=i;
    }
}

int find_root(int x){return p[x]==x?x:p[x]=find_root(p[x]);}

bool cmp(const Edge a,const Edge b){return a.w<b.w;}

int main(){//ioopt
    while(1){
        cin>>n>>m;
        init();
        if(n==0&&m==0)break;
        FOR(m){
            cin>>in1>>in2>>E[i].w;
            E[i].u=in1-1;
            E[i].v=in2-1;
            adj[E[i].u].push_back(E[i].v);
            adj[E[i].v].push_back(E[i].u);
        }
        dfs(0);
        FOR(n){
            if(!vis[i]){
                notCon=1;
                break;
            }
        }
        if(notCon){
            cout<<-1<<'\n';
            continue;
        }
        sort(E,E+m,cmp);
        FOR(m){
            int x=find_root(E[i].u),y=find_root(E[i].v);
            if(x!=y){
                ans+=E[i].w;
                p[x]=y;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
