import java.io.File;
import java.io.FileDescriptor;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Scanner;

public class project7b {
	
	public static void main(String[] args) throws FileNotFoundException {
		
		FileOutputStream fos1 = new FileOutputStream(args[1]);
		FileOutputStream fos2 = new FileOutputStream(args[2]);
		Scanner scan = null;
		PrimMST pmst = null;
		undirectedEdge newedge = null;
		
		int x = 0;
		int y = 0;
		int c = 0;
		int counter = 0;
		
		//output to output1
		System.setOut(new PrintStream(fos1));
		
		try {
			scan = new Scanner(new File(args[0]));
			
			//step 0
			x = scan.nextInt();
			pmst = new PrimMST(x);
			System.out.println("*** The Prim¡¯s MST of the input graph is given below: ***");
			System.out.println(x);
			
			//output to output2
			System.setOut(new PrintStream(fos2));
			pmst.printList(pmst.edgeListHead);
			
			//step 1,2,3
			while(scan.hasNextInt()){
				//output to output1
				System.setOut(new PrintStream(fos1));
				x = scan.nextInt();
				y = scan.nextInt();
				c = scan.nextInt();
				System.out.println(x + " " + y + " " + c);
				
				
				//output to output2
				System.setOut(new PrintStream(fos2));
				newedge = new undirectedEdge(x,y,c);
				pmst.insertEdge(newedge);
				pmst.printList(pmst.edgeListHead);
			}
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} finally{
			if(scan != null) scan.close();	
		}
		
		System.setOut(new PrintStream(fos1));
		System.out.println();
		System.out.println("List MSTofG:");
		
		//Step 4,5,6,7,8
		while(!pmst.isSetBEmpty()){
			//step 4,5		
			newedge = pmst.removeEdge(pmst.edgeListHead);
			//step 6
			pmst.pushEdge(newedge);
			pmst.totalMSTCost += newedge.edgeCost;
			if(pmst.inWhichSet[newedge.Ni] == 1){
				pmst.move2SetA(newedge.Nj);
			}
			else{
				pmst.move2SetA(newedge.Ni);
			}
			System.setOut(new PrintStream(fos2));
			pmst.printSet();
			
			//step 7
			System.setOut(new PrintStream(fos1));
			pmst.printList(pmst.MSTofG);
		}
		
		System.out.println();
		System.out.println("Final MSTofG:");
		pmst.printList(pmst.MSTofG);
		System.out.println("*** The  total Cost  of  the Prim¡¯s MST is: " + pmst.totalMSTCost);
		
		//finish up
		try {
			fos1.close();
			fos2.close();
			System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out)));
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("Done");
	}
}
