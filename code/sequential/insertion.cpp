/** C++ implementation for Red-Black Tree Insertion 
This code is taken from the code provided by 
Dinesh Khandelwal in comments **/
#include <bits/stdc++.h> 
using namespace std; 

enum Color {RED, BLACK}; 

struct Node 
{ 
	int data; 
	bool color; 
	Node *left, *right, *parent; 

	// Constructor 
	Node(int data) 
	{ 
	this->data = data; 
	left = right = parent = NULL; 
	this->color = RED; 
	} 
}; 

// Class to represent Red-Black Tree 
class RBTree 
{ 
private: 
	Node *root; 
protected: 
	void rotateLeft(Node *&, Node *&); 
	void rotateRight(Node *&, Node *&); 
	void fixViolation(Node *&, Node *&); 
public: 
	// Constructor 
	RBTree() { root = NULL; } 
	void insert(const int &n); 
	int rankofnode( Node *&temp, int rank);
}; 

/* A utility function to insert a new node with given key 
in BST */
Node* BSTInsert(Node* root, Node *pt) 
{ 
	/* If the tree is empty, return a new node */
	if (root == NULL) 
	return pt; 

	/* Otherwise, recur down the tree */
	if (pt->data < root->data) 
	{ 
		root->left = BSTInsert(root->left, pt); 
		root->left->parent = root; 
	} 
	else if (pt->data > root->data) 
	{ 
		root->right = BSTInsert(root->right, pt); 
		root->right->parent = root; 
	} 

	/* return the (unchanged) node pointer */
	return root; 
} 
void RBTree::rotateLeft(Node *&root, Node *&pt) 
{ 
	Node *pt_right = pt->right; 

	pt->right = pt_right->left; 

	if (pt->right != NULL) 
		pt->right->parent = pt; 

	pt_right->parent = pt->parent; 

	if (pt->parent == NULL) 
		root = pt_right; 

	else if (pt == pt->parent->left) 
		pt->parent->left = pt_right; 

	else
		pt->parent->right = pt_right; 

	pt_right->left = pt; 
	pt->parent = pt_right; 
} 

void RBTree::rotateRight(Node *&root, Node *&pt) 
{ 
	Node *pt_left = pt->left; 

	pt->left = pt_left->right; 

	if (pt->left != NULL) 
		pt->left->parent = pt; 

	pt_left->parent = pt->parent; 

	if (pt->parent == NULL) 
		root = pt_left; 

	else if (pt == pt->parent->left) 
		pt->parent->left = pt_left; 

	else
		pt->parent->right = pt_left; 

	pt_left->right = pt; 
	pt->parent = pt_left; 
} 
void RBTree::fixViolation(Node *&root, Node *&pt) 
{ 
	Node *parent_pt = NULL; 
	Node *grand_parent_pt = NULL; 

	while ((pt != root) && (pt->color != BLACK) && 
		(pt->parent->color == RED)) 
	{ 

		parent_pt = pt->parent; 
		grand_parent_pt = pt->parent->parent; 

		/* Case : A 
			Parent of pt is left child of Grand-parent of pt */
		if (parent_pt == grand_parent_pt->left) 
		{ 

			Node *uncle_pt = grand_parent_pt->right; 

			/* Case : 1 
			The uncle of pt is also red 
			Only Recoloring required */
			if (uncle_pt != NULL && uncle_pt->color == RED) 
			{ 
				grand_parent_pt->color = RED; 
				parent_pt->color = BLACK; 
				uncle_pt->color = BLACK; 
				pt = grand_parent_pt; 
			} 

			else
			{ 
				/* Case : 2 
				pt is right child of its parent 
				Left-rotation required */
				if (pt == parent_pt->right) 
				{ 
					rotateLeft(root, parent_pt); 
					pt = parent_pt; 
					parent_pt = pt->parent; 
				} 

				/* Case : 3 
				pt is left child of its parent 
				Right-rotation required */
				rotateRight(root, grand_parent_pt); 
				swap(parent_pt->color, grand_parent_pt->color); 
				pt = parent_pt; 
			} 
		} 

		/* Case : B 
		Parent of pt is right child of Grand-parent of pt */
		else
		{ 
			Node *uncle_pt = grand_parent_pt->left; 

			/* Case : 1 
				The uncle of pt is also red 
				Only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt->color == RED)) 
			{ 
				grand_parent_pt->color = RED; 
				parent_pt->color = BLACK; 
				uncle_pt->color = BLACK; 
				pt = grand_parent_pt; 
			} 
			else
			{ 
				/* Case : 2 
				pt is left child of its parent 
				Right-rotation required */
				if (pt == parent_pt->left) 
				{ 
					rotateRight(root, parent_pt); 
					pt = parent_pt; 
					parent_pt = pt->parent; 
				} 

				/* Case : 3 
				pt is right child of its parent 
				Left-rotation required */
				rotateLeft(root, grand_parent_pt); 
				swap(parent_pt->color, grand_parent_pt->color); 
				pt = parent_pt; 
			} 
		} 
	} 

	root->color = BLACK; 
}


//According to tree
int RBTree::rankofnode(Node *&temp,int rnk){
	while(temp->left != NULL || temp->right != NULL){
		temp=temp->left;
		if(temp->color == BLACK){rnk++;}
	}
	return rnk;
}


void RBTree::insert(const int &data) 
{ 
	Node *pt = new Node(data); 
	
	root = BSTInsert(root, pt); 

	fixViolation(root, pt); 

	// if(pt->color == BLACK){cout<<"Rank of node("<<data<<"): "<<rankofnode(pt,1)<<endl;}
	// else{cout<<"Rank of node("<<data<<"): "<<rankofnode(pt,0)<<endl;}

	

} 

int main() 
{ 
	RBTree tree; 
	
	tree.insert(7);
	tree.insert(6); 
	tree.insert(5); 
	tree.insert(4); 


	clock_t begin = clock();
	tree.insert(3);
	clock_t end = clock();
	double time =(double )(end-begin)/CLOCKS_PER_SEC;


	
	cout<<"Sequential Time: "<<time<<endl; 
	tree.insert(2); 
	tree.insert(1); 

	return 0; 
} 
