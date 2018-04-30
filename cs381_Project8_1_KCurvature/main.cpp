#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

class boundaryPt{
public:
	int x;
	int y;
	double curvature;
	int localMax;
	int corner;
	
	boundaryPt(int xi, int yi){
		x = xi;
		y = yi;
		curvature = 0;
		localMax = 0;
		corner = 0;
	}
	
	void print(){
		cout<<"x:"<<x<<", y:"<<y<<", curvature:"<<curvature<<", corner:"<<corner<<endl;
	}
	
	void printCurv(){
		cout<<"x:"<<x<<", y:"<<y<<", curvature:"<<curvature<<endl;
	}
	
	void printCorner(){
		cout<<x<<" "<<y<<" "<<corner<<endl;
	}
};

class kCurvature{
public:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int label;
	
	int K;
	int countPts;
	int numPts;
	int beginIndex;
	
	boundaryPt **PtAry;
	
	kCurvature(int k, int num,string input){
		numRows = 0;
		numCols = 0;
		minVal = 0;
		maxVal = 0;
		label = 0;
		
		K = k;
		numPts = num;
		beginIndex = 0;

		PtAry = new boundaryPt*[numPts];
		
		ifstream inFile;
		inFile.open(input);
		inFile >> numRows;
		inFile >> numCols;
		inFile >> minVal;
		inFile >> maxVal;
		inFile >> label;
		int r = 0;
		int c = 0;
		while(inFile>>r){
			inFile>>c;
			storePt(r, c, beginIndex++);
		}
		inFile.close();
	}
	
	~kCurvature(){
		for(int i = 0; i < numPts; i++){
			delete PtAry[i];
		}
		delete[] PtAry;
	}
	
	void storePt(int x, int y, int index){
		PtAry[index] = new boundaryPt(x, y);
	}
	
	double computeCurvature(int q, int p, int r){
	
		double curv = 0;
		double slope1 = (PtAry[q]->y - PtAry[p]->y - 0.0) / (PtAry[q]->x - PtAry[p]->x + 0.01);
		double slope2 = (PtAry[p]->y - PtAry[r]->y - 0.0) / (PtAry[p]->x - PtAry[r]->x + 0.01);
		//cout<<"P:"<<p<<" slope 1:"<<slope1<<" slope 2:"<<slope2<<endl;	
		curv = slope1 - slope2;
	
		if(curv < 0) curv = 0 - curv;
		return curv;
	}
	
	void computeLocalMaxima(){
		int firstIndex = 0;
		int secondIndex = 0;
		int thirdIndex = 0;
		int forthIndex = 0;
		for(int i = 0; i < numPts; i++){
			firstIndex = (i+numPts-2)%numPts;
			secondIndex = (i+numPts-1)%numPts;
			thirdIndex = (i+1)%numPts;
			forthIndex = (i+2)%numPts;
			if(PtAry[i]->curvature >= PtAry[firstIndex]->curvature
				&& PtAry[i]->curvature >= PtAry[secondIndex]->curvature
				&& PtAry[i]->curvature >= PtAry[thirdIndex]->curvature 
				&& PtAry[i]->curvature >= PtAry[forthIndex]->curvature){
				PtAry[i]->localMax++;
			}
		}
	}
	
	void setCornor(){
		int firstIndex = 0;
		int forthIndex = 0;
		for(int i = 0; i < numPts; i++){
			firstIndex = (i + numPts - 2) % numPts;
			forthIndex = (i + 2) % numPts;
			
			if(PtAry[i]->localMax == 1 
			&& PtAry[firstIndex]->localMax == 0
			&& PtAry[forthIndex]->localMax == 0){
				PtAry[i]->corner = 8;
			}
			else{
				PtAry[i]->corner = 1;
			}
		}
	}
	
	void printPtAry(){
		for(int i = 0; i < numPts; i++){
			PtAry[i]->print();
		}
	}
	
