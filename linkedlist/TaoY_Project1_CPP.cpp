#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Node {
public:
	string data;
	Node *next;
	//constructor
	Node() {
		data = "dummy";
		next = NULL;
	}
	//constructor
	Node(string s){
		data = s;
		next = NULL;
	}
}; //class

class LinkedList {
private:
	Node *head;
	
public:
	//constructor
	LinkedList(){
		head = new Node();
	}
	//destructor
	~LinkedList(){
		Node *walker = head;
		while(walker != NULL){
			walker = walker->next;
			delete head;
			head = walker;
		}
	}
	
	bool isEmpty(){
		bool b =false;
		if(head->next == NULL){
			b = true;
		}
		return b;
	}
	
	void insert(string s) {
		Node *n = new Node(s);
		Node *walker = head;
		
		while(walker->next != NULL && s.compare(walker->next->data)>0) {
			//cout<<s.compare(walker->next->data)<<endl;
			walker = walker->next;
		}
		
		n->next = walker->next;
		walker->next = n;
	}
	
	void listDelete(string s){}
	
	string print() {
		string s = "";
		Node *walker =head;
		
		s = s + "listHead-> (" +walker->data + ",";
		while((walker = walker->next) != NULL) {
			s = s + walker->data + ")-> (" + walker->data + ",";
		}
		s = s + "Null)";
		
		return s;
	}
	
}; //class


int main(int argc, char *argv[]) {
	
	LinkedList *LL = new LinkedList();
	if(argv[1] == NULL || argv[2] == NULL){
		cout<< "Error : No parameters" << endl;
		return 0;
	}
	ifstream inFile(argv[1]);
	ofstream outFile(argv[2]);
	
	if(inFile == NULL || outFile == NULL ){
		cout<< "Error : Invaild parameter" << endl;
		return 0;
	}
	
	string s;
	while(inFile>>s){
		LL->insert(s);
		outFile<< LL->print()<<endl;
	}
	inFile.close();
	outFile.close();
	
	cout<<"Done!"<<endl;
	
	delete LL;
	return 0;
	/* Testing
	LL->insert("zxc");
	cout<< LL->print()<<endl;
	LL->insert("abc");
	cout<< LL->print()<<endl;
	LL->insert("abzxc");
	cout<< LL->print()<<endl;
	*/
//	LL->~LinkedList();

}
