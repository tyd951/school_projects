public class PrimMST {
	int numNodes;
	int inWhichSet[];
	undirectedEdge edgeListHead;
	undirectedEdge MSTofG;
	int totalMSTCost;
	
	PrimMST(int num){
		numNodes = num;
		inWhichSet = new int[numNodes + 1];
		edgeListHead = new undirectedEdge();
		MSTofG = new undirectedEdge();
		totalMSTCost = 0;
		inWhichSet[1] = 1;
		for(int i = 2; i < numNodes + 1; i++){
			inWhichSet[i] = 2;
		}
	}
	
	void insertEdge(undirectedEdge newedge){
		undirectedEdge walker = edgeListHead;
		
		while(walker.next != null && walker.next.edgeCost < newedge.edgeCost){
			walker = walker.next;
		}
		
		newedge.next = walker.next;
		walker.next = newedge;
	}
	
	undirectedEdge removeEdge(undirectedEdge head){
		undirectedEdge walker = head;
		undirectedEdge r;

		while(walker.next != null && inWhichSet[walker.next.Ni] == inWhichSet[walker.next.Nj]){
			walker = walker.next;
		}
		if(walker.next == null){
			throw new NullPointerException("no vaild edge in the graph");
		}
		r = walker.next;
		walker.next = walker.next.next;
		return r;
	}
	
	void pushEdge(undirectedEdge newedge){
		undirectedEdge walker = MSTofG;
		
		while(walker.next != null){
			walker = walker.next;
		}
		
		newedge.next = walker.next;
		walker.next = newedge;
	}
	
	void move2SetA(int i){
		inWhichSet[i] = 1;
	}
	
	void printSet(){
		System.out.println("inWhichSet array:");
		for(int i = 1; i < numNodes + 1; i++){
			System.out.print(inWhichSet[i] + " ");
		}
		
		System.out.println();
	}
	
	void printList(undirectedEdge newedge){
		undirectedEdge walker = newedge;
		int counter = 0;
		
		System.out.print("listHead --> " );
		walker.printEdge();
		while(walker.next != null && counter++ < 10){
			walker = walker.next;
			System.out.print(" --> ");
			walker.printEdge();
		}
		
		System.out.println();
	}
	
	boolean isSetBEmpty(){
		boolean b = true;
		for(int i = 2; i < numNodes + 1; i++){
			if(inWhichSet[i] == 2){
				return false;
			}
		}
		return b;
	}
}
