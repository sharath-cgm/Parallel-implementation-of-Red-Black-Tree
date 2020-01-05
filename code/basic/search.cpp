// input: n, tree;
//# searches, elements to be searched
// output: index of element if element is present
//			else index at which it needs to be placed
#include<iostream>
#include <omp.h>
using namespace std;

//CREW PRAM ALGORITHM
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

int main(){
	int N;
	cin>>N;
	int tree[N];
	
	for (int i = 0; i < N; ++i){
		cin>>tree[i];
	}

	int k;
	cin>>k;
	int query_block[k];
	for (int i = 0; i < k; ++i){
		cin>>query_block[i];
	}

	// parallel 
	double begin = omp_get_wtime();
	#pragma omp parallel for
	for (int i = 0; i < k; ++i){
		query_block[i] = search(query_block[i],N,tree);
	}
	double end = omp_get_wtime();
	double time=end-begin;
	cout<<"Search of 'k' elements:"<<endl<<"Time taken in parallel: "<<time<<endl;
	// output
	for(int i=0; i<k; i++){
		cout<<query_block[i]<<" ";
	} cout<<endl;

	return 0;
}