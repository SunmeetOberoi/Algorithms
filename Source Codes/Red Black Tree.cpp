#include<iostream>
#include<conio.h>
using namespace std;

#define RED 1
#define BLACK 2

class RBTree {
	struct RBNode {
		int key;
		int color;
		RBNode *left;
		RBNode *right;
		RBNode *parent;
		RBNode() {}
		RBNode(void *t) {
			key = -1;
			color = 0;
			left = NULL;
			right = NULL;
			parent = NULL;
		}
	};
	RBNode *NIL = new RBNode(NULL);
	RBNode *root = NIL;
	void insert_fixup(RBNode* node);
	void insert(RBNode* node);
	void right_rotate(RBNode *x);
	void left_rotate(RBNode *x);
	void transplant(RBNode *u, RBNode *v);
	void delete_fixup(RBNode *x);
public:
	RBNode *get_root() {return root;}
	RBNode *search(RBNode *node, int key) {
		if (node->key == key || node == NIL)
			return node;
		if (node->key <= key)
			return search(node->right, key);
		else
			return search(node->left, key);
	}
	void delete_node(int x);
	void create_and_insert(int x);
	void inorder(RBNode *x);
	RBNode *tree_minimum(RBNode *x) {
		RBNode *y = x;
		while (y->left != NIL)
			y = y->left;
		return y;
	}
};

void RBTree::right_rotate(RBNode *x) {
	if (x->left != NIL) {
		RBNode *y = x->left;
		x->left = y->right;

		if (y->right != NIL)
			y->right->parent = x;
		y->parent = x->parent;

		if (x->parent == NIL)
			root = y;

		else if (x->parent->left == x)
			x->parent->left = y;

		else
			x->parent->right = y;

		x->parent = y;
		y->right = x;
	}
	else {
		cout << "Right Rotate Not Possible";
	}
}

void RBTree::left_rotate(RBNode *x) {
	if (x->right != NIL) {
		RBNode *y = x->right;
		x->right = y->left;

		if (y->left != NIL)
			y->left->parent = x;
		y->parent = x->parent;

		if (x->parent == NIL)
			root = y;

		else if (x == x->parent->left)
			x->parent->left = y;

		else
			x->parent->right = y;

		x->parent = y;
		y->left = x;
	}
	else {
		cout << "Left Rotate Not Possible";
	}
}

void RBTree::insert(RBNode *node) {
	RBNode *y = NIL;
	RBNode *x = root;
	while (x != NIL) {
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	node->parent = y;
	if (y == NIL)
		root = node;
	else if (node->key < y->key)
		y->left = node;
	else
		y->right = node;
	node->left = NIL;
	node->right = NIL;
	node->color = RED;
	insert_fixup(node);
}

void RBTree::insert_fixup(RBNode *node){
	while (node->parent->color == RED) {
		if (node->parent == node->parent->parent->left) {
			RBNode* y = node->parent->parent->right;
			if (y->color == RED) {
				node->parent->color = BLACK;
				y->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else if (node == node->parent->right) {
				node = node->parent;
				left_rotate(node);
			}
			else {
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				right_rotate(node->parent->parent);
			}
		}
		else {
			RBNode* y = node->parent->parent->left;
			if (y->color == RED) {
				node->parent->color = BLACK;
				y->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else if (node == node->parent->left) {
				node = node->parent;
				right_rotate(node);
			}
			else {
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				left_rotate(node->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

void RBTree::create_and_insert(int x) {
	RBNode* newNode = new RBNode;
	//RBNode* newNode = (RBNode*)malloc(sizeof(RBNode));
	newNode->key = x;
	insert(newNode);
}

void RBTree::inorder(RBNode *x) {
	if (x == NIL) {
		return;
	}
	inorder(x->left);
	cout << x->key << ":" << (x->color == 1 ? "RED" : "BLACK") << "\t";
	inorder(x->right);
}

void RBTree::transplant(RBNode *u, RBNode *v) {
	if (u->parent == NIL)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

void RBTree::delete_fixup(RBNode * x){
	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			RBNode *w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				left_rotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else if (w->right->color == BLACK) {
				w->left->color = BLACK;
				w->color = RED;
				right_rotate(w);
			}
			else {
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				left_rotate(x->parent);
				x = root;
			}
		}
		else {
			RBNode *w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				right_rotate(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else if (w->left->color == BLACK) {
				w->right->color = BLACK;
				w->color = RED;
				left_rotate(w);
			}
			else {
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				right_rotate(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

void RBTree::delete_node(int x){
	RBNode *z = search(root, x);
	if (z != NIL) {
		RBNode *y = z;
		RBNode *x;
		int yOriginalColor = y->color;
		if (z->left == NIL) {
			x = z->right;
			transplant(z, z->right);
		}
		else if (z->right == NIL) {
			x = z->left;
			transplant(z, z->left);
		}
		else {
			y = tree_minimum(z->right);
			yOriginalColor = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else {
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		if (yOriginalColor == BLACK)
			delete_fixup(x);
	}
}

int main() {
	RBTree T;
	int x;
	// insert and delete till non-zero values are encountered
	do {
		cin >> x;
		T.create_and_insert(x);
	} while (x);
	cout << endl << endl << endl;
	T.inorder(T.get_root());
	cout << endl << endl << endl;
	do {
		cin >> x;
		T.delete_node(x);
	} while (x);
	cout << endl << endl << endl;
	T.inorder(T.get_root());
	_getch();
	return 0;
}