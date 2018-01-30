public class undirectedEdge {
	int Ni;
	int Nj;
	int edgeCost;
	undirectedEdge next;
	
	undirectedEdge(){
		Ni = 0;
		Nj = 0;
		edgeCost = 0;
	}
	
	undirectedEdge(int i, int j, int cost){
		Ni = i;
		Nj = j;
		edgeCost = cost;
		next = null;
	}
	
	void printEdge(){
		System.out.print("<" + Ni + "," + Nj + "," + edgeCost + ">");
	}
}
