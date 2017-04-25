#include <bits/stdc++.h>
#define FOR(n) for(int i=0;i<n;i++)
#define JFOR(n) for(int j=0;j<n;j++)
#define KFOR(n) for(int k=0;k<n;k++)
#define ioopt ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
int n,m,nxt,L,R;
int tptr[500000];
struct Node{
    int l,r,ls,rs,q;
}STptr[1000000];
int query(int l,int r,int idx){
    if(l==STptr[idx].l&&STptr[idx].r==r)return STptr[idx].q;
    int mid=(STptr[idx].r+STptr[idx].l)/2;
    if(r<=mid)return query(l,r,STptr[idx].ls);
    if(l>=mid)return query(l,r,STptr[idx].rs);
    else return max(query(l,mid,STptr[idx].ls),query(mid,r,STptr[idx].rs));
}
void build(int l,int r,int idx){
    STptr[idx].l=l,STptr[idx].r=r;
    if(l==r-1)STptr[idx].q=tptr[l];
    else{
        STptr[idx].ls=++nxt;
        STptr[idx].rs=++nxt;
        build(l,(l+r)/2,STptr[idx].ls);
        build((l+r)/2,r,STptr[idx].rs);
        STptr[idx].q=max(STptr[STptr[idx].ls].q,STptr[STptr[idx].rs].q);
    }
}
int main(){ioopt
    while(cin>>n){
        nxt=0;
        FOR(n)cin>>tptr[i];
        cin>>m;
        build(0,n,0);
        FOR(m){
            cin>>L>>R;
            if(L>R)swap(L,R);
            cout<<query(L-1,R,0)<<'\n';
        }
    }
    return 0;
}
