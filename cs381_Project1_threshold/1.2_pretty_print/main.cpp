#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
	//input check
	if(argv[1]==NULL) {
		cout<<"no parameter"<<endl;
		return 0;	
	}
	
	ifstream inFile;
	inFile.open(argv[1]);
	if(!inFile.is_open()){
		cout<<"cant find file"<<endl;
		return 0;
	}
	
	//remove extension
	string fileName = argv[1];
	string fileNameWithoutExtension = fileName.substr(0, fileName.rfind("."));
	string outfile = fileNameWithoutExtension + "_PP.txt";
	
	streambuf *console = cout.rdbuf();	
	ofstream out1;
	out1.open(outfile);
	
	//set output to outfile 1
	cout.rdbuf(out1.rdbuf());
	
	
	int numRows = 0;
	int numCols = 0;
	int minVal = 0;
	int maxVal = 0;
	
	int i = 0;
	inFile >> numRows;
	inFile >> numCols;
	inFile >> minVal;
	inFile >> maxVal;
	
	// step2 , 3
	cout << numRows << " " << numCols << " " << minVal << " " << maxVal <<endl;
	int counter = 0;
	while(inFile >> i){
		if(i > 0){
			cout << i << " ";
		}
		else{
			cout << "  ";
		}
		counter++;
		if(counter%numCols == 0){
			cout<<endl;
		}
	}
	//step 4
	inFile.close();
	
	cout.rdbuf(console);
	cout<<"done"<<endl;
	
	out1.close();
		
	return 0;
}
