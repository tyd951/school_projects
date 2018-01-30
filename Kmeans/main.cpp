#include <iostream>
#include <fstream>
#include <string>
#include <cmath> 
using namespace std;

class Point{
public:
	int X;
	int Y;
	int Label;
	double Distance;
	//constructors
	Point(int x, int y){
		this->X =x;
		this->Y =y;
		this->Label =0;
		this->Distance =0;
	}

	//destructor
	~Point(){}
	
	void PrintPoint(){
		cout<<"X:"<<X<<" Y:"<<Y<<" Label:"<<Label<<
			" Distance to its own cluster centroid:"<<Distance<<endl;
	}
	
	void setPoint(int x,int y){
		this->X = x;
		this->Y = y;
	}
	
	//destructor
	void deletePoint(){
		delete this;
	}
};

class Kmean{
	struct xyCoord{
        int K_X;
        int K_Y;
        int K_Label;
        //constructor
        xyCoord(int x,int y,int l){
        	K_X = x;
        	K_Y = y;
        	K_Label = l;
        }
    };
public:
	int K;
	xyCoord **Kcentroids;
	int K_numPts;
	Point **pointSet;
	int K_numRow;
	int K_numCol;
	int **imageArray;
	int changes;
	int counter;
	int print_trial;
	
	//constructor
	Kmean(int k,int numPts,int numRow,int numCol){
		K = k;
		K_numPts = numPts;
		K_numRow = numRow;
		K_numCol = numCol;
		
		Kcentroids = new xyCoord*[K];
		pointSet = new Point*[K_numPts];
		imageArray = new int*[K_numRow];	
		for(int i = 0; i < K_numRow; i++){
			imageArray[i] = new int[K_numCol];
			for(int j = 0; j < K_numCol; j++){
				imageArray[i][j] = 0;
			}
		}
		counter = 0;
		print_trial = 0;
	}
	
	//destructor
	~Kmean(){
		for(int i = 0; i < K; i++){
			delete Kcentroids[i];
		}
		delete[] Kcentroids;
		delete[] imageArray;
		for(int i = 0; i < K_numPts; i++){
			pointSet[i]->deletePoint();
		}
		delete[] pointSet;
	}
	
	void loadPointSet(int x, int y){
		pointSet[counter] = new Point(x,y);
		counter++;
	}
	
	void assignLable(){
		// assign label from 1 to k, for every point in set
		for(int i = 0; i < K_numPts; i++){
			pointSet[i]->Label = i%K+1;
		}
	}
	
	void mapPoint2Image(){
		int x;
		int y;
		int l;
		for(int i = 0; i < K_numPts; i++){
			x = pointSet[i]->X;
			y = pointSet[i]->Y;
			l = pointSet[i]->Label;
			imageArray[x][y] = l;
		}
	}
	
	void kMeanClustering(){
		changes = 0;
		int x1=0,y1=0,count1=0;
		int x2=0,y2=0,count2=0;
		int x3=0,y3=0,count3=0;
		int x4=0,y4=0,count4=0;
		
		//step 5 look for centroids
		for(int i = 0; i < K_numPts; i++){
			if(pointSet[i]->Label == 1){
				x1 += pointSet[i]->X;
				y1 += pointSet[i]->Y;
				count1++;
			}
			else if(pointSet[i]->Label == 2){
				x2 += pointSet[i]->X;
				y2 += pointSet[i]->Y;
				count2++;
			}
			else if(pointSet[i]->Label == 3){
				x3 += pointSet[i]->X;
				y3 += pointSet[i]->Y;
				count3++;
			}
			else {
				x4 += pointSet[i]->X;
				y4 += pointSet[i]->Y;
				count4++;
			}
		}
		//x1 == x2, y1 == y2 1st time, so i modified x1 by plus 1
		x1 = x1/count1 + 1;
		y1 = y1/count1;
		x2 = x2/count2;
		y2 = y2/count2;
		x3 = x3/count3;
		y3 = y3/count3;
		x4 = x4/count4;
		y4 = y4/count4;
		
		cout<<"centroid #1:"<<x1<<" "<<y1<<endl; 
		cout<<"centroid #2:"<<x2<<" "<<y2<<endl; 
		cout<<"centroid #3:"<<x3<<" "<<y3<<endl; 
		cout<<"centroid #4:"<<x4<<" "<<y4<<endl; 
		
		Kcentroids[0]= new xyCoord(x1,y1,1);
		Kcentroids[1]= new xyCoord(x2,y2,2);
		Kcentroids[2]= new xyCoord(x3,y3,3);
		Kcentroids[3]= new xyCoord(x4,y4,4);
		
		//step 6 ,7
		reLabel();	
	}
	
