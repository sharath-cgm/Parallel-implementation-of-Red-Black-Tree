//Construction of balanced binary tree with
//colors represented as ranks
//parallelly
#include <iostream>
#include <fstream>
#include <math.h>
#include <omp.h>
using namespace std;
std::ofstream fout;

int minimum(int a, int b){
	if(a<b)
		return a;
	return b;
}
//outputs a graph which is then visualised using GRAPHVIZ
void graph(int* tree, int* color, int n){
	for(int i=0; i<n; i++){
		if((2*i + 1 < n) && (tree[(2*i + 1)]!= -1))
			fout<< tree[i] <<"--" << tree[(2*i + 1)] << ";"<<endl ;
		if((2*i + 2 < n) && (tree[(2*i + 2)]!= -1))
			fout<< tree[i] <<"--" << tree[(2*i + 2)] << ";"<<endl ;
	}

	for(int i=0; i<n; i++){
		if(color[i] == 0)
			fout<< tree[i]<<"[color = black, style = filled, fontcolor = white]"<<endl;
		else
			fout<< tree[i]<<"[color = red, style = filled, fontcolor = white]"	<<endl;
	}
}

int main(){
	//Algortihm
	//According to Heejin Park. and Kunso Park. research paper
	int n; cin>>n;
	int array[n];

	for(int i=0; i<n; i++){
		array[i] = i+1;
	}
	int N[n+2], P[n+2], logValues[n+2];
	// #pragma omp parallel for
	for (int i = 0; i <= n+1; ++i){
		N[i]= pow(2,(int)floor(log2(n)));
		P[i]= (i!=0) ? pow(2,(int)floor(log2(i))) : 0;
		logValues[i] = (i!=0) ? ceil(log2(i)) : 0;
	}

	// step 1
	int max = pow(2, (int)(ceil(log2(n+1)))) - 1; // need to be made parallel
	int tree[max]; 
	int color[max]; // 0 - black, 1 - red
	for(int i=0; i<max; i++){ tree[i] = -1; color[i] = -1;}
	int D[n], J[n], CI[n], CL[n], I[n];
	int constant = pow(2, (int)(floor(log2(n+1))));// log(n) --->> O(1)
	int L = n+1 - constant;
	int rank[max]={0};

	bool perfectTree = (max == n) ? 1 : 0; 
	double begin, end;

	//Paralllel construction part
	begin = omp_get_wtime();
	if(perfectTree){
		constant = constant/2;
		#pragma omp parallel for
		for(int i=0; i<n; i++){
			D[i] = (int)(floor(log2(i+1)));
			J[i] = i+1 - pow(2, D[i]);
			CI[i] = (2*J[i] + 1)* constant /(int)pow(2,D[i]) - 1;
			// int temp = (2*J[i] + 1)* max /pow(2,D[i]);

			tree[i] = array[CI[i]];
			color[i] = 0;

			rank[i] = N[i] - logValues[i+2];
		}
	}
	else{ // not a perfect tree
		#pragma omp parallel for 
		for(int i=0; i<n; i++){
			D[i] = (int)(floor(log2(i+1)));
			J[i] = i+1 - pow(2, D[i]);
			CI[i] = (2*J[i] + 1)* constant /(int)pow(2,D[i]);
			CL[i] = CI[i]/2;
			I[i] = minimum(CI[i], CI[i] - CL[i] + L) - 1;

			tree[i] = array[I[i]];
			if(2*i +1 >= max)
				color[i] = 1;
			else 
				color[i] = 0;
			rank[i] = N[i] - logValues[i+2] -1;
		}
	}
	end = omp_get_wtime();
	double time = end-begin;
	cout<<"Construction in Parallel:"<<endl<<"Time taken: "<<time<<endl;


	// to display a graph,writing the data in a .dot file
	fout.open("graph.dot");
	fout<<"graph a{ ";
	graph(tree, color, n);
	fout<<"}";
	fout.close();

	system("dot graph.dot -Tpng -o picture1.png");

	// cout<<endl;
	//constructed tree to be written in a .txt file
	//for further use in search,insertion
	// for(int i=0; i<max; i++){
	// 	cout<<tree[i]<<" ";	
	// }cout<<endl;
	// for(int i=0; i<n; i++){
	// 	cout<<color[i]<<" ";	
	// }cout<<endl;

	return 0;
}