#include<iostream>
#include <math.h>
#include <omp.h>
using namespace std;

int search(int q,int N,int tree[]){
	int index=0;
	int result=-1;

	while(index<N){
		if(tree[index] <= -1){
			result = index;
			break;
		}

		if(tree[index]==q){
			result=index;
			// cout<<"found";
			break;
		}
		else if(tree[index]>q){
			// if (result == -1) result = index;
			index=2*index+1;
		}
		else{
			// if (result == -1) result = index;
			index=2*index+2;
		}
	}
	if (result <= -1) result = index;
	return result;
}

void doubleRotation(int* tree, int* color, int about){
	int current, parent, left, right, sibling, grandparent, uncle, uncleIndex, grandparentIndex, parentIndex;
	parentIndex = (about-1)/2; 
	grandparentIndex = (parentIndex-1)/2;
	uncleIndex = (parentIndex == 2*grandparentIndex + 1)? 2*grandparentIndex + 2 : 2* grandparentIndex+1;

	current = tree[about]; parent = tree[parentIndex]; left = tree[2*about + 1]; right = tree[2*about + 2]; //sibling = tree[(about == 2*parentIndex + 1)? 2*parentIndex + 2 : 2* parentIndex+1]; 
	grandparent = tree[grandparentIndex]; uncle = tree[uncleIndex];

	tree[grandparentIndex] = current;
	tree[parentIndex] = parent;
	tree[about] = left; 
	tree[uncleIndex] = grandparent;
	tree[uncleIndex*2 + 1] = right;
	tree[uncleIndex*2 + 2] = uncle;
	tree[2*about + 1] = -1; tree[2*about + 2] = -1;
	color[uncleIndex] = 1;
	color[2*about + 2] = -1;
	color[grandparent] = 0;
 }

int main(){
	// input
	int n; cin>>n;
	// int max = pow(2, ceil(log2(n+2))) -1;
	int tree[30], color[30];
	for(int i=0; i<30; i++){
		tree[i] = -1;
		color[i] = -1;
	}
	for(int i=0; i<n; i++){
		cin>>tree[i];
	}
	for(int i=0; i<n; i++){
		cin>>color[i];
	}

	// operation begins

	// search -> O(log(n))
	int query; cin>>query;
	int position = search(query,n,tree);
	tree[position] = query;
	color[position] = 1;

	// O(1) -> rotation
	doubleRotation(tree, color, position);

	// output
	cout<<"30"<<endl;
	for(int i=0; i<30; i++){
		cout<<tree[i]<<" ";
	} cout<<endl;
	for(int i=0; i<30; i++){
		cout<<color[i]<< " ";
	}cout<<endl;
	return 0;
}