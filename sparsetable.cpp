#include<bits/stdc++.h>
using namespace std;
using Int = long long;
//BEGIN CUT HERE
template<typename T>
struct SparseTable{
  using F = function<T(T,T)>;
  vector<vector<T> > dat;
  vector<int> ht;
  const F f;
  
  SparseTable(){}
  SparseTable(int n,F f):f(f){init(n);}
  
  void init(int n){
    int h=1;
    while((1<<h)<n) h++;
    dat.assign(h,vector<T>(n));
    ht.assign(n+1,0);
    for(int j=2;j<=n;j++) ht[j]=ht[j>>1]+1;
  }
  
  void build(int n,vector<T> &v){
    int h=1;
    while((1<<h)<n) h++;
    for(int j=0;j<n;j++) dat[0][j]=v[j];
    for(int i=1,p=1;i<h;i++,p<<=1)
      for(int j=0;j<n;j++)
        dat[i][j]=f(dat[i-1][j],dat[i-1][min(j+p,n-1)]);
  };

  T query(int a,int b){
    int l=b-a;
    return f(dat[ht[l]][a],dat[ht[l]][b-(1<<ht[l])]);
  }
};
//END CUT HERE


signed ARC023_D(){
  int n,m;
  cin>>n>>m;
  vector<Int> a(n),x(m);
  for(int i=0;i<n;i++) cin>>a[i];
  for(int i=0;i<m;i++) cin>>x[i];

  SparseTable<Int>::F f=[](Int a,Int b){return __gcd(a,b);};
  SparseTable<Int> st(n,f);
  st.build(n,a);
  
  map<Int, Int> ans;
  for(int i=0;i<n;i++){
    int l=i;
    Int pre=a[i],lst=st.query(i,n);
    while(lst!=pre){
      int r=n,pl=l;
      while(l+1<r){
	int m=(l+r)>>1;
	if(st.query(i,m)!=pre) r=m;
	else l=m;
      }
      ans[pre]+=l-pl;
      pre=st.query(i,r);
    }
    ans[lst]+=n-l;
  }
  
  for(int i=0;i<m;i++) cout<<ans[x[i]]<<endl;
  return 0;
}

/*
  verified on 2018/04/11
  https://beta.atcoder.jp/contests/arc023/tasks/arc023_4
*/

signed main(){
  ARC023_D();
  return 0;
}

