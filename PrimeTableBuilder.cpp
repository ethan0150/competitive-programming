#include <iostream>
//#include <climits>
#include <bitset>
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

#define MAXN 32000
#define sqrt_MAXN 178
using namespace std;
typedef pair<int,int> pii;
typedef unsigned long ul;
int cur,n=0;
bitset<MAXN> isPrime;
int main(){ioopt
    isPrime.set();
    isPrime[0]=0;
    FOR(sqrt_MAXN){
        if(isPrime[i]){
            cur=i+1;
            for(int j=i+cur;j<MAXN;j+=cur){
                isPrime[j]=0;
            }
        }
    }
    PC('{');
    FOR(MAXN){
        if(isPrime[i]){
            if(i!=1)PC(',');
            PI(i+1);
            n++;
        }
    }
    PC('}');
    PI(n);
    return 0;
}
