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

void singleRotation(int* tree, int* color, int about){
	int parent, right, left, sibling, current, parentIndex = (about-1)/2, siblingIndex = (about == parentIndex*2 + 1) ? parentIndex*2 + 2 : parent*2 +1;
	current = tree[about];
	parent = tree[parentIndex];
	sibling = tree[siblingIndex];
	left = tree[about*2 + 1]; right = tree[2*about +2];
	int color_current = color[about]; int color_parent = color[(about-1)/2]; int color_left = color[2*about + 1]; int color_right = color[2*about+2];

	tree[about] = left;
	tree[parentIndex] = current;
	tree[siblingIndex] = parent;
	tree[2*siblingIndex + 1] = right;
	tree[2*siblingIndex + 2] = sibling;
	tree[about*2 + 1] = -1;
	tree[about*2 + 2] = -1;
	color[about] = color_left;
	color[siblingIndex] = color_current;
}

int main(){
	// input
	int n; cin>>n;
	// int max = pow(2, ceil(log2(n+2))) -1;
	int tree[20], color[20];
	for(int i=0; i<20; i++){
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

	// O(1) rotation
	singleRotation(tree, color, (position-1)/2);

	// output
	cout<<"20"<<endl;
	for(int i=0; i<20; i++){
		cout<<tree[i]<<" ";
	} cout<<endl;
	for(int i=0; i<20; i++){
		cout<<color[i]<< " ";
	}cout<<endl;
	
	return 0;
}