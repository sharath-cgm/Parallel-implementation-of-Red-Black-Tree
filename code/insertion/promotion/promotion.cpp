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

void promotion(int* tree, int* color, int insertion){
	int parentIndex = (insertion-1)/2;
	int uncleIndex = parentIndex+1;

	if((color[parentIndex] == 1) && (color[uncleIndex] == 1)){
		color[parentIndex] = 0;
		color[uncleIndex] = 0;
	}
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

	// search -> O(log(n))
	int query; cin>>query;
	int position = search(query,n,tree);
	tree[position] = query;
	color[position] = 1;

	promotion(tree, color, position);

	// output
	cout<<"20"<<endl;
	for(int i=0; i<20; i++){
		cout<<tree[i]<<" ";
	} cout<<endl;
	for(int i=0; i<20; i++){
		cout<<color[i]<< " ";
	}cout<<endl;
}