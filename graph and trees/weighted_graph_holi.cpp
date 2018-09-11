#include<iostream>
#include<list>
#include<set>
#include<limits.h>

using namespace std;

typedef long long ll;

class Graph{

    ll V;
    list<pair<ll,ll> > *l;
public:
    Graph(ll v){
        V = v;
        l = new list<pair<ll,ll> >[V];
    }

    void addEdge(ll u,ll v,ll cost,bool bidir=true){
        l[u].push_back(make_pair(v,cost));
        if(bidir){
            l[v].push_back(make_pair(u,cost));
        }
    }
    void dfs(ll i,ll *cnt,bool*vis){

        vis[i] = true;

        for(auto it=l[i].begin();it!=l[i].end();it++){
            if(!vis[it->first]){
                dfs(it->first,cnt,vis);
                cnt[i] += cnt[it->first];
            }

        }
       // cout<<cnt[i]<<endl;

    }

    ll dfsCost(ll i,ll *cnt,bool *vis){
        vis[i] = true;
        ll cost = 0;
        for(auto it=l[i].begin();it!=l[i].end();it++){
            if(!vis[it->first]){
                 cost += 2*it->second*min(V-cnt[it->first],cnt[it->first]) + dfsCost(it->first,cnt,vis);
            }
        }
        return cost;

    }

    ll dfsHoliday(){
        ll *cnt = new ll[V];
        for(ll i=0;i<V;i++){
            cnt[i] = 1;
        }

        bool *visited = new bool[V]{0};

        dfs(0,cnt,visited);

        bool* visited2 = new bool[V]{0};

        return dfsCost(0,cnt,visited2);

    }

    
};


int main(){
    
    int t;
    cin>>t;

    for(int q=1;q<=t;q++){
        ll n;
        cin>>n;
        Graph g(n);

        for(ll i=0;i<n-1;i++){
            ll u,v,w;
            cin>>u>>v>>w;
            g.addEdge(u-1,v-1,w);
        }
        cout<<"Case #"<<q<<": "<<g.dfsHoliday()<<endl;
    }

    return 0;
}
