public class listBinTreeNode {
	String chStr;
	int prob;
	String code;
	listBinTreeNode left;
	listBinTreeNode right;
	listBinTreeNode next;
	
	public listBinTreeNode(){
		chStr = "";
		prob = 0;
		code = "";
		left = null;
		right = null;
		next = null;
	}
	
	public listBinTreeNode(String s, int i){
		chStr = s;
		prob = i;
		code = "";
		left = null;
		right = null;
		next = null;
	}
	
	public void printNode(){
		String s = "";
		if(this.chStr != null) s += "Node:" + this.chStr + ", Node's prob:" + this.prob;
		else
			s+= "Node:Null" + ", Node's prob:" + this.prob;
		
		if(this.next != null) s += ", Node.next:" + this.next.chStr;
		else
			s += ", Node.next:null";
		
		if(this.left != null) s += ", Node.left:" + this.left.chStr;
		else 
			s += ", Node.left:null";
		
		if(this.right != null) s += ", Node.right:" + this.right.chStr;
		else
			s += ", Node.right:null";
		
		System.out.println(s);
	}
}