	void printInfo(){
		cout<<"print the info (x, y, curvature) of the entire PtAry:"<<endl;
		for(int i = 0; i < numPts; i++){
			PtAry[i]->printCurv();
		}
	}
	
	void printCor(){
		cout<< numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
		cout<<label<<endl;
		cout<<numPts<<endl;
		for(int i = 0; i < numPts; i++){
			PtAry[i]->printCorner();
		}
	}
};

class image{
public:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int **imgAry;

	image(kCurvature *kc){
		numRows = kc->numRows;
		numCols = kc->numCols;
		minVal = kc->minVal;
		maxVal = kc->maxVal;
		
		imgAry = new int*[numRows];
		for(int i = 0; i < numRows; i++){
			imgAry[i] = new int[numCols];
			for(int j = 0; j < numCols; j++){
				imgAry[i][j] = 0;
			}
		}
		
		plotPt2Img(kc);

	}
	
	~image(){
		for(int i = 0; i < numRows; i++){
			delete imgAry[i];
		}
		delete[] imgAry;
	}
	
	void plotPt2Img(kCurvature *kc){
		for(int i = 0; i < kc->numPts; i++){
			imgAry[kc->PtAry[i]->x][kc->PtAry[i]->y] = kc->PtAry[i]->corner;
		}
	}
	
	void prettyPrint(){
		//cout<< numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
		for(int i = 0; i < numRows; i++){
			for(int j = 0; j < numCols; j++){
				if(imgAry[i][j] > 0){
					cout << imgAry[i][j] <<" ";
				}
				else{
					cout << "  ";
				}
			}
			cout << endl;
		}
	}
};

int main(int argc, char *argv[]){
	if(argv[1]==NULL) {
		cout<<"no parameter"<<endl;
		return 0;	
	}
	
	ofstream out1;
	out1.open(argv[2]);
	ofstream out2;
	out2.open(argv[3]);
	ofstream out3;
	out3.open(argv[4]);
	streambuf *console = cout.rdbuf();
	
	ifstream inFile;
	
	//step 0
	inFile.open(argv[1]);
	int index = 0;
	int temp = 0;
	int k = 0;
	//skip first 5 numbers
	inFile >> temp;
	inFile >> temp;
	inFile >> temp;
	inFile >> temp;
	inFile >> temp;
	while(inFile >> temp){
		inFile >> temp;
		index ++;
	}
	inFile.close();
	cout<<"Give me K value:"<<endl;
	cin>>k;
	
	//step 1,2,3
	kCurvature *kc = new kCurvature(k,index,argv[1]);
	cout.rdbuf(out3.rdbuf());
	kc->printPtAry();
	
	//step 4
	int Q = 0;
	int P = k;
	int R = 2*k;
	
	//step 5,6,7
	double curv = 0;
	do{	
	
		index = P;
		curv = kc->computeCurvature(Q,P,R);
		kc->PtAry[index]->curvature = curv;
		cout<<"Q:"<<Q<<", P:"<<P<<", R:"<<R<<", index:"<<index;
		cout<<", x:"<<kc->PtAry[index]->x<<", y:"<<kc->PtAry[index]->y;
		cout<<", curvature:"<<kc->PtAry[index]->curvature<<endl;
		Q = (Q + 1) % (kc->numPts);
		P = (P + 1) % (kc->numPts);
		R = (R + 1) % (kc->numPts);
	}while(P != k);
	
	//step 8
	kc->printInfo();
	
	//step 9
	kc->computeLocalMaxima();
	
	//step 10
	kc->setCornor();
	
	//step 11
	cout.rdbuf(out1.rdbuf());
	kc->printCor();
	
	//step 12,13
	image *i = new image(kc);
	
	//step 14
	cout.rdbuf(out2.rdbuf());
	i->prettyPrint();
	
	//step 15
	cout.rdbuf(console);
	cout<<"done"<<endl;
	delete kc;
	out1.close();
	out2.close();
	out3.close();
	return 0;
}
