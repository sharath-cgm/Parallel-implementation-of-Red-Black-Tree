#include<iostream>
// #include <omp.h>
using namespace std;

void singleRotation(int* tree, int max, int about){
	int parent, right, left, sibling, current, parentIndex = (about-1)/2, siblingIndex = (about == parentIndex*2 + 1) ? parentIndex*2 + 2 : parent*2 +1;
	current = tree[about];
	parent = tree[parentIndex];
	sibling = tree[siblingIndex];
	left = tree[about*2 + 1]; right = tree[2*about +2];

	tree[about] = left;
	tree[parentIndex] = current;
	tree[siblingIndex] = parent;
	tree[2*siblingIndex + 1] = right;
	tree[2*siblingIndex + 2] = sibling;
	tree[about*2 + 1] = -1;
	tree[about*2 + 2] = -1;
}

void doubleRotation(int* tree, int max, int about){
	int current, parent, left, right, sibling, grandparent, uncle, uncleIndex, grandparentIndex, parentIndex;
	parentIndex = (about-1)/2; 
	grandparentIndex = (parentIndex-1)/2;
	uncleIndex = (parentIndex == 2*grandparentIndex + 1)? 2*grandparentIndex + 2 : 2* grandparentIndex+1;

	current = tree[about]; parent = tree[parentIndex]; left = tree[2*about + 1]; right = tree[2*about + 2]; //sibling = tree[(about == 2*parentIndex + 1)? 2*parentIndex + 2 : 2* parentIndex+1]; 
	grandparent = tree[grandparentIndex]; uncle = tree[uncleIndex];

	tree[grandparentIndex] = current;
	// tree[parentIndex] = parent;
	tree[about] = left; 
	tree[uncleIndex] = grandparent;
	tree[uncleIndex*2 + 1] = right;
	tree[uncleIndex*2 + 2] = uncle;
	tree[2*about + 1] = -1; tree[2*about + 2] = -1;
}

int main(){
	int max ; cin>>max;
	int tree[max]; 
	for(int i=0; i<max; i++){
		cin>>tree[i];
	}

	int about = 3; //cin>>about;
	singleRotation(tree, max, about);
	// doubleRotation(tree, max, about);

	for(int i=0; i<max; i++){
		cout<<tree[i]<<" ";
	}

	return 0;
}