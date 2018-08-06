#include<bits/stdc++.h>
using namespace std;
using ll = long long;
//BEGIN CUT HERE
// mod lib {{{
#define MAX_P 200005
ll fact[MAX_P]; // fact[n]: n!
ll inv[MAX_P];  // inv[n]: n^(-1)
ll finv[MAX_P]; // finv[n]: (n!)^(-1)

void init(ll mod){  // 階乗関連テーブルの初期化 O(n)
  fact[0]=1;
  for(ll i=1;i<MAX_P;i++)
    fact[i]=(fact[i-1]*i)%mod;

  inv[1]=1;
  for(ll i=2;i<MAX_P;i++)
    inv[i]=inv[mod%i]*(mod-mod/i)%mod;

  finv[0]=1;  //　高速(10倍程度)な逆元階乗テーブルの作成。
  for(ll i=1;i<MAX_P;i++)
    finv[i]=finv[i-1]*inv[i]%mod;
}

ll extgcd(ll a,ll b,ll& x,ll& y){ //O(log(max(a,b)))
  ll d=a;
  if(b!=0){
    d=extgcd(b,a%b,y,x);
    y-=(a/b)*x;
  }else{
    x=1;y=0;
  }
  return d;
}
ll mod_inverse(ll a,ll mod){  // ユークリッドの拡張互除法による逆元
  ll x,y;
  extgcd(a,mod,x,y);
  return (mod+x%mod)%mod;
}

ll mod_pow(ll x,ll n,ll mod){ // 二分累乗法による階乗
  ll res=1;
  while(n){
    if(n&1) (res*=x)%=mod;
    (x*=x)%=mod;
    n>>=1;
  }
  return res;
}

ll mod_inverse2(ll a,ll mod){  // フェルマーの小定理による逆元
  return mod_pow(a,mod-2,mod);
}


ll mod_fact(ll n,ll mod,ll& e){ // n!=a*p^eとしたときのa mod pを返す。O(p)
  e=0;
  if(n==0) return 1;
  ll res=mod_fact(n/mod,mod,e);
  e+=n/mod;
  if(n/mod%2!=0)return res*(mod-fact[n%mod]) %mod;
  return res*fact[n%mod]%mod;
}

ll mod_comb(ll n,ll k,ll mod){
  if(n==k||k==0) return 1;
  ll e1,e2,e3;
  ll a1=mod_fact(n,mod,e1),a2=mod_fact(k,mod,e2),a3=mod_fact(n-k,mod,e3);
  if(e1>e2+e3) return 0;
  return a1*mod_inverse(a2*a3%mod,mod)%mod;
}

ll mod_comb2(ll n,ll k,ll mod){
  ll res=1;
  for(ll i=0;i<k;i++){
    res*=(n-i)%mod;
    res%=mod;
    res*=mod_inverse(i+1,mod);
    res%=mod;
  }
  return res;
}

//only for prime mod
ll mod_comb_pm(ll n,ll k,ll mod){  // テーブルがあればO(1)
  if(k<0||k>n) return 0;
  return fact[n]*finv[k]%mod*finv[n-k]%mod;
}

ll montmort(ll n,ll mod){
  ll res=0,inv=1;
  for(ll k=2;k<=n;k++){
    (inv*=mod_inverse(k,mod))%=mod;
    if(k%2) (res+=mod-inv)%=mod;
    else (res+=inv)%=mod;
  }
  for(ll i=1;i<=n;i++)
    (res*=i)%=mod;
  return res;
}

// calculate P(t) from given points in [0,N]
ll LagrangePolynomial(vector<ll> &y,ll t,const ll mod){
  init(mod);
  ll n=y.size()-1;
  ll num=1;
  for(ll i=0;i<=n;i++)
    num=num*((t-i)%mod)%mod;
  ll res=0;
  for(ll i=0;i<=n;i++){
    ll tmp=(y[i]*num%mod)*mod_inverse((t-i)%mod,mod)%mod;
    tmp=tmp*finv[i]%mod;
    tmp=tmp*finv[n-i]%mod;
    if((n-i)&1) tmp=mod-tmp;
    res=(res+tmp)%mod;
  }
  return res;
}
// }}}
//END CUT HERE

#define MOD 1000000007
//mod_pow
signed AOJ_NTL1B(){
  ll n,m;
  cin>>m>>n;
  cout<<mod_pow(m,n,MOD)<<endl;
  return 0;
}
/*
  verified on 2017/12/31
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B&lang=jp
*/

//extgcd
signed AOJ_NTL1E(){
  ll a,b;
  cin>>a>>b;
  ll x,y;
  extgcd(a,b,x,y);
  cout<<x<<" "<<y<<endl;
  return 0;
}
/*
  verified on 2017/12/31
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E&lang=jp
*/

//montmort
signed ARC009_C(){
  ll n,k;
  cin>>n>>k;
  const ll MMOD=1777777777;
  ll a=montmort(k,MMOD);
  a=a*mod_comb2(n,k,MMOD)%MMOD;
  cout<<a<<endl;
  return 0;
}
/*
  verified on 2017/12/31
  https://arc009.contest.atcoder.jp/tasks/arc009_3
*/


signed yuki_665(){
  ll n,k;
  cin>>n>>k;
  vector<ll> y(k+2,0);
  for(ll i=1;i<=k+1;i++) y[i]=(y[i-1]+mod_pow(i,k,MOD))%MOD;
  if(n<=k+1) cout<<y[n]<<endl;
  else cout<<LagrangePolynomial(y,n,MOD)<<endl;
  return 0;
}
/*
  verified on 2018/03/10
  https://yukicoder.me/problems/no/665
*/

signed ARC033_D(){
  ll n;
  cin>>n;
  vector<ll> y(n+1);
  for(ll i=0;i<=n;i++) cin>>y[i];
  ll t;
  cin>>t;
  if(t<=n) cout<<y[t]<<endl;
  else cout<<LagrangePolynomial(y,t,MOD)<<endl;
  return 0;
}
/*
  verified on 2018/03/10
  https://beta.atcoder.jp/contests/arc033/tasks/arc033_4
*/



signed main(){
  //AOJ_NTL1B();
  //AOJ_NTL1E();
  //ARC009_C();
  //yuki_665();
  ARC033_D();
  return 0;
}
