#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char *argv[]){
	//input check
	if(argv[1]==NULL) {
		cout<<"no parameter"<<endl;
		return 0;	
	}
	//step 0
	ifstream inFile;
	inFile.open(argv[1]);
	if(!inFile.is_open()){
		cout<<"cant find file"<<endl;
		return 0;
	}
	
	//step 1
	int numRows = 0;
	int numCols = 0;
	int minVal = 0;
	int maxVal = 0;
	
	inFile >> numRows;
	inFile >> numCols;
	inFile >> minVal;
	inFile >> maxVal;
	
	//step 2
	int thrValue = 0;
	cout<<"Give me a threshold value:"<<endl;
	cin>>thrValue;
	//check input is vaild value
	while(cin.fail()){
		cout<<"Threshold value must be integer type, Give me a threshold value:"<<endl;
		cin.clear();
		cin.ignore(256,'\n');
		cin>>thrValue;
	}
		
	//step 3. generate output file name	
	//remove extension
	string fileName = argv[1];
	string fileNameWithoutExtension = fileName.substr(0, fileName.rfind("."));

	string outfile = fileNameWithoutExtension + "_thr_";
	stringstream ss;
	ss<<outfile<<thrValue;
	outfile = ss.str();
	outfile = outfile + ".txt";
	
	//step 4
	streambuf *console = cout.rdbuf();
	ofstream out1;
	out1.open(outfile);
	//set output to outfile 1
	cout.rdbuf(out1.rdbuf());
	
	//step 5
	cout << numRows << " " << numCols << " " << 0 << " " << 1 <<endl;
	
	//step 6 & step 7
	int pVal = 0;
	int counter = 0;
	while(inFile >> pVal){
		if(pVal >= thrValue){
			cout << 1 << " ";
		}
		else{
			cout << 0 << " ";
		}
		counter++;
		if(counter%numCols == 0){
			cout<<endl;
		}
	}
	
	//step 8
	inFile.close();
	cout.rdbuf(console);
	cout<<"done"<<endl;
	
	out1.close();
	return 0;
}
