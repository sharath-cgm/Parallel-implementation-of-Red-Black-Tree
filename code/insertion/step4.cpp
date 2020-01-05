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
	int n; cin>>n;
	int tree[n];
	for (int i = 0; i < n; ++i){
		cin>>tree[i];
	}

	int rank[n];
	for(int i=0; i<n; i++){
		cin>>rank[i];
	}

	int k; cin>>k;
	int elementInsert[k], position[k];
	for(int i=0; i<k; i++){
		cin>>elementInsert[i];	
	}

	#pragma omp parallel for 
	for(int i=0; i<k; i++){
		position[i] = search(elementInsert[i],n,tree);
	}

	if(k == 1){
		tree[position[0]] = elementInsert[0];
		rank[position[0]] = 1;
		int parentIndex = (position[0] -1)/2;
		int grandparentIndex = (parentIndex - 1)/2;
		int uncleIndex = (parentIndex == grandparentIndex*2 + 1)? grandparentIndex*2 + 2 : grandparentIndex*2+1;

		cout<<parentIndex<<" "<<uncleIndex<<" "<<grandparentIndex<<endl;
		if(rank[parentIndex] == rank[uncleIndex])
			rank[(parentIndex-1)/2]+=1;
		else if(rank[uncleIndex] != rank[parentIndex]){ 
			if(position[0] == parentIndex*2 + 1){
				singleRotation(tree, n, parentIndex);
			}
			else if(position[0] == parentIndex*2 +2){
				doubleRotation(tree, n, position[0]);
			}
		}
	}

	for(int i=0; i<n; i++){
		cout<<tree[i]<<" ";
	} cout<<endl;

	return 0;
}