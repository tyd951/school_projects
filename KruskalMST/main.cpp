#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class graphNode{
public:
	int nodeID;
	graphNode *next;
	
	graphNode(int i){
		nodeID = i;
		next = NULL;
	}
	~graphNode(){
		delete this;
	}
};

class undirectedEdge{	
public:
	int Ni;
	int Nj;
	int edgeCost;
	undirectedEdge *next;
	
	undirectedEdge(){
		Ni = 0;
		Nj = 0;
		edgeCost = 0;
		next = NULL;
	}
	undirectedEdge(int i, int j, int c){
		Ni = i;
		Nj = j;
		edgeCost = c;
		next = NULL;
	}
	
	void printEdge(){
		cout<< "<" << Ni << "," << Nj << "," << edgeCost <<">";
	}
};

class KruskalMST{
public:
	int numNodes;
	int *inWhichSet;
	int numSets;
	int totalMSTCost;
	undirectedEdge *MSTofG;
	undirectedEdge *edgeListHead;
	
	KruskalMST(int num){
		numNodes = num;
		inWhichSet = new int[numNodes + 1];
		numSets = numNodes;
		totalMSTCost = 0;
		MSTofG = new undirectedEdge();
		edgeListHead = new undirectedEdge();
		for(int i = 0; i < numNodes + 1; i++){
			inWhichSet[i] = i;
		}
	}
	
	~KruskalMST(){
		undirectedEdge *walker = edgeListHead;
		while(walker != NULL){
			walker = walker->next;
			delete edgeListHead;
			edgeListHead = walker;
		}
		
		walker = MSTofG;
		while(walker != NULL){
			walker = walker->next;
			delete MSTofG;
			MSTofG = walker;
		}
		
		delete[] inWhichSet;
	}
	
	void printList(undirectedEdge *head){
		undirectedEdge *temp = head;
		int counter = 0;
		
		temp->printEdge();
		while(temp->next != NULL && counter < 10){
			temp = temp->next;
			cout<<" --> ";
			temp->printEdge();
			counter++;
		}
		cout<<endl;
		cout<<endl;
	}
	
	void printSet(){
		cout<<"inWhichSet array: "<<endl;
		for(int i = 1; i < numNodes + 1; i++){
			cout<<i<<" is in : group "<< inWhichSet[i]<<endl;
		}
		cout<<endl;
	}
	
	void insertEdge(undirectedEdge *newEdge){
		undirectedEdge *walker = edgeListHead;
		
		while(walker->next != NULL && walker->next->edgeCost < newEdge->edgeCost) {
			walker = walker->next;
		}
		
		newEdge->next = walker->next;
		walker->next = newEdge;
	}
	
	undirectedEdge* removeEdge(){
		undirectedEdge *walker = edgeListHead;
		if(walker->next == NULL){
			throw ("list is empty");
		}
		walker = walker->next;
		edgeListHead->next = walker->next;
		
		return walker;
	}
	
	void pushEdge(undirectedEdge *edge){
		undirectedEdge *walker = MSTofG;
		
		while(walker->next != NULL) {
			walker = walker->next;
		}
		
		edge->next = walker->next;
		walker->next = edge;
	}
	
	void merge2Sets(int i, int j){
		if(inWhichSet[i] < inWhichSet[j]){
			int temp = inWhichSet[j];
			for(int k = 1; k < numNodes + 1; k++){
				if(inWhichSet[k] == temp){
					inWhichSet[k] = inWhichSet[i];
				}
			}
		}
		else{
			int temp = inWhichSet[i];
			for(int k = 1; k < numNodes + 1; k++){
				if(inWhichSet[k] == temp){
					inWhichSet[k] = inWhichSet[j];
				}
			}
		}
	}
	
	
};

int main(int argc, char *argv[]) {
	//file checking ----------------------------------------------------
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
	
	//end file checking--------------------------------------------------
	
	//set output to output file 1
	cout.rdbuf(out1.rdbuf());
	
	KruskalMST *kmst = NULL;
	undirectedEdge *edge = NULL;
	int i = 0;
	int j = 0;
	int c = 0;
	
   	infile.open(argv[1]);
   	// Step 0
   	infile >> i;
   	cout << "*** A Kruskal's MST of the input graph is given below: ***"<<endl;
   	cout << i <<endl;
   	kmst = new KruskalMST(i);
   	
   	//debug
   	cout.rdbuf(out2.rdbuf());
   	//kmst->printList();
   	kmst->printSet();
   	
   	//Step 1,2,3
   	while(infile >> i) {
   		cout.rdbuf(out1.rdbuf());
		infile >> j;
		infile >>c;
		cout << i <<" "<< j <<" "<< c <<endl;
		cout.rdbuf(out2.rdbuf());
		edge = new undirectedEdge(i,j,c);
		kmst->insertEdge(edge);
		cout<<"edgeListHead --> ";
		kmst->printList(kmst->edgeListHead);
	}
	infile.close();
	cout<<endl;
	
	//Step 4,5,6,7,8
	while(kmst->numSets != 1){
		//step 4,5
		do{
			edge = kmst->removeEdge();
		}while(kmst->inWhichSet[edge->Ni] == kmst->inWhichSet[edge->Nj]);
		
		//step 6
		
		kmst->pushEdge(edge);
		kmst->totalMSTCost += edge->edgeCost;
		kmst->merge2Sets(edge->Ni, edge->Nj);
		kmst->numSets --;
		cout<<"------------------------------------------------------"<<endl;
		cout<<"numset:" <<kmst->numSets<<endl;
		kmst->printSet();
		
		//step 7
		cout<<"MSTofG --> ";
		kmst->printList(kmst->MSTofG);
		cout<<"edgeListHead --> ";
		kmst->printList(kmst->edgeListHead);
	}
	
	
	//step 9
	
	cout.rdbuf(out1.rdbuf());
	cout<<endl;
	cout<<"Final MSTofG:"<<endl;
	kmst->printList(kmst->MSTofG);
	cout<<"*** The total cost of  a Kruskal's MST is: "<<kmst->totalMSTCost<<endl;
	
	
   	//step 10
	cout.rdbuf(console);
	cout<<"input: "<<argv[1]<<endl;
	cout<<"output1: "<<argv[2]<<endl;
	cout<<"output2: "<<argv[3]<<endl;
	cout<<"done"<<endl;
	out1.close();
	out2.close();
	delete edge;
	delete kmst;
    return 0;
}

