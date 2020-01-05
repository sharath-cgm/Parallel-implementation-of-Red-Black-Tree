#include<iostream>
#include <math.h>
#include <omp.h>
#include <unordered_map>
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

int main(){
	// input and initializations
	int N ;
	cin>>N;
	int tree[N];
	for (int i = 0; i < N; ++i){
		cin>>tree[i];
	}
	int k;
	cin>>k;
	int elementsInsert[k],positions[k];
	for (int i = 0; i < k; ++i){
		cin>>elementsInsert[i];
	}
	int fb[k]={0}, lb[k]={0};
	int max = (int)ceil(log2(k));

	// search
	#pragma omp parallel for
	for (int i = 0; i < k; ++i){
		positions[i] = search(elementsInsert[i],N,tree);
	}

	fb[0] = 1; lb[k-1] = 1;
	#pragma omp parallel for 
	for(int i=0; i<k; i++){
		if((i!=0) && (positions[i] != positions[i-1]))
			fb[i] = 1;
		if((i!=k-1) && positions[i]!=positions[i+1])
			lb[i] = 1;
	}

	// prefix sum
	int psl[k], psf[k], next[k];
	#pragma omp parallel for
	for(int i=0; i<k; i++){
		psl[i] = lb[i];
		psf[i] = fb[i];
		next[i] = i-1;
	}
	for(int j=1; j<=max ;j++){
		#pragma omp parallel for
		for(int i=0; i<k; i++){
			if(next[i] >= 0){
				psl[i]= psl[i] + psl[next[i]];
				psf[i]= psf[i] + psf[next[i]];
				next[i]= next[next[i]];
			}
		}
	}

	int blockCount = psl[k-1];
	int M[blockCount];
	unordered_map<int, int> block;

	#pragma omp parallel for 
	for(int i=0; i<k; i++){
		if(lb[i] == 1)
			M[psl[i]-1] = i;
	}

	#pragma omp parallel for 
	for(int i=0; i<k; i++){
		if(fb[i] == 1){
			// block[psf[i]-1][0] = i;
			// block[psf[i]-1][1] = M[psf[i]-1];
			block[i] = M[psf[i]-1];
		}
	}

	for(int i=0; i<k; i++){
		cout<<positions[i]<<" ";
	} cout<<endl;

	// when fb[i]=1, (i, M[psf[i]-1]) denotes the temp

	// step 3
	unordered_map<int, int> temp;
	temp = block;
	#pragma omp parallel for //default(none) shared(block)
	for(auto i=temp.begin(); i!=temp.end(); i++){
		// int c = (temp[i] + i)/2 + (temp[i] + i)%2 ;
		int c = (i->first + i->second)/2 + (i->first + i->second)%2 ;
		tree[positions[c]] = elementsInsert[c];
		if(i->second != i->first){
			#pragma omp parallel for 
			for(int j=0; j<(i->second - i->first +1); j++){
				if(j<c)
					positions[j] = 2*positions[j] + 1;
				else if(j>c)
					positions[j] = 2*positions[j] + 2;
			}
			int last = i->second;
			block[i->first] = c-1;
			block[c+1] = last;
		}
		else
			block.erase(i->first);
		positions[c] = -1; elementsInsert[c] = -1; // assigned


	// step 4 -> Rebalancing
		


	}

	// output
	// for(int i=0; i<k; i++){
	// 	cout<<positions[i]<<" ";
	// } cout<<endl;
	// for(int i=0; i<k; i++){
	// 	cout<<fb[i]<<" ";
	// } cout<<endl;
	// for(int i=0; i<k; i++){
	// 	cout<<lb[i]<<" ";
	// } cout<<endl;
	// for(int i=0; i<k; i++){
	// 	cout<<psl[i]<<" ";
	// } cout<<endl;
	// for(int i=0; i<k; i++){
	// 	cout<<psf[i]<<" ";
	// } cout<<endl<<endl;
	// for(int i=0; i<k; i++){
	// 	if(fb[i])
	// 		cout<<i<<" "<<M[psf[i]-1]<<endl;
	// }

	cout<<"map:"<<endl;
	for(auto i=block.begin(); i!=block.end(); i++){
		cout<<i->first<<" "<<i->second<<endl;
	}cout<<endl;

	return 0;
}