#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
std::ofstream fout;

void graph(int* tree, int* color, int n){
	for(int i=0; i<n; i++){
		if(color[i]!= -1 && tree[i]!=-1){
			if((2*i + 1 < n) && (tree[(2*i + 1)]!= -1))
				fout<< tree[i] <<"--" << tree[(2*i + 1)] << ";"<<endl ;
			if((2*i + 2 < n) && (tree[(2*i + 2)]!= -1))
				fout<< tree[i] <<"--" << tree[(2*i + 2)] << ";"<<endl ;
		}
	}

	for(int i=0; i<n; i++){
		if(color[i] == 0)
			fout<< tree[i]<<"[color = black, style = filled, fontcolor = white]"<<endl;
		else if(color[i] == 1)
			fout<< tree[i]<<"[color = red, style = filled, fontcolor = white]"	<<endl;
	}
}

int main(){
	int max; cin>>max;
	int tree[max]; 
	for(int i=0; i<max; i++){
		cin>>tree[i];
	}

	int color[max] ;// = {0};
	for(int i=0; i<max; i++){
		cin>>color[i];
	}

	fout.open("graph.dot");
	fout<<"graph a{ ";
	graph(tree, color, max);
	fout<<"}";
	fout.close();

	system("dot graph.dot -Tpng -o picture1.png");
	

	return 0;
}