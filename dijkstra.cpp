using namespace std;
#include<bits/stdc++.h>
//BEGIN CUT HERE
//{{{ dijkstra(start, graph, inf_for_initing_cost)
template <typename cost, typename node>
vector<cost> dijkstra(
    // return d (d[i]:iへの最短距離)
    node s, //start node
    vector<vector<pair<node, cost>>> & G,  //Graph
    cost inf // cost初期化用の十分大きな値
    ){
  using P = pair<cost, node>; // <cost, v> costをkeyにするため
  node n=G.size();
  vector<cost> d(n, inf);  // 最短距離
  priority_queue<P, vector<P>, greater<P>> q;

  d[s]=0; q.emplace(d[s], s);
  while(!q.empty()){
    P p=q.top();q.pop();
    node v=p.second;
    if(d[v]<p.first) continue;
    for(auto& e:G[v]){
      node u=e.first;
      cost c=e.second;
      if(d[u]>d[v]+c){
        d[u]=d[v]+c;
        q.emplace(d[u],u);
      }
    }
  }
  return d;
} //}}}
//END CUT HERE

signed main(){
  int n,l; cin>>n>>l;
  using Int = long long;
  using P = pair<int, Int>;
  vector<vector<P> > G(l+1);  // G[i] = [(node, cost), (node, cost), ・・・]
  for(int i=0;i<n;i++){
    int a,b,c;
    cin>>a>>b>>c;
    G[a].emplace_back(b,c);
  }
  for(int i=0;i<l;i++)
    G[i+1].emplace_back(i,0);
  cout<<dijkstra(0,G,(1LL<<55LL))[l]<<endl;
  return 0;
}

/*
   verified on 2017/11/27
http://arc026.contest.atcoder.jp/tasks/arc026_3
*/