	void reLabel(){
		//step 7 repeat step 6 until all points in pointSet are processed.
		for(int i = 0; i < K_numPts; i++){
			minDistance(pointSet[i]);
		}
	}
	
	//step 6 if min_i's Label is not the same as p's Label change p's label to 
	void minDistance(Point *p){
		int dx;
		int dy;
		double min = 9999.9;
		int Label_temp = Kcentroids[0]->K_Label;
		double d;
		for(int i = 0; i < K; i++){
			//cout<<Kcentroids[i]->K_X<<" "<<Kcentroids[i]->K_Y<<" "<<Kcentroids[i]->K_Label<<endl;
			dx = pow((p->X - Kcentroids[i]->K_X),2);
  			dy = pow((p->Y - Kcentroids[i]->K_Y),2);
  			d = sqrt(dx + dy);
  			if(d < min){
  				min = d;
  				Label_temp = Kcentroids[i]->K_Label;
  			}
		}
		if(p->Label != Label_temp){
			p->Label = Label_temp;
			changes++;
		}
		p->Distance = min;
	}
	
	void printPointSet(){
		cout<<endl;
		cout<<"PrintPointSet:"<<endl;
		for(int i = 0; i < K_numPts; i++){
			pointSet[i]->PrintPoint();
		}
	}
	
	void PrettyPrint(){
		cout<<endl<<"Trails: "<<print_trial<<endl;
		for(int i = 0; i < K_numRow; i++){
			for(int j = 0; j < K_numCol; j++){
				if(imageArray[i][j] )
					cout<<imageArray[i][j];
				else
					cout<<" ";
			}
			cout<<endl;
		}
		cout<<"Trails: "<<print_trial<<" end here!"<<endl;
		cout<<endl;
		print_trial++;
	}
};

int main(int argc, char *argv[]){
	Kmean *myKmean;
	int k;
	int numPts;
	int r;
	int c;
	
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
	
	streambuf *console = cout.rdbuf();
	
	ofstream out1;
	out1.open(argv[2]);
	ofstream out2;
	out2.open(argv[3]);
	
	//set output to outfile 1
	cout.rdbuf(out1.rdbuf());
	
	//step 1.1 read first 3 line
	while(!inFile.eof()){
		inFile>>k;
		cout<<k<<endl;
		inFile>>numPts;
		cout<<numPts<<endl;
		inFile>>r;
		inFile>>c;
		cout<<r<<"  "<<c<<endl;
		break;
	}
	
	//paremeters: int k,int numPts,int numRow,int numCol
	myKmean = new Kmean(k,numPts,r,c);
	
	//step 1.2 read rest file
	while(inFile>>r){
		if(inFile>>c){
			cout<<r<<"  "<<c<<endl;
			myKmean->loadPointSet(r,c);
		}
	}
	inFile.close();
	
	//step 2 assignlable randomly
	myKmean->assignLable();
	
	cout.rdbuf(out2.rdbuf());

	do{
		//step 3 call mapPoint2Image 
		myKmean->mapPoint2Image();
		
		//step 4 call prettyprint
		myKmean->PrettyPrint();
		
		//step 5,6,7
		myKmean->kMeanClustering();

		//step 8 repeat step 3 to step 7 while changes > 0 
	} while(myKmean->changes > 0 );

	//step 9 Output the info of pointSet to Output-1 file.
	cout.rdbuf(out1.rdbuf());
	myKmean->printPointSet();
	
	//step 10 close all files, delete objects
	cout.rdbuf(console);
	cout<<"done"<<endl;
	
	out1.close();
	out2.close();
	delete myKmean;
}
