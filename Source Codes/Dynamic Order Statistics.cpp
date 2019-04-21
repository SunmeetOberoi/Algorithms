#include<iostream>
using namespace std;

#define RED 1
#define BLACK 2

class RBTree {
	struct RBNode {
		int key;
		int color;
		int size;
		RBNode* left;
		RBNode* right;
		RBNode* parent;
		RBNode() {}
		RBNode(bool isNIL) {
			key = NULL;
			color = NULL;
			left = NULL;
			right = NULL;
			parent = NULL;
			size = 0;
		}
	};
	RBNode* NIL = new RBNode(true);
	RBNode* root = NIL;
	void insert_fixup(RBNode* node);
	void insert(RBNode* node);
	void right_rotate(RBNode* x);
	void left_rotate(RBNode* x);
	void transplant(RBNode* u, RBNode* v);
	void delete_fixup(RBNode* x);
	void fixsize(RBNode* x);
public:
	RBNode* get_root() { return root; }
	RBNode* search(RBNode* node, int key) {
		if (node->key == key || node == NIL)
			return node;
		if (node->key <= key)
			return search(node->right, key);
		else
			return search(node->left, key);
	}
	RBNode * tree_minimum(RBNode * x) {
		RBNode* y = x;
		while (y->left != NIL)
			y = y->left;
		return y;
	}
	RBNode* os_select(RBNode* x, int i) {
	void fixsize(RBTree* T, RBNode* x);
		if (x->left != NULL) {
			int r = x->left->size + 1;
			if (i == r)
				return x;
			else if (i < r)
				return os_select(x->left, i);
			else
				return os_select(x->right, i - r);
		}
	}
	void delete_node(int x);
	void create_and_insert(int x);
	void inorder(RBNode* x);
	int os_rank(int x);
};

void RBTree::right_rotate(RBNode * x) {
	if (x->left != NIL) {
		RBNode* y = x->left;
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
		y->size = x->size;
		x->size = x->left->size + x->right->size + 1;
	}
	else {
		cout << "Right Rotate Not Possible";
	}
}

void RBTree::left_rotate(RBNode * x) {
	if (x->right != NIL) {
		RBNode* y = x->right;
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
		y->size = x->size;
		x->size = x->left->size + x->right->size + 1;
	}
	else {
		cout << "Left Rotate Not Possible";
	}
}

void RBTree::insert(RBNode * node) {
	RBNode* y = NIL;
	RBNode* x = root;
	while (x != NIL) {
		y = x;
		x->size++;
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
	node->size = 1;
	insert_fixup(node);
}

void RBTree::insert_fixup(RBNode * node) {
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

void RBTree::inorder(RBNode * x) {
	if (x == NIL) {
		return;
	}
	inorder(x->left);
	cout << x->key << ":" << (x->color == 1 ? "RED" : "BLACK") << ":" << x->size << "\t";
	inorder(x->right);
}

int RBTree::os_rank(int x) {
	RBNode* z = search(root, x);
	int r = z->left->size + 1;
	while (z != root) {
		if (z == z->parent->right)
			r = r + z->parent->left->size + 1;
		z = z->parent;
	}
	return r;
}

void RBTree::transplant(RBNode * u, RBNode * v) {
	if (u->parent == NIL)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
	if (v != NIL)
		v->size = u->size;
}

void RBTree::delete_fixup(RBNode * x) {
	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			RBNode* w = x->parent->right;
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
			RBNode* w = x->parent->left;
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

void RBTree::fixsize(RBNode* x) {
	RBNode* y = x;
	while (y != NIL) {
		y->size--;
		y = y->parent;
	}
}

void RBTree::delete_node(int x) {
	RBNode* z = search(root, x);
	if (z != NIL) {
		RBNode* y = z;
		RBNode* x;
		int yOriginalColor = y->color;
		if (z->left == NIL) {
			x = z->right;
			fixsize(z->parent);
			transplant(z, z->right);
		}
		else if (z->right == NIL) {
			x = z->left;
			fixsize(z->parent);
			transplant(z, z->left);
		}
		else {
			y = tree_minimum(z->right);
			fixsize(y->parent);
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
		delete(z);
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
	cout << endl;
	cin >> x;
	cout << x << "th order statistic: " << T.os_select(T.get_root(), x)->key << endl;
	cin >> x;
	cout << "Rank: " << T.os_rank(x);
	return 0;
}

