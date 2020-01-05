#include<iostream>
#include <math.h>
#include<omp.h>
using namespace std;

int main(){	
	int SIZE; cin>>SIZE;
	int arr[SIZE],next[SIZE];
	#pragma omp parallel for
	for(int i=0; i<SIZE; i++){
		cin>>arr[i];
		next[i] = i-1;
	}
	
	int k = (int)ceil(log2(SIZE));
	for(int j=1; j<= k;j++){
		#pragma omp parallel for
		for(int i=0; i<SIZE; i++){
			if(next[i] >= 0){
				arr[i]= arr[i] + arr[next[i]];
				next[i]= next[next[i]];
			}
		}
	}

	for(int i = 0; i < SIZE; i++){
		cout<<arr[i]<<" ";
	} cout<<endl;

	return 0;
}