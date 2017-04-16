#include <bits/stdc++.h>
#define FOR(n) for(int i=0;i<n;i++)
#define JFOR(n) for(int j=0;j<n;j++)
#define KFOR(n) for(int k=0;k<n;k++)
#define ioopt ios_base::sync_with_stdio(0);cin.tie(0);
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
using namespace std;
typedef unsigned long long ull;
ull product(ull i,ull j){
    ull ret=1;
    for(;i<=j;i++)ret*=i;
    return ret;
}
ull C(ull n,ull k){
    if(k>n-k)return product(k+1,n)/product(1,n-k);
    else return product(n-k+1,n)/product(1,n);
}
ull P(ull n,ull k){return product(n-k+1,n);}
ull H(ull n,ull k){return C(n+k-1,k);}
int main(){ioopt
    return 0;
}
