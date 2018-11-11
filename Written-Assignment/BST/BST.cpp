#include <iostream>

using namespace std;

#ifndef Key
#define Key int
#endif

struct node {
	Key   key;   // key
	node* left;  // left child
	node* right; // right child
	
	node(Key key_in){
		this->key = key_in;
		this->left = NULL;
		this->right = NULL;
	}
};

node *search(node *root, Key k) { if(root == NULL) return NULL;
if(k == root->key) return root; if(k < root->key)
    return search(root->left, k);
  	else return search(root->right, k);
}

void insert(node *&root, Key key)
{
	if(root == NULL) {
		root = new node(key);
		return;
	}
	if(key < root->key)
		insert(root->left, key);
	else if(key > root->key)
		insert(root->right, key);
}

int levels (node *root){
	if (root == NULL)
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL)
	{
		return 1;
	}
	else if (root -> left == NULL)
	{
		return 1 + levels(root -> right);
	}
	else if (root -> right == NULL) {
		return 1 + levels(root -> left);
	}
	else {
		return max((1 + levels(root -> right)), (1 + levels(root -> left)));
	}
}

int depth(node *root){
	return levels(root) - 1;
}

void print_tree_helper(node *&root){
	if (root == NULL)
	{
		cout<<"N";
		return;
	}
	if (root->left == NULL && root->right == NULL)
	{
		cout<<""<<root->key<<"";
		return;
	}
	else {
		cout<<""<<root->key<<"(";
		print_tree_helper(root->left);
		cout<<", ";
		print_tree_helper(root->right);
		cout<<")";
		return;
	}
}

void print_tree(node *&root){
	cout<<"[";
	print_tree_helper(root);
	cout<<"]"<<endl;
}

node *&findMax(node *&root) {
	if(root->right == NULL) 
		return root; 
	return findMax(root->right);
}

node* getPredHelper(node* root, Key key, node* parent, bool& flag){
	if (root -> key == key)
	{
		if (root->left != NULL)
		{
			return findMax(root->left);
		}
		flag = true;
		return NULL;
	}
	if (root->key > key)
	{
		return getPredHelper(root->left, key, root, flag);
	}
	else if (root->key < key)
	{
		node* temp = getPredHelper(root->right, key, root, flag);
		// cout<<"[flag = "<<flag<<"]";
		if(flag){
			flag = false;
			return root;
		}
		return temp;
	}
	return NULL;
}

node* getPred(node* root, Key key){
	bool flag = false;
	return getPredHelper(root, key, NULL, flag);
}

void print_node(node* root){
	if (root == NULL)
	{
		cout<<"NULL";
	}
	else cout<<root->key;
}

int main(int argc, char *argv[]) {
	const int array_size = 7;
	Key array[array_size] = {5,3,9,1,4,7,8};
	node *root = new node(array[0]);
	for (int i = 1; i < array_size; ++i)
	{
		insert(root, array[i]);
	}
	cout<<"depth is "<<depth(root)<<endl;
	print_tree(root);
	Key key = 1;
	for (int i = 0; i < array_size; ++i)
	{
		cout<<" Get Predecessor of ["<< array[i] <<"] is [";
		print_node(getPred(root, array[i]));
		cout<<"]"<<endl;
	}
}