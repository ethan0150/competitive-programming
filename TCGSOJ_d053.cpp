#include <iostream>
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

#define MAXN 31622
#define sqrt_MAXN 177
using namespace std;
typedef pair<int,int> pii;
int p[3401];
bitset<31622> isPrime;
int n,pn=0,cur,i;
bool f;
void build(){
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
    FOR(MAXN){
        if(isPrime[i]){
            p[pn]=i+1;
            pn++;
        }
    }
}
int main(){//ioopt
    build();
    while(cin>>n){
        i=0;
        f=1;
        if(n<2){
            cout<<n<<'\n';
            continue;
        }
        cout<<n<<" = ";
        while(n!=1){
            if(n%p[i]==0){
                n/=p[i];
                if(!f)cout<<" * ";
                else f=0;
                cout<<p[i];
            }
            else if(i==3400){
                cout<<" * "<<n;
                break;
            }
            else i++;
        }
        cout<<'\n';
    }
    return 0;
}
