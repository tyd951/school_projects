#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void printAry(int charAry[],char* out){
	ofstream outFile(out);
	char c = 0;
	
	for(int i = 0; i < 256; i++){
		if(charAry[i]!=0){
			c=(char)i;
			outFile<<c<<"  # "<<charAry[i]<<endl;
		}
	}
	outFile.close();
	cout<<"Done writing!"<<endl;
}

int main(int argc, char *argv[]){
	char charIn = 0;
	int index;
	int charCounts [256] = {};
	
	if(argv[1] == NULL || argv[2] == NULL){
		cout<< "Error : Missing parameters" << endl;
		return 0;
	}
	
	ifstream inFile(argv[1]);
	/* cant compile with g++,works when compile in Dev c++
	if(inFile == NULL){
		cout<< "Error : Invaild parameter" << endl;
		return 0;
	}
	*/
	while(inFile>>charIn){
		index = (int)charIn;
		//cout<<index<<endl;
		charCounts[index]+=1;
	}
	inFile.close();
	
	printAry(charCounts,argv[2]);
	return 0;
}
