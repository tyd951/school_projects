//input.txt o1.txt o2.txt o3.txt o4.txt o5.txt
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class listBinTreeNode {
public:
	string chStr;
	int prob;
	string code;
	listBinTreeNode *left;
	listBinTreeNode *right;
	listBinTreeNode *next;
	
	//constructor
	listBinTreeNode() {
		chStr = "dummy";
		prob = 0;
		code = "";
		next = NULL;
		left = NULL;
		right = NULL;
	}
	//constructor
	listBinTreeNode(string s, int i){
		chStr = s;
		prob = i;
		code = "";
		next = NULL;
		left = NULL;
		right = NULL;
	}
	
	void printNode(){
		cout<< "Node:" + chStr + ", Node's prob:" << prob;

		if(next != NULL) {
			cout<< ", Node->next:" + next->chStr;
		}else {
			cout<<", Node->next:null";
		}
		
		if(left != NULL) {
			cout<< ", Node->left:" + left->chStr;
		}else {
			cout<<", Node->left:null";
		}
		
		if(right != NULL) {
			cout<< ", Node->right:" + right->chStr;
		}else {
			cout<<", Node->right:null";
		}	
		cout<<endl;
	}
	
}; //class

class HuffmanLinkedList {

public:
	listBinTreeNode *head;
	
	HuffmanLinkedList(){
		head = new listBinTreeNode();
	}
	
	//destructor
	~HuffmanLinkedList(){
		listBinTreeNode *walker = head;
		while(walker != NULL){
			walker = walker->next;
			delete head;
			head = walker;
		}
	}
	
	void constructHuffmanLList(char* in){
		string s1 = "";
		int i1 = 0;
		listBinTreeNode *newNode = NULL;
		
		//open file
		ifstream inFile;
		inFile.open(in);

		string s;
		while(inFile>>s){
			s1 = s;
			if(inFile>>s){
				istringstream ( s ) >> i1;
			}
			newNode = new listBinTreeNode(s1,i1);
			newNode->printNode();
			listInsert((findSpot(newNode->prob)),newNode);
			printList();
		}
		inFile.close();
	}
	
	int findSpot(int prob) {
		int i=0;
		listBinTreeNode *walker = head;
		while(walker->next != NULL && (prob > walker->next->prob)) {
			walker = walker->next;
			i++;
		}
		return i;
	}
	
	void listInsert(int spot, listBinTreeNode *nNode) {
		listBinTreeNode *n = nNode;
		listBinTreeNode *walker = head;
		
		for(int i = 0; i < spot ; i++){
			walker = walker->next;
		}
		
		n->next = walker->next;
		walker->next = n;
	}
	
	bool isEmpty(){
		bool b = false;
		if(head->next == NULL) b = true;
		return b;	
	}
	
	void printList() {
		listBinTreeNode *walker =head;
		
		cout<< "listHead-->(" + walker->chStr + "," << walker->prob << ",";
		while((walker = walker->next) != NULL) {
			cout << walker->chStr + ")-->("+ walker->chStr + "," << walker->prob << ",";
		}
		cout << "Null)"<<endl;
	}
	
}; //class

class HuffmanBinaryTree{
	
public:
	listBinTreeNode *root;
	
	HuffmanBinaryTree(){
		root = NULL;		
	}
	
	HuffmanBinaryTree(listBinTreeNode *t){
		root = t;
	}

	void constructHuffmanBinTree(HuffmanLinkedList *LL){
		listBinTreeNode *newHead = LL->head;
		listBinTreeNode *first = NULL;
		listBinTreeNode *second = NULL;
		string comb ="";
		int totalCount = 0;
		listBinTreeNode *nNode = NULL;
		
		while(newHead->next->next != NULL){
			first =  newHead->next;
			second = newHead->next->next;
			comb = first->chStr + second->chStr;
			totalCount = first->prob + second->prob;

			nNode = new listBinTreeNode(comb , totalCount);
			nNode->left = first;
			nNode->right = second;
			LL->listInsert(LL->findSpot(nNode->prob), nNode);
			nNode->printNode();
			LL->printList();
			newHead = newHead->next->next;
		}
		root = nNode;
	}
	
