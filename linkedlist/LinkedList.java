/**
 * 
 * @author Yida
 * @class LinkedList
 * 
 */
public class LinkedList {
	Node head;
	
	public LinkedList() {
		head = new Node();
	}
	
	/**
	 * @param s is String type
	 */
	public void insert(String s){
		Node n = new Node(s);
		Node walker = head;

		while(walker.next != null && s.compareTo(walker.next.data) > 0) {
			walker = walker.next;
		}

		n.next = walker.next;
		walker.next = n;

	}
	
	public String print(){
		String s ="";
		
		Node walker = head;
		
		//System.out.print(walker.data + ":");	
		s += walker.data + ":";
		
		while((walker = walker.next) != null) {
			//System.out.print(walker.data + "->"+ walker.data + ":");
			s += walker.data + "->"+ walker.data + ":";
			//walker = walker.next;
		}
		//System.out.println("Null");
		s += "Null";
		
		return s;
	}
}
