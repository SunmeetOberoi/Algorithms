#include<iostream>
#include<algorithm>
using namespace std;
struct Tree{
	int key;
	Tree *right;
	Tree *left;
	Tree *p;
};

Tree *insert(Tree *root, Tree *key){
	if(root == NULL){
		root = key;
	}
	else
		if(root->key <= key->key ){
			root->right = insert(root->right, key);
			root->right->p = root;
	}
	else{
		root->left = insert(root->left, key);
		root->left->p = root;
	}
	return root;
}
Tree *newNode(int val){
	Tree *key = new Tree;
	key->key = val;
	key->p = NULL;
	key->left = NULL;
	key->right = NULL;
	return key;
}
Tree *max(Tree *node){
	while(node->right != NULL)
		node=node->right;
	return node;
}

Tree *min(Tree *node){
	while(node->left != NULL)
		node=node->left;
	return node;
}

Tree *Successor(Tree *node){
	if(node->right)
		return min(node->right);
	Tree *parent = node->p;
	while(parent != NULL && node == parent->right){
		node = parent;
		parent = parent->p;
	}
	return parent;
}

Tree *search(Tree *node, int key){
	if(node->key == key || node == NULL)
		return node;
	if(node->key <= key)
		return search(node->right, key);
	else
		return search(node->left, key);
}

Tree *Predecessor(Tree *node){
	if(node->left)
		return max(node->left);
	Tree *parent = node->p;
	while(parent != NULL && node == parent->left){
		node = parent;
		parent = parent->p;
	}
	return parent;
}

void inorder(Tree *node){

	if(node != NULL){
		inorder(node->left);
		cout<<node->key<<" ";
		inorder(node->right);
	}
}

Tree *transplant(Tree *root, Tree *oldNode, Tree *newNode){
	if(oldNode == NULL)
		root = newNode;
	else
		if(oldNode->p->left == oldNode)
			oldNode->p->left = newNode;
	else
		oldNode->p->right = newNode;
	if(newNode != NULL)
		newNode->p = oldNode->p;

	return root;
}

Tree *del(Tree *root, Tree *delNode){
	if(delNode != NULL){
		if(delNode->left == NULL && delNode->right == NULL){
			if(delNode->p->left==delNode)
				delNode->p->left = NULL;
			else
				delNode->p->right = NULL;
			delNode->p = NULL;
		}
		else
			if(delNode->left == NULL)
				root = transplant(root, delNode, delNode->right);
		else
			if(delNode->right == NULL){
				root = transplant(root, delNode, delNode->left);
			}
		else{
			Tree *successor = Successor(delNode);
			if(successor == delNode->right)
			{
				root = transplant(root, delNode, successor);
				successor->left=delNode->left;
			}
			else{
				root = transplant(root, successor, successor->right);
				root = transplant(root, delNode, successor);
				successor->right = delNode->right;
				successor->left = delNode->left;
			}
		}
	}
	return root;
}

int main()
{
	int arr[] = {815, 819, 239, 816, 123, 814, 222, 212, 223, 213, 214, 1, 2, 3};


	int n = sizeof(arr)/sizeof(arr[0]);
	Tree *root = NULL;

	for (int i=0;i<n;i++){
		root = insert(root, newNode(arr[i]));
	}
	cout<<"Tree: "; inorder(root);
	int numb;
	cout<<"\nNumber: ";
	cin>>numb;
	Tree *successor = Successor(search(root, numb)), *predecessor = Predecessor(search(root, numb));
	if(successor != NULL)
		cout<<"Successor: "<<successor->key<<endl;
	if(predecessor != NULL)
		cout<<"Predecessor: "<<predecessor->key<<endl;
	cout<<"Enter Number to be deleted: ";
	cin>>numb;
	root = del(root, search(root, numb));
	inorder(root);
	return 0;
}
