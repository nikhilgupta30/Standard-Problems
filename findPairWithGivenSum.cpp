#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll mod = 1000000007;

int main(){

    int t;
    cin>>t;

    while(t--){
        ll n,x;
        cin>>n>>x;
        ll arr[n];
        unordered_map<ll,ll> mp;
        for(ll i=0;i<n;i++){
            cin>>arr[i];
            mp[arr[i]]++;
        }

        int yes = 0;
        for(ll i=0;i<n;i++){
            ll temp = x - arr[i];
            if(temp == arr[i]){
                if(mp[arr[i]]>1){
                    yes=1;
                    break;
                }
            }else{
                if(mp[temp]>0){
                    yes = 1;
                    break;
                }
            }
        }
        if(yes){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
    }

	return 0;
}
