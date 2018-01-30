import java.io.*;
import java.util.Scanner;

public class project91 {
	public static void main(String[] args) {
		Scanner scan = null;
		graphColoring gc = null;
		node curr = null;
		FileOutputStream fos1 =null;
		try {
			fos1 = new FileOutputStream(args[1]);
			System.setOut(new PrintStream(fos1));
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}
		int n1 = 0;
		int n2 = 0;
		//step 0 -- start
		try {
			scan = new Scanner(new File(args[0]));
			n1 = scan.nextInt();
			gc = new graphColoring(n1);
			while(scan.hasNextInt()){
				n1 = scan.nextInt();
				n2 = scan.nextInt();
				System.out.println(n1 + " " + n2);
				gc.loadMatrix(n1, n2);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} finally{
			if(scan != null) scan.close();	
		}
		System.out.println("initial adjacencyMatrix and nodelist:");
		gc.printMatrix();
		gc.constructNodeList();
		gc.printList();
		//step 0 -- end
		
		//step 5
		while(gc.uncolorNode != 0){
			//step 1
			System.out.println();
			System.out.println("trial " + gc.newColor);
			curr = gc.listHead.next;
			gc.newColor++;
			//step 2-3
			while(true){
				if(curr.color == 0 && gc.checkAdjacent(curr.nodeId, gc.newColor) == 0){
					System.out.print(curr.nodeId + " ");
					curr.color = gc.newColor;
					gc.adjMatrix[curr.nodeId][curr.nodeId] = gc.newColor;
					gc.uncolorNode--;
				}
				if(curr.next == null) break;
				curr = curr.next;
			}
			System.out.println("are colored with " + gc.newColor);
			//step 4
			gc.printMatrix();
		}
		
		//step 6
		System.out.println();
		System.out.println("number of colors used:" + gc.newColor);
		System.out.println("Final adjacentcyMatrix with the assign colors in the diagonal of the matrix");
		gc.printMatrix();
		gc.printList();
		
		//step 7
		try {
			fos1.close();
			System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out)));
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("Done");
	}

}
