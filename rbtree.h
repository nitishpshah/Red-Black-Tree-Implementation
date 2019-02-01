#ifndef RB_TREE
#define RB_TREE

#include <iostream>
#include <string>
#define RED 0
#define BLACK 1

template <class dataStruct>
struct rb_tree_node{
	dataStruct data;
	rb_tree_node<dataStruct> *left;
	rb_tree_node<dataStruct> *right;
	rb_tree_node<dataStruct> *parent;
	bool color; //0 for red, 1 for black

	rb_tree_node(){
		data = 0;
		parent = NULL;
		left = NULL;
		right = NULL;
		color = 0;
	}

	rb_tree_node(dataStruct x, bool b = RED, rb_tree_node<dataStruct> *p = NULL, rb_tree_node<dataStruct> *l = NULL, rb_tree_node<dataStruct> *r = NULL){
		data = x;
		parent = p;
		left = l;
		right = r;
		color = b;
	}

	rb_tree_node(dataStruct x, rb_tree_node<dataStruct>*  defaultt, bool b = RED){
		data = x;
		parent = defaultt;
		left = defaultt;
		right = defaultt;
		color = b;
	}
};

template <class dataStruct>
class rbtree{
      public:

	rb_tree_node<dataStruct> *root;
	rb_tree_node<dataStruct> *nil;	 //sentinel

	rbtree(){
		nil = new rb_tree_node<dataStruct>(0);	//all members of sentinel NULL
		root = nil;
	}

	bool is_empty();
	bool is_lchild(rb_tree_node<dataStruct> *n);
	bool is_rchild(rb_tree_node<dataStruct> *n);
	bool is_leaf(rb_tree_node<dataStruct> *n);
	int height_node(rb_tree_node<dataStruct>* r);
	int bh_node(rb_tree_node<dataStruct>* r);
	int height();
	int bh();

	rb_tree_node<dataStruct> *min();
	rb_tree_node<dataStruct> *max();
	rb_tree_node<dataStruct> *min(rb_tree_node<dataStruct> *r);
	rb_tree_node<dataStruct> *max(rb_tree_node<dataStruct> *r);
	rb_tree_node<dataStruct> *predecessor(rb_tree_node<dataStruct> *n);
	rb_tree_node<dataStruct> *successor(rb_tree_node<dataStruct> *n);
	rb_tree_node<dataStruct> *predecessor(dataStruct n);
	rb_tree_node<dataStruct> *successor(dataStruct n);
	rb_tree_node<dataStruct> *search_lower_bound(dataStruct value);
	rb_tree_node<dataStruct> *search(dataStruct value);

	void swap_nodes(rb_tree_node<dataStruct> *q, rb_tree_node<dataStruct> *r);
	void right_rotate(rb_tree_node<dataStruct> *y);
	void left_rotate(rb_tree_node<dataStruct> *y);
	void insert_fixup(rb_tree_node<dataStruct> *node);
	void insert(dataStruct value);
	void linear_display();
	void linear_display2(rb_tree_node<dataStruct> *r);
};

template <class dataStruct>
int rbtree<dataStruct>::height_node(rb_tree_node<dataStruct>* r) {
	if (r == nil) {
		return 0;
	}
	int height_left = height_node(r->left);
	int height_right = height_node(r->right);
	return height_left > height_right ? height_left+1: height_right+1;
}

template <class dataStruct>
int rbtree<dataStruct>::height() {
	return height_node(root);
}

template <class dataStruct>
int rbtree<dataStruct>::bh() {
	//returns 0 when the black heights of 2 paths dont match
	//else returns the black height including the roots and leaves count
	return bh_node(root);
}

template <class dataStruct>
int rbtree<dataStruct>::bh_node(rb_tree_node<dataStruct>* r) {
	if (r == nil) {
		return 1;
	}
	int bhl = bh_node(r->left);
	int bhr = bh_node(r->right);
	if (bhl == 0 || bhr == 0) {
		return 0;
	}
	if (bhl != bhr) {
		return 0;
	}
	int bh = bhr;
	if (r->color == BLACK) {
		bh += 1;
	}
	return bh;
}

template <class dataStruct>
bool rbtree<dataStruct>::is_empty(){
	if (root == nil){
		return true;
	}
	else
		return false;
}

template <class dataStruct>
bool rbtree<dataStruct>::is_leaf(rb_tree_node<dataStruct> *n){
	if (n->left == nil && n->right == nil){
		return true;
	}
	else
		return false;
}

