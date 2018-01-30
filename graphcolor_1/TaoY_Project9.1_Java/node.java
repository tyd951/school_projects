public class node {
	int nodeId;
	int color = 0;
	int numEdge = 0;
	node next = null;
	
	public node(){
		nodeId = 0;
	}
	public node(int i, int num){
		nodeId = i;
		numEdge = num;
	}
	
	public void printNode(){
		System.out.print(nodeId + ":" + numEdge + ":" + color);
	}
}
