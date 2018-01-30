public class HuffmanBinaryTree {
	private listBinTreeNode root;
	//Node right;
	//Node left;

	public HuffmanBinaryTree(){
		root = null;
	}
	
	public HuffmanBinaryTree(listBinTreeNode t) {
		root = t;
	}
	
	public void constructHuffmanBinTree(HuffmanLinkedList LL){
		listBinTreeNode newHead = LL.head;
		listBinTreeNode first = null;
		listBinTreeNode second = null;
		String comb ="";
		int totalCount = 0;
		listBinTreeNode nNode = null;
		
		while(newHead.next.next != null){
			first =  newHead.next;
			second = newHead.next.next;
			comb = first.chStr + second.chStr;
			totalCount = first.prob + second.prob;

			nNode = new listBinTreeNode(comb , totalCount);
			nNode.left = first;
			nNode.right = second;
			LL.listInsert(LL.findSpot(nNode.prob), nNode);
			nNode.printNode();
			LL.printList();
			newHead = newHead.next.next;
		}
		root = nNode;
	}
	
	private static boolean isLeaf(listBinTreeNode t){
		boolean b = false;
		if(t.left == null && t.right == null) b = true;
		return b;
	}
	
	public void constructCharCode(){
		constructCharCode(root,"");
		//System.out.println();
	}
	private static void constructCharCode(listBinTreeNode t,String s){
		if(t!=null){
			t.code = s;
			constructCharCode(t.left,s+"0");
			if(isLeaf(t)){
				System.out.println(t.chStr +  ", code:" + t.code);
			}
			constructCharCode(t.right,s+"1");					
		}
		return;
	}
	
	public void preOrderTraveral(){
		preOrderTraveral(root);
	}
	private static void preOrderTraveral(listBinTreeNode t){
		if(t!=null){
			System.out.println(t.chStr + ",  prob:"+ t.prob);
			preOrderTraveral(t.left);
			preOrderTraveral(t.right);			
		}
		return;
	}
	
	public void inOrderTraveral(){
		inOrderTraveral(root);
	}
	private static void inOrderTraveral(listBinTreeNode t){
		if(t!=null){
			inOrderTraveral(t.left);
			System.out.println(t.chStr + ",  prob:"+ t.prob);
			inOrderTraveral(t.right);			
		}
		return;
	}
	
	public void postOrderTraveral(){
		postOrderTraveral(root);
	}
	private static void postOrderTraveral(listBinTreeNode t){
		if(t!=null){
			postOrderTraveral(t.left);
			postOrderTraveral(t.right);
			System.out.println(t.chStr + ",  prob:"+ t.prob);
		}
		return;
	}
}