template <class dataStruct>
bool rbtree<dataStruct>::is_lchild(rb_tree_node<dataStruct> *n){
	if (n->parent == nil){
		return false;
	}
	if (n == n->parent->left){
		return true;
	}
	else
		return false;
}

template <class dataStruct>
bool rbtree<dataStruct>::is_rchild(rb_tree_node<dataStruct> *n){
	if (n->parent == nil){
		return false;
	}
	if (n == n->parent->right){
		return true;
	}
	else
		return false;
}

template <class dataStruct>
rb_tree_node<dataStruct> *rbtree<dataStruct>::predecessor(rb_tree_node<dataStruct> *n){
	if (n->left != nil){
		return max(n->left);
	}
	else{
		while (is_lchild(n)){
			n = n->parent;
		}
		return n->parent;
	}
}

template <class dataStruct>
rb_tree_node<dataStruct> *rbtree<dataStruct>::successor(rb_tree_node<dataStruct> *n){
	if (n->right != nil){
		return min(n->right);
	}
	else{
		while (is_rchild(n)){
			n = n->parent;
		}
		return n->parent;
	}
}

template <class dataStruct>
rb_tree_node<dataStruct> *rbtree<dataStruct>::predecessor(dataStruct n){
	return predecessor(search(n));
}

template <class dataStruct>
rb_tree_node<dataStruct> *rbtree<dataStruct>::successor(dataStruct n){
	return successor(search(n));
}

template <class dataStruct>
rb_tree_node<dataStruct> *rbtree<dataStruct>::min(rb_tree_node<dataStruct> *r){
	if (is_empty()){
		return NULL;
	}
	else{
		rb_tree_node<dataStruct> *cursor = r;
		while (cursor->left != nil){
			cursor = cursor->left;
		}
		return cursor;
	}
}

template <class dataStruct>
rb_tree_node<dataStruct> *rbtree<dataStruct>::max(rb_tree_node<dataStruct> *r){
	if (is_empty()){
		return NULL;
	}
	else{
		rb_tree_node<dataStruct> *cursor = r;
		while (cursor->right != nil){
			cursor = cursor->right;
		}
		return cursor;
	}
}

template <class dataStruct>
rb_tree_node<dataStruct> *rbtree<dataStruct>::max(){
	return max(root);
}

template <class dataStruct>
rb_tree_node<dataStruct> *rbtree<dataStruct>::min(){
	return min(root);
}

template <class dataStruct>
rb_tree_node<dataStruct> *rbtree<dataStruct>::search_lower_bound(dataStruct value){
	//returns the equal or next highest element in the tree
	if (is_empty()){
		return NULL;
	}
	else{
		rb_tree_node<dataStruct> *cursor = root;
		while (cursor != nil){
			dataStruct x = cursor->data;
			if (x == value){
				return cursor;
			}
			else if (x > value){
				if (cursor->left == nil){
					break;
				}
				cursor = cursor->left;
			}
			else
			{
				if (cursor->right == nil)
				{
					cursor = successor(cursor);
					break;
				}
				cursor = cursor->right;
			}
		}
		return cursor;
	}
}


template <class dataStruct>
rb_tree_node<dataStruct> *rbtree<dataStruct>::search(dataStruct value){
	//returns NULL if not found, else returns the node address
	rb_tree_node<dataStruct> *search_result = search_lower_bound(value);
	if(search_result->data == value){
		return search_result;
	}else{
		return NULL;
	}
}

template <class dataStruct>
void rbtree<dataStruct>::swap_nodes(rb_tree_node<dataStruct> *q, rb_tree_node<dataStruct> *r){
	rb_tree_node<dataStruct> *temp = NULL;
	temp = q->parent;
	q->parent = r->parent;
	r->parent = temp;
}

template <class dataStruct>
void rbtree<dataStruct>::right_rotate(rb_tree_node<dataStruct> *y){
	rb_tree_node<dataStruct> *x = y->left;
	if (x == nil){
		//std::cout<< "cannot rotate right" <<std::endl;
		return;
	}

	if (x == root) {
		root = y;
	}
	y->left = x->right;
	if (y->left != nil){
		y->left->parent = y;
	}

	if (y->parent != nil){
		if (is_lchild(y)){
			y->parent->left = x;
		}
		else{
			y->parent->right = x;
		}
	}
	x->parent = y->parent;
	y->parent = x;
	x->right = y;
}

