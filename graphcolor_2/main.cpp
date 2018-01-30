#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class node{
public:
	int colorId;
	node *next;
public:
	node(int color){
		colorId = color;
		next = NULL;
	}
};

class graphColoring{
public:
	int **adjMatrix;
	node *usedColorTop;
	int newColor;
	int numNode;
	
	graphColoring(int size){
		numNode = size;
		newColor = 0;
		usedColorTop = new node(0);
		adjMatrix = new int*[numNode + 1];
		for(int i = 0; i < size + 1; i++){
			adjMatrix[i] = new int[numNode + 1];
			for(int j = 0; j < size +1; j++){
				adjMatrix[i][j] = 0;
			}
		}
	}
	~graphColoring(){
		node *walker = usedColorTop;
		while(walker != NULL){
			walker = walker->next;
			delete usedColorTop;
			usedColorTop = walker;
		}
		
		for(int i = 0; i < numNode + 1; i++){
			delete[] adjMatrix[i];
		}
		delete[] adjMatrix;
	}
	
	void loadMatrix(int n1, int n2){
		adjMatrix[n1][n2] = 1;
		adjMatrix[n2][n1] = 1;
	}
	
	void printMatrix(){
		for(int i = 1; i < numNode + 1; i++){
			for(int j = 1; j < numNode +1; j++){
				cout<<adjMatrix[i][j]<<"  ";			
			}
			cout<<endl;
		}
	}
	
	void pushUsedColor(int color){
		node *curr = usedColorTop;
		node *newcolor = new node(color);
		while(curr->next != NULL){
			curr = curr->next;
		}
		newcolor->next = curr->next;
		curr->next = newcolor;
	}
	
	int findUsedColor(int currNode){
		node *curr = usedColorTop;
		int color = 0;
		int used = 0;
		while(curr->next != NULL){
			curr = curr->next;
			color = curr->colorId;
			for(int i = 1;i < numNode + 1; i++){
				//color is used by abjacent node
				if(adjMatrix[currNode][i] == 1 && adjMatrix[i][i] == color){
					used++;
				}
			}
			//color is not used
			if(used == 0){
				return color;
			}
			used = 0;
		}
		//all colors in stack are used
		return 0;
	}
	
};

int main(int argc, char *argv[]) {
	//file checking ----------------------------------------------------
	if(argv[1]==NULL || argv[2]==NULL) {
		cout<<"no parameter, require 1 input file, 1 output file"<<endl;
		return 0;	
	}
	
    ifstream infile;
    infile.open(argv[1]);
    if(!infile.is_open()){
		cout<<"cant find file"<<endl;
		return 0;
	}
	infile.close();
	//end file checking--------------------------------------------------
		
	streambuf *console = cout.rdbuf();
	ofstream out1;
	out1.open(argv[2]);
	//set output to output file 1
	cout.rdbuf(out1.rdbuf());
	
	int n1 = 0;
	int n2 = 0;
	int currNode = 0;
	int currColor = 0;
	graphColoring *gc = NULL;
	infile.open(argv[1]);
   	// Step 0
   	infile >> n1;
	gc = new graphColoring(n1);
	while(infile >> n1){
		infile >> n2;
		gc->loadMatrix(n1,n2);
		cout << n1 << " " << n2 << endl;
	}
	infile.close();
	
	//step 3
	while(currNode < gc->numNode){
		//step 1
		currNode++;
		cout<<"current node:"<< currNode << endl;
		//step 2
		currColor = gc->findUsedColor(currNode);
		if(currColor > 0){
			gc->adjMatrix[currNode][currNode] = currColor;
		}
		else{
			gc->newColor++;
			gc->adjMatrix[currNode][currNode] = gc->newColor;
			gc->pushUsedColor(gc->newColor);
		}
		gc->printMatrix();
	}
	cout<<endl;
	cout<<"Number of colors used to color:" << gc->newColor<<endl;
	
	cout.rdbuf(console);
	cout<<"input: "<<argv[1]<<endl;
	cout<<"output1: "<<argv[2]<<endl;
	cout<<"done"<<endl;
	out1.close();
	delete gc;
	return 0;
}
