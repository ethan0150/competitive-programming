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
using namespace std;
typedef pair<int,int> pii;
typedef unsigned long long ull;
struct Node{
    int l,r,ls,rs;
    bool z,n;
}ST[200002];
struct ter{
    bool n,z;
}E[100001];
int n,k,nxt,in,I,v,l,r;
char c;
void mod(int i,int v,int idx){
    if(ST[idx].l==ST[idx].r-1){
        ST[idx].n=(v<0);
        ST[idx].z=(v==0);
        return;
    }
    int mid=(ST[idx].l+ST[idx].r)/2;
    if(i<mid)mod(i,v,ST[idx].ls);
    else mod(i,v,ST[idx].rs);
    ST[idx].n=ST[ST[idx].ls].n^ST[ST[idx].rs].n;
    ST[idx].z=ST[ST[idx].ls].z|ST[ST[idx].rs].z;
}
char query(int l,int r,int idx){
    if(ST[idx].l==l&&ST[idx].r==r){
        if(ST[idx].z)return '0';
        else if(ST[idx].n)return '-';
        else return '+';
    }
    int mid=(ST[idx].l+ST[idx].r)/2;
    if(r<=mid)return query(l,r,ST[idx].ls);
    if(l>=mid)return query(l,r,ST[idx].rs);
    char ql=query(l,mid,ST[idx].ls),qr=query(mid,r,ST[idx].rs);
    if(ql=='0'||qr=='0')return '0';
    else if(ql!=qr)return '-';
    else return '+';
}
void build(int l,int r,int idx){
    ST[idx].l=l;ST[idx].r=r;
    if(l==r-1){
        ST[idx].n=E[l].n;
        ST[idx].z=E[l].z;
    }
    else{
        ST[idx].ls=nxt++;
        ST[idx].rs=nxt++;
        int mid=(ST[idx].l+ST[idx].r)/2;
        build(l,mid,ST[idx].ls);
        build(mid,r,ST[idx].rs);
        ST[idx].n=ST[ST[idx].ls].n^ST[ST[idx].rs].n;
        ST[idx].z=ST[ST[idx].ls].z|ST[ST[idx].rs].z;
    }
}
int main(){ioopt
    while(cin>>n>>k){
        nxt=1;
        FOR(n){
            cin>>in;
            E[i].n=(in<0);
            E[i].z=(in==0);
        }
        build(0,n,0);
        FOR(k){
            cin>>c;
            if(c=='C'){
                cin>>I>>v;
                I--;
                mod(I,v,0);
            }
            else{
                cin>>l>>r;
                l--;
                cout<<query(l,r,0);
            }
        }
        cout<<endl;
    }
    return 0;
}