template <class dataStruct>
void rbtree<dataStruct>::left_rotate(rb_tree_node<dataStruct> *x){
	//if root changes?
	rb_tree_node<dataStruct> *y = x->right;
	if (y == nil){
		//std::cout<< "cannot rotate left" <<std::endl;
		return;
	}
	if (x == root) {
		root = y;
	}
	x->right = y->left;
	if (y->left != nil){
		y->left->parent = x;
	}
	if (x->parent != nil){
		if (is_lchild(x)){
			x->parent->left = y;
		}
		else{
			x->parent->right = y;
		}
	}
	y->parent = x->parent;
	x->parent = y;
	y->left = x;
}

template <class dataStruct>
void rbtree<dataStruct>::insert_fixup(rb_tree_node<dataStruct>* node) {
	while (1) {
		rb_tree_node<dataStruct>* prnt = node->parent, *granny, *temp;
		if (prnt == nil) {
			//if node n is root
			node->color = BLACK;
			break;
		}
		if (prnt->color == BLACK) {
			break;
		}
		//if node is a child of root, then the color of the parent, ie the root will always be black, so the look stops before this line
		//if node not a child of root, the =n gprnt not nil
		granny = prnt->parent;
		temp = granny->right;
		//temp is the uncle
		if (prnt != temp) {
			//parent is left child of granny
			if (temp != nil && temp->color == RED) {
				//case 1: nodes uncle is red
				//paint parent to black, granny to red, uncle to black
				granny->color = RED;
				prnt->color = BLACK;
				temp->color = BLACK;
				node = granny;
				continue;
			}
			temp = prnt->right;
			if (node == temp) {
				//case 2: nodes uncle is black and the node is parents right child
				left_rotate(prnt);
				prnt->color = RED;
				//swap parent and node
				temp = node;
				node = prnt;
				prnt = temp;
				//reduced to case 3
			}
			//case 3: nodes uncle is black and node is a left child
			right_rotate(granny);
			prnt->color = BLACK;
			granny->color = RED;
			break;
		}
		else {
			temp = granny->left;
			//mirror cases of the three above
			if (temp != nil && temp->color == RED) {
				//case 1: nodes uncle is red
				granny->color = RED;
				prnt->color = BLACK;
				temp->color = BLACK;
				node = granny;
				continue;
			}
			temp = prnt->left;
			if (node == temp) {
				//case 2: nodes uncle is black and the node is left child
				right_rotate(prnt);
				prnt->color = RED;
				temp = node;
				node = prnt;
				prnt = temp;
				//reduced to case 3
			}
			//case 3: nodes uncle is black and node is a right child
			left_rotate(granny);
			prnt->color = BLACK;
			granny->color = RED;
			break;
		}
	}
	root->color = BLACK;
}

template <class dataStruct>
void rbtree<dataStruct>::insert(dataStruct value){
	/*
		look at root, if greater than or equal to, then insert at its successor, else insert at predecessor
	*/
	rb_tree_node<dataStruct> *new_node = new rb_tree_node<dataStruct>(value, nil, 1); //color black
	if (is_empty()){
		root = new_node;
	}
	else{
		rb_tree_node<dataStruct> *cursor = root;
		//get position to insert the new node...and insert
		while (1){
			if (cursor->data >= value){
				if (cursor->left != nil){
					cursor = cursor->left;
				}
				else{
					cursor->left = new_node;
					new_node->parent = cursor;
					break;
				}
			}
			else{
				if (cursor->right != nil){
					cursor = cursor->right;
				}
				else{
					cursor->right = new_node;
					new_node->parent = cursor;
					break;
				}
			}
		}
		new_node->color = RED;
		insert_fixup(new_node);
		return;
	}
}

template <class dataStruct>
void rbtree<dataStruct>::linear_display(){
	linear_display2(root);
	std::cout<< std::endl;
}

template <class dataStruct>
void rbtree<dataStruct>::linear_display2(rb_tree_node<dataStruct> *r){
	if (r == nil){
		return;
	}
	if (r->left == nil && r->right == nil){
		std::cout << r->data<< "(" << r->color << ")";
		return;
	}
	std::cout << r->data <<"("<<r->color<<")";
	std::cout << " [";
	if (r->left != nil){
		linear_display2(r->left);
	}
	std::cout << "] [";
	if (r->right != nil){
		linear_display2(r->right);
	}
	std::cout << "] ";
}

#endif