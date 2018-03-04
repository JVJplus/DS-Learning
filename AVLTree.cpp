#include<bits/stdc++.h>
using namespace std;

template<typename T>
class BinaryTreeNode {
public:
	T data;
	int height;
	BinaryTreeNode<T> *left;
	BinaryTreeNode<T> *right;
	BinaryTreeNode(){
		data=0;
		left=NULL;
		right=NULL;
		height=0;
	}

	BinaryTreeNode(T data){
		this->data=data;
		left=NULL;
		right=NULL;
		height=1;
	}
};

template<typename T>
class AVLTree {
private:
	BinaryTreeNode<T> *root;

	BinaryTreeNode<T>* LR(BinaryTreeNode<T>*root){
		BinaryTreeNode<T> *newRoot=root->right;
		root->right=newRoot->left;
		newRoot->left=root;

		return newRoot;		
	}

	BinaryTreeNode<T>* RR(BinaryTreeNode<T>*root){
		BinaryTreeNode<T> *newRoot=root->left;
		root->left=newRoot->right;
		newRoot->right=root;
		
		return newRoot;		
	}

	BinaryTreeNode<T>* add(BinaryTreeNode<T>*root, T data){
		if(!root){
			BinaryTreeNode<T>* ans=new BinaryTreeNode<T>(data);
			return ans;
		}
		if(data<root->data){
			root->left=add(root->left,data);
		}
		else if(data>root->data){
			root->right=add(root->right,data);
		}
		else{ //duplicates not allowed
			return root;
		}

		int balanceFactor=root->left->height - root->right->height;
		if(balanceFactor==-2){ //R Case
			if(data > root -> right->data) //RR
				return LR(root);
			else{ //RL Case
				root->left=RR(root->left);
				return LR(root);
			}
		}
		if(balanceFactor==2){ //L Case
			if(data < root -> left->data) //LL
				return RR(root);
			else{ //LR Case
				root->right=LR(root->right);
				return RR(root);
			}
		}

		return root;
	}

	BinaryTreeNode<T>* remove(BinaryTreeNode<T>*root, T data){

	}	

	void printLevelWise(BinaryTreeNode<T>* root){
		if(!root)
			return;

		queue<BinaryTreeNode<T>*> pendingNodes;
		pendingNodes.push(root);

		while(pendingNodes.size()!=0)
		{
			BinaryTreeNode<T> *front=pendingNodes.front();
			pendingNodes.pop();     

			cout<<front->data<<":";

			if(front->left)
			{   
				cout<<"L:"<<front->left->data<<",";
				pendingNodes.push(front->left);
			}
			else 
				cout<<"L:"<<-1<<",";

			if(front->right)
			{
				cout<<"R:"<<front->right->data;
				pendingNodes.push(front->right);
			}
			else
				cout<<"R:"<<-1;

			cout<<endl;
		}
	}

	void inorder(BinaryTreeNode<T>*root){
		if(!root)
			return;
		inorder(root->left);
		cout<<root->data<<" ";
		inorder(root->right);
	}

public:
	AVLTree(){
		root=NULL;
	}

	void add(T data){
		root=add(root,data);
	}

	void remove(T data){
		root=remove(root,data);
	}

	void print(){
		printLevelWise(root);
	}

	void inorder(){
		inorder(root);
	}

};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);    
#ifndef ONLINE_JUDGE
    // for getting input from input.txt
	freopen("input.txt", "r", stdin);
    // for writing output to output.txt
	freopen("output.txt", "w", stdout);
#endif
///////////////////////////////////////////////////////////////////////////////

	
	time_t curr_time_data = time(NULL);
	cout << ctime(&curr_time_data);

	AVLTree<int> root;
	int n;
	while(cin>>n){
		root.add(n);
	}

	root.print();
	root.inorder();
	cout<<"\n";
}