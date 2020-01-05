#include<iostream>
#include<math.h>
#include<omp.h>
// #define SIZE 10
using namespace std;

void fillar(int SIZE,int A[]){
	for (int i = 0; i < SIZE; ++i)
	{
		A[i]=i+1;
	}
}
void intotree(int low,int hi,int index,int A[],int tree[],int color[])
{	
	int middle=(low+hi)/2;
	if((hi-low)>0)
	{	
		tree[index]=A[middle];
		intotree(low,middle-1,2*index+1,A,tree,color);
		intotree(middle+1,hi,2*index+2,A,tree,color);
		// cout<<"root: "<<A[middle]<<endl;
	}
	else if(hi==low)
	{
		tree[index]=A[middle];
	}
		else{
			if(index > N || (2*index+1) > N ){
		//red node at end
		color[index]=1;
	}
		}
	
}
int main(){
	int SIZE; cin>>SIZE;
	int A[SIZE];
	int N=(int)(pow(2,((ceil(log2(SIZE+1))))))-1;
	int tree[N];
	int color[N];

	double begin,end;
	for (int i = 0; i < N; ++i)
	{
		tree[i]=-1;
		//black node initially
		color[i]=0;
	}
	cout<<N<<endl;
	fillar(SIZE,A);
	begin = omp_get_wtime();
	intotree(0,SIZE-1,0,A,tree,color);
	end =  omp_get_wtime();
	cout<<"Sequential Construction:"<<endl<<"Time taken: "<<(end-begin)<<endl;
	return 0;
}