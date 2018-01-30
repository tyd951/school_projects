#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class HeapSort{
private:
	int *heapAry;
	const int rootIndex = 1;
	int fatherIndex;
	int leftKidIndex;
	int rightKidIndex;
	int minKidIndex;
	int maxSize;
	
	void bubbleUp(int i){
		if(isRoot(i)) return;
		fatherIndex = i/2;
		if(heapAry[i] < heapAry[fatherIndex]){
			swap(i,fatherIndex);
			bubbleUp(fatherIndex);
		}
		else return;
	}
	
	void bubbleDown(int i){
		//if no child, return
		if(isleaf(i)) return;
		leftKidIndex= 2*i;
		
		//only left child
		if(isOneChild(i)){
			if(heapAry[i] > heapAry[leftKidIndex]){
				swap(i,leftKidIndex);

			}
			return; 
		}

		//2 children, swap with smaller one, call bubbledown again
		minKidIndex = findMinKidIndex(i);
		if(heapAry[i] > heapAry[minKidIndex]){
			swap(i,minKidIndex);
			bubbleDown(minKidIndex);
		}
		
		return;
	}
	
	//check isleaf
	bool isleaf(int i){
		bool b = false;
		leftKidIndex = 2*i;
		rightKidIndex = 2*i+1;
		if(leftKidIndex > maxSize || rightKidIndex > maxSize){
			b= true;
		}
		else if(heapAry[leftKidIndex] == -1 && heapAry[rightKidIndex] == -1){
			b = true;
		}
		return b;
	}
	
	//check only has left child
	bool isOneChild(int i){
		bool b = false;
		rightKidIndex = 2*i+1;
		if(heapAry[rightKidIndex] == -1){
			b = true;
		}
		return b;		
	}
	
	bool isRoot(int i){
		return i == 1;
	}
	
	//find the index has smaller kid
	int findMinKidIndex(int i){
		rightKidIndex = 2*i+1;
		leftKidIndex = 2*i;	
		int small;
		if(heapAry[leftKidIndex] >= heapAry[rightKidIndex]){
			small = rightKidIndex;
		}
		else small = leftKidIndex;
		return small;
	}
	
public:
	HeapSort(int size){
		heapAry = new int[size+1];
		
		//initallize array by filled with -1
		for(int i = 1; i<= size; i++){
			heapAry[i] = {-1};
		}
		
		heapAry[0]=0;
		maxSize = size;
	}
	
	~HeapSort(){
		delete[] heapAry;
	}
	
	//read ints and build heap
	void buildHeap(char* in){	
		ifstream inFile;
		inFile.open(in);
		
		int i;
		while(inFile>>i){
			cout<<i<<endl;
			insertOneDataItem(i);
		}
		inFile.close();
	}
	
	//heapsort by delete heap
	void deleteHeap(){
		cout<<"heapsort:";
		while(!isHeapEmpty()){
			//printHeap();
			cout<<" "<<deleteRoot();
		}
		cout<<endl;
	}
	
	//insert one data to first empty spot of array
	void insertOneDataItem(int i){
		if(isHeapFull()){
    		cout<<"this array is full, can not insert number!";
    		return;
    	}
		heapAry[0]++;
		heapAry[heapAry[0]] = i;
		bubbleUp(heapAry[0]);
		printHeap();
	}
	
	//delete root and print it 
	int deleteRoot(){
		int oldroot = heapAry[rootIndex];
		heapAry[rootIndex] = -1;
		swap(rootIndex,heapAry[0]);
		heapAry[0]--;
		bubbleDown(rootIndex);		
		return oldroot;
	}
	
	//print heap
	void printHeap(){
		for(int i =0; i < heapAry[0]; i++ ){
			cout<< heapAry[i]<<",";
		}
		cout<<heapAry[heapAry[0]]<<endl;
	}
	
	//swap two index
	void swap(int i1, int i2){
		int x = heapAry[i1];
		heapAry[i1] = heapAry[i2];
		heapAry[i2] = x;
	}
	
	bool isHeapEmpty(){
		bool b = false;
    	if(heapAry[0]==0){
    		b = true;
    	}  
		return b;
    }
    
    bool isHeapFull(){
    	bool b = false;
    	if(heapAry[0]>= maxSize){
    		b = true;
    	}
    	return b;
    }
};

int main(int argc, char *argv[]){
	HeapSort *myHeap;
	int count = 0;
	if(argv[1]==NULL) {
		cout<<"no parameter"<<endl;
		return 0;	
	}
	
	ifstream inFile;
	inFile.open(argv[1]);
	if(!inFile.is_open()){
		cout<<"cant find file"<<endl;
		return 0;
	}else {
		int i;
		while(inFile>>i){
			count++;
		}
		inFile.close();
	}
	//finish counting
			
	myHeap = new HeapSort(count);
	
	streambuf *console = cout.rdbuf();
	
	ofstream out1;
	out1.open(argv[2]);
	ofstream out2;
	out2.open(argv[3]);
	
	//set output to outfile 1
	cout.rdbuf(out1.rdbuf());		
	myHeap->buildHeap(argv[1]);
	
	//set output to outfile 2
	cout.rdbuf(out2.rdbuf());
	myHeap->deleteHeap();
	
	cout.rdbuf(console);
	cout<<"done"<<endl;
	
	out1.close();
	out2.close();
	
	delete myHeap;
}
