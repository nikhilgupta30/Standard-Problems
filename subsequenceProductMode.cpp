#include<bits/stdc++.h>

using namespace std;

typedef long long ll;	

int main(){

	ll n,m,x;
	cin>>n>>m>>x;

	vector<ll> arr(n);

	for(ll i=0;i<n;i++){
		cin>>arr[i];
		arr[i] %= m;
	}

	vector<ll> ans(m,0);
	ans[arr[0]] = 1;

	for(ll i=1;i<n;i++){
		vector<ll> add(m,0);
		add[arr[i]] = 1;
		for(ll j=0;j<m;j++){
			if(ans[j]>0){
				add[(j*arr[i])%m] += ans[j];
			}
		}

		for(ll j=0;j<m;j++){
			ans[j] += add[j];
		}
	}	

	cout<<ans[x];

	return 0;
}