	//tree is deleted by deleting Linked List
	~HuffmanBinaryTree(){
	}
	
	bool isLeaf(listBinTreeNode *t){
		bool b = false;
		if(t->left == NULL && t->right == NULL) b = true;
		return b;
	}
	
	void constructCharCode(){
		constructCharCode(root,"");
	}

	void preOrderTravesal(){
		cout<<"preOrderTravesal:"<<endl;
		preOrderTravesal(root);
	}
	
	void inOrderTravesal(){
		cout<<"inOrderTravesal:"<<endl;
		inOrderTravesal(root);
	}
	
	void postOrderTravesal(){
		cout<<"postOrderTravesal:"<<endl;
		postOrderTravesal(root);
	}
	/*
	void deleteTree(){
		if(root!=NULL){
			deleteTree(root);
		}
	}
	*/
	
private:
	
	void constructCharCode(listBinTreeNode *t,string s){
		if(t!=NULL){
			t->code = s;
			constructCharCode(t->left,s+"0");
			if(isLeaf(t)){
				cout<< t->chStr +  ", code:" + t->code <<endl;
			}
			constructCharCode(t->right,s+"1");					
		}
	}
	
	void inOrderTravesal(listBinTreeNode *t){
		if(t!=NULL){
			inOrderTravesal(t->left);
			cout<< t->chStr + ",  prob:"<< t->prob <<endl;
			inOrderTravesal(t->right);	
		}
		return;
	}
	
	void preOrderTravesal(listBinTreeNode *t){
		if(t!=NULL){
			cout<< t->chStr + ",  prob:"<< t->prob <<endl;
			preOrderTravesal(t->left);
			preOrderTravesal(t->right);			
		}
		return;
	}
	
	void postOrderTravesal(listBinTreeNode *t){
		if(t!=NULL){
			postOrderTravesal(t->left);
			postOrderTravesal(t->right);			
			cout<< t->chStr + ",  prob:"<< t->prob <<endl;
		}
		return;
	}
	/*
	void deleteTree(listBinTreeNode *t){
		if(t!=NULL){
			deleteTree(t->left);
			deleteTree(t->right);	
			delete(t);
		}
		return;
	}
	*/
};

int main(int argc, char *argv[]) {
	HuffmanLinkedList *LL = new HuffmanLinkedList();
	HuffmanBinaryTree *tree = new HuffmanBinaryTree();
	
	if(argv[1]==NULL) {
		cout<<"no parameter"<<endl;
		return 0;	
	}
	
	//open file and do check
	ifstream inFile;
	inFile.open(argv[1]);
	if(!inFile.is_open()){
		cout<<"cant find file"<<endl;
		return 0;
	}else {
		inFile.close();
	}
	
	//im going to do redirect for cout
	streambuf *console = cout.rdbuf();
	
	ofstream out1;
	out1.open(argv[2]);
	ofstream out2;
	out2.open(argv[3]);
	ofstream out3;
	out3.open(argv[4]);
	ofstream out4;
	out4.open(argv[5]);
	ofstream out5;
	out5.open(argv[6]);

	cout.rdbuf(out5.rdbuf());
	LL->constructHuffmanLList(argv[1]);
	tree->constructHuffmanBinTree(LL);
	
	cout.rdbuf(out1.rdbuf());
	tree->constructCharCode();
	
	cout.rdbuf(out2.rdbuf());
	tree->preOrderTravesal();
	
	cout.rdbuf(out3.rdbuf());
	tree->inOrderTravesal();
	
	cout.rdbuf(out4.rdbuf());
	tree->postOrderTravesal();
	
	cout.rdbuf(console);
	cout<<"done"<<endl;
	
	out1.close();
	out2.close();
	out3.close();
	out4.close();
	out5.close();
	
	//tree is deleted by deleting linked list
	delete LL;
	return 0;
}
