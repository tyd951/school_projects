import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class HuffmanLinkedList {
	listBinTreeNode head;
	
	public HuffmanLinkedList() {
		head = new listBinTreeNode("dummy",0);
	}
	
	public void constructHuffmanLList(String in,String out){
		listBinTreeNode newNode = null;
		Scanner sc = null;
		String s1 = "";
		int i1 = 0;
		
		try {
			sc = new Scanner(new File(in));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		while(sc.hasNext()) {
			s1 = sc.next();
			i1 = sc.nextInt();
			
			newNode = new listBinTreeNode(s1,i1);
			newNode.printNode();
			this.listInsert(this.findSpot(newNode.prob), newNode);
			this.printList();
		}
		
		sc.close();
	}

	public int findSpot(int prob){
		int i=0;
		listBinTreeNode walker = head;
		while(walker.next != null && (prob > walker.next.prob)) {
			//System.out.println(i + " " + walker.next.prob);
			walker = walker.next;
			i++;
		}
		return i;
	}
	
	public void listInsert(int spot, listBinTreeNode nNode){
		listBinTreeNode n = nNode;
		listBinTreeNode walker = head;
		
		for(int i = 0; i < spot ; i++){
			walker = walker.next;
		}
		
		n.next = walker.next;
		walker.next = n;
	}
	
	public boolean isEmpty(){
		boolean b = false;
		if(this.head.next == null) b= true;
		return b;
	}
	
	public void printList(){
		String s ="";
		
		listBinTreeNode walker = head;
		
		s += "listHead-->(" + walker.chStr + "," + walker.prob + ",";
		
		while((walker = walker.next) != null) {
			s += walker.chStr + ")-->("+ walker.chStr + "," + walker.prob + ",";
		}
		s += "Null)";
		
		System.out.println(s);
	}
}
