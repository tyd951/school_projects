#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class DijktraSSS{
	int numNodes;
	int sourceNode;
	int minNode;
	int currentNode;
	int newCost;
	int **costMatrix;
	int *fatherAry;
	int *toDoAry;
	int *bestCostAry;
	int count=0;
	
public:	

	~DijktraSSS(){
		delete[] costMatrix;
		delete[] fatherAry;
		delete[] toDoAry;
		delete[] bestCostAry;
	}
	void loadCostMatrix(string in){
		ifstream infile;
    	infile.open(in);
    	
		//load # of node and source node
		infile >> numNodes;
		infile >> sourceNode;
		
		//initialize arrays
		fatherAry = new int[numNodes + 1];
		toDoAry = new int[numNodes + 1];
		bestCostAry = new int[numNodes + 1];
		costMatrix = new int*[numNodes+1];
		
		for(int i = 0; i < numNodes + 1; i++){	
			fatherAry[i] = i;
			toDoAry[i] = 1;
			bestCostAry[i] = 99999;
			costMatrix[i] = new int[numNodes+1];
			for(int j = 0; j < numNodes + 1; j++){
				costMatrix[i][j] = 99999;
			}
			costMatrix[i][i] = 0;
		}
		
		//load date to costmatrix
		int start = 0;
		int end = 0;
		int distance = 0;
		while(infile >> start) {
			infile >> end;
			infile >>distance;
			costMatrix[start][end] = distance;
		}
		infile.close();
		
		cout<<"costMatrix:"<<endl;
		for(int i = 1; i < numNodes + 1; i++){	
			for(int j = 1; j < numNodes + 1; j++){
				cout<<costMatrix[i][j]<<"     ";
			}
			cout<<endl;
		}
	}
	
	void setBestCostAry(){
		for(int i = 1; i < numNodes + 1; i++){
			bestCostAry[i] = costMatrix[sourceNode][i];
		}
	}
	
	void setToDoAry(){
		toDoAry[sourceNode] = 0;
	}
	
	void setFatherAry(){
		for(int i = 1; i < numNodes + 1; i++){
			fatherAry[i] = sourceNode;
		}
	}
	
	void findMinNode(){
		int min = 99999;
		for(int i = 1; i < numNodes + 1; i++){
			if(toDoAry[i] == 1 && bestCostAry[i] < min){
				minNode = i;
				min = bestCostAry[i];
			}
		}
	}
	
	bool isAllZero(){
		for(int i = 1; i< numNodes + 1; i++){
			if(toDoAry[i] == 1){
				return false;
			}
		}
		return true;
	}
	
	void computeCost(){
		newCost = bestCostAry[minNode] + costMatrix[minNode][currentNode];
	}
	
	void markMinNode(){
		toDoAry[minNode] = 0;
	}
	
	void changeFather(){
		fatherAry[currentNode] = minNode;
	}
	
	void changeCost(){
		bestCostAry[currentNode] = newCost;
	}
	
	void Dijkstras(){
		for(currentNode = 1; currentNode< numNodes + 1; currentNode++){
			if(toDoAry[currentNode] == 1){
				computeCost();
				if(newCost < bestCostAry[currentNode]){
					changeCost();
					changeFather();
					debugPrint();
				}
			}
		}
	}
	
	void printShortestPath(){
		int temp = 0;
		cout<<"===================================="<<endl;
		cout<<"There are "<<numNodes<<" nodes in the input graph."<<endl;
		cout<<"===================================="<<endl;
		cout<<"Source node = "<<sourceNode<<endl;
		cout<<"The shortest paths from the source node "<<sourceNode<<" are:"<<endl;
		for(currentNode = 1; currentNode< numNodes + 1; currentNode++){
			cout<<"The path from "<<sourceNode<<" to "<<currentNode<<" : "<<currentNode;
			temp = fatherAry[currentNode];
			while(temp != sourceNode){
				cout<<" <-- "<<temp;
				temp = fatherAry[temp];
			}
			cout<<"<--"<<temp<<"  Cost: "<< bestCostAry[currentNode]<<endl;
		}
	}
	
	void debugPrint(){
		cout<<"===================================="<<endl;
		cout<<"loop "<<count<<": "<<endl;
		cout<<"the sourceNode is: "<<sourceNode<<endl;
		
		cout<<"fatherAry: ";
		for(int i = 1; i < numNodes + 1; i++){
			cout<<fatherAry[i]<<" ";
		}
		cout<<endl;
		
		cout<<"bestCostAry: ";
		for(int i = 1; i < numNodes + 1; i++){
			cout<<bestCostAry[i]<<" ";
		}
		cout<<endl;
		
		cout<<"toDoAry: ";
		for(int i = 1; i < numNodes + 1; i++){
			cout<<toDoAry[i]<<" ";
		}
		cout<<endl;
		count++;
	}
};

int main(int argc, char *argv[]) {
	if(argv[1]==NULL || argv[2]==NULL || argv[3]==NULL) {
		cout<<"no parameter, require 1 input file, 2 output file"<<endl;
		return 0;	
	}
	
    ifstream infile;
    infile.open(argv[1]);
    if(!infile.is_open()){
		cout<<"cant find file"<<endl;
		return 0;
	}
	infile.close();
	
	streambuf *console = cout.rdbuf();
	
	ofstream out1;
	out1.open(argv[2]);
	ofstream out2;
	out2.open(argv[3]);
	
	//set output to outfile 1
	cout.rdbuf(out2.rdbuf());
	
    string inputFile = argv[1];
    DijktraSSS *sss = new DijktraSSS();
    
    //step 0,1
    sss->loadCostMatrix(inputFile);
    //sss->debugPrint();
    
    //step 2
    sss->setBestCostAry();
    sss->setFatherAry();
    sss->setToDoAry();
    
    while(!sss->isAllZero()){
    	//step 3
    	sss->findMinNode();
    	sss->markMinNode();
    	sss->debugPrint();
    	//step 4,5,6,7
    	sss->Dijkstras();
    }
    
    //output to output1
    cout.rdbuf(out1.rdbuf());
    
    //step 9,10,11,12
    sss->printShortestPath();
    
    //step 13 close all files, delete objects
	cout.rdbuf(console);
	cout<<"input: "<<argv[1]<<endl;
	cout<<"output1: "<<argv[2]<<endl;
	cout<<"output2: "<<argv[3]<<endl;
	cout<<"done"<<endl;
	out1.close();
	out2.close();
	delete sss;
    return 0;
}
