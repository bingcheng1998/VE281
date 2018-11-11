

```c++
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
```

Let's test this program with the following BST.

<img src="https://ws3.sinaimg.cn/large/006tNbRwgy1fx4l37lcpgj30fg0budgx.jpg" width="200" align=center />

I have tested this program with `main()` below.

```c++
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
```

The answer is shown in the terminal

```ruby
$ make
g++ -g -o bst BST.cpp
./bst
depth is 3
[5(3(1, 4), 9(7(N, 8), N))]
 Get Predecessor of [5] is [4]
 Get Predecessor of [3] is [1]
 Get Predecessor of [9] is [8]
 Get Predecessor of [1] is [NULL]
 Get Predecessor of [4] is [3]
 Get Predecessor of [7] is [5]
 Get Predecessor of [8] is [7]
```

Which is absolutely right!