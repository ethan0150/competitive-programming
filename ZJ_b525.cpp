#include <bits/stdc++.h>
#define FOR(n) for(int i=0;i<n;i++)
#define JFOR(n) for(int j=0;j<n;j++)
#define KFOR(n) for(int k=0;k<n;k++)
#define ioopt ios_base::sync_with_stdio(0);cin.tie(0);
#define x (unsigned long long)100000007
using namespace std;
typedef unsigned long long ull;
ull m,f,k,m2;
ull A[25][2][2]={{{0,1},{1,1}},{{0}}};
int main(){ioopt
    FOR(24){
        A[i+1][0][0]=(((A[i][0][0]%x)*(A[i][0][0]%x))%x+((A[i][0][1]%x)*(A[i][1][0]%x))%x)%x;
        A[i+1][1][0]=(((A[i][0][0]%x)*(A[i][1][0]%x))%x+((A[i][1][1]%x)*(A[i][1][0]%x))%x)%x;
        A[i+1][0][1]=(((A[i][0][0]%x)*(A[i][0][1]%x))%x+((A[i][0][1]%x)*(A[i][1][1]%x))%x)%x;
        A[i+1][1][1]=(((A[i][1][0]%x)*(A[i][0][1]%x))%x+((A[i][1][1]%x)*(A[i][1][1]%x))%x)%x;
    }
    while(cin>>m>>f>>k){
        FOR(25){
            if(k&1){
                m2=m;
                m=(((m%x)*A[i][0][0])%x+((f%x)*A[i][0][1])%x)%x;
                f=(((m2%x)*A[i][1][0])%x+((f%x)*A[i][1][1])%x)%x;
            }
            k>>=1;
        }
        ull ans=(m%x+f%x)%x;
        cout<<ans<<'\n';
    }
    return 0;
}
