#include<iostream>
using namespace std;
int search(int q,int N,int tree[]){
	int index=0;
	int result=-1;
	while(index<N){
		if(tree[index]==q){
			result=index;
			// cout<<"found";
			break;
		}
		else if(tree[index]>q){
			index=2*index+1;
		}
		else{
			index=2*index+2;
		}
	}
	return result;
}
int main()
{
	int a;
	int N;
	cin>>N;
	int tree[N];
	for (int i = 0; i < N; ++i)
	{
		cin>>tree[i];
	}
	cin>>a;
	int query[a];
	for(int i=0; i<a; i++){
		cin>>query[i];
	}

	clock_t begin = clock();
	for (int i = 0; i < a; ++i)
	{
		
		cout<<search(query[i],N,tree)<<endl;
	}
	clock_t end = clock();
	double time = (double)(end-begin)/CLOCKS_PER_SEC;
	
	return 0;
}