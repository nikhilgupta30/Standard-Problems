#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll mod = 1000000007;

int main() {
	
	int t;
	cin>>t;

	while(t--){
		int n,s;
		cin>>n>>s;
		int arr[n];
		for(int i=0;i<n;i++){
			cin>>arr[i];
		}

		std::vector<pair<int,int> > ans;
		int i=0,j=-1;
		int curr = 0;
		while(i<n && j<n){
			if(curr == s){
				ans.push_back(make_pair(i+1,j+1));
				break;
				j++;
				curr += arr[j];
			}
			else if(curr < s){
				j++;
				curr += arr[j];
			}
			else{
				curr -= arr[i];
				i++;
			}
		}

		if(ans.size()==0){
			cout<<"-1\n";
		}else{
			cout<<ans[0].first<<" "<<ans[0].second<<endl;
		}

	}
	
	return 0;

}
