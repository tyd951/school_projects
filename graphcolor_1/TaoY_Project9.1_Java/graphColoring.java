public class graphColoring {
	int adjMatrix[][];
	node listHead;
	int uncolorNode;
	int newColor;
	int numNode;
	
	public graphColoring(int size){
		numNode = size;
		uncolorNode = size;
		newColor = 0;
		adjMatrix = new int[size + 1][size + 1];
		listHead = new node();
		
		for(int i = 0; i < size + 1; i++){
			for(int j = 0; j < size + 1; j++){
				adjMatrix[i][j] = 0;
			}
		}
	}
	
	public void loadMatrix(int n1, int n2){
		adjMatrix[n1][n2] = 1;
		adjMatrix[n2][n1] = 1;
	}
	
	public void printMatrix(){
		for(int i = 1; i < numNode + 1; i++){
			for(int j = 1; j < numNode + 1; j++){
				System.out.print(adjMatrix[i][j] + "  ");
			}
			System.out.println();
		}
	}
	
	public void insertOneNode(node listh , node n){
		node curr = listh;
		while(curr.next != null && n.numEdge > curr.next.numEdge){
			curr = curr.next;
		}
		n.next = curr.next;
		curr.next = n;
	}
	
	public void constructNodeList(){
		int edgecount = 0;
		for(int i = 1; i < numNode + 1; i++){
			for(int j = 1; j < numNode + 1; j++){
				if(i != j){
					edgecount += adjMatrix[i][j];
				}
			}
			insertOneNode(listHead, new node(i,edgecount));
			edgecount = 0;
		}
	}
	
	public void printList(){
		node curr = listHead;
		while(curr.next != null){
			curr.printNode();
			curr = curr.next;
			System.out.print("-->");
		}
		System.out.println("endlist");
	}
	
	public int checkAdjacent(int nodeId, int color){
		int num = 0;
		for(int i = 1; i < numNode + 1; i++){
			//there is a edge between nodeid and i, and the color of i equal color
			if(adjMatrix[nodeId][i] == 1 && adjMatrix[i][i] == color){
				num++;
			}
		}
		return num;
	}
}
