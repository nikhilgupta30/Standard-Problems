#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll mod = 1000000007;

int main(){

    int t;
    cin>>t;

    while(t--){
        int n;
        cin>>n;
        int arr[n];
        int allneg = 1;
        for(int i=0;i<n;i++){
            cin>>arr[i];
            if(arr[i] >= 0){
                allneg = 0;
            }
        }

        if(allneg){
            int ans = arr[0];
            for(int i=1;i<n;i++){
                if(arr[i] > ans){
                    ans = arr[i];
                }
            }
            cout<<ans<<endl;
            continue;
        }


        int temp = arr[0];
        if(temp < 0){
            temp = 0;
        }
        int ans = temp;
        for(int i=1;i<n;i++){
            temp += arr[i];
            if(temp<0){
                temp = 0;
            }
            else{
                if(ans < temp){
                    ans = temp;
                }
            }
        }

        cout<<ans<<endl;

    }

	return 0;
}
