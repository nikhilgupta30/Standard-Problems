#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll sumH=0;

struct node{

    ll key;
    struct node *left, *right;

};
  
// A utility function to create a new BST node
struct node *newNode(ll item){

    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;

}
  
/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, ll key){

    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);
 
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);   
 
    /* return the (unchanged) node pointer */
    return node;

}

// A utility function to do inorder traversal of BST
ll inorder(struct node *root){
    //cout<<"ok1\n";
	if(root->left == NULL && root->right == NULL){
		//cout<<"ok3\n";
		return 1;
	}

	//cout<<"ok2\n";

	ll maxL=0,maxR=0;
	if(root->left != NULL){
		maxL = inorder(root->left);
	}

	if(root->right != NULL){
		maxR = inorder(root->right);
	}

	ll ans = max(maxL,maxR);
	//cout<<ans<<endl;
	sumH = sumH + ans;
	return ans+1;

}

void inorder2(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout<<root->key<<endl;
        inorder(root->right);
    }
}

int main(){

	ll n;
	cin>>n;

	vector<ll> arr(n);

	for(ll i=0;i<n;i++){
		cin>>arr[i];
	}

	struct node *root = NULL;
	root = insert(root,arr[0]);

	for(ll i=1;i<n;i++){
		insert(root,arr[i]);
	}

	//inorder2(root);
	cout<<inorder(root)-1<<endl;
	cout<<sumH;

	return 0;
}