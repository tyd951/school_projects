import java.io.*;

public class project3 {
	public static void main(String[] args) {
		HuffmanLinkedList LL = new HuffmanLinkedList();
		HuffmanBinaryTree tree = new HuffmanBinaryTree();
		FileOutputStream fos = null;
		
		//constructHuffmanList
		//constructHuffmanTree
		try {
			fos = new FileOutputStream(args[5]);
			System.setOut(new PrintStream(fos));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		LL.constructHuffmanLList(args[0], args[5]);
		tree.constructHuffmanBinTree(LL);
		
		//Call constructCharCode () 
		try {
			fos = new FileOutputStream(args[1]);
			System.setOut(new PrintStream(fos));
			tree.constructCharCode();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		//Call preOrderTraveral ()
		try {
			fos = new FileOutputStream(args[2]);
			System.setOut(new PrintStream(fos));
			tree.preOrderTraveral();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		//Call inOrderTraversal ()
		try {
			fos = new FileOutputStream(args[3]);
			System.setOut(new PrintStream(fos));
			tree.inOrderTraveral();;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		//Call postOrderTraveral ()
		try {
			fos = new FileOutputStream(args[4]);
			System.setOut(new PrintStream(fos));
			tree.postOrderTraveral();;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		//finish up
		try {
			fos.close();
			System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out)));
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		System.out.println("Done");
		
	}
}