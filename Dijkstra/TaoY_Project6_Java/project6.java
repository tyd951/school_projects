import java.io.FileDescriptor;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;

public class project6{

	public static void main(String[] args) {
		DijktraSSS sss = new DijktraSSS();
		FileOutputStream fos = null;
		
		//output to output2
		try {
			fos = new FileOutputStream(args[2]);
			System.setOut(new PrintStream(fos));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		//step 0, 1
		sss.loadCostMatrix(args[0]);

		//step 2
		sss.setBestCostAry();
		sss.setFatherAry();
		sss.setToDoAry();
				
		//step 8
		while(!sss.isAllZero()){
			//step3
			sss.findMinNode();
			sss.markMinNode();
			sss.debugPrint();
			//step 4,5,6,7
			sss.Dijkstras();
		}
		
		//output to output1
		try {
			fos = new FileOutputStream(args[1]);
			System.setOut(new PrintStream(fos));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		//step 9,10,11,12
		sss.printShortestPath();
		
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
