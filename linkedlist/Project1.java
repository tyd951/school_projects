import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

/**
 * 
 * @author Yida
 *
 */
public class Project1 {

	public static void main(String[] args) {
		LinkedList LL = new LinkedList();
		Scanner sc = null;
		BufferedWriter bw = null;
		FileWriter fw = null;
		String s;
		
		try {
			sc = new Scanner(new File(args[0]));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			System.out.println("Cant find the file" + args[0]);
		}
		
		try {
			fw = new FileWriter(args[1]);
			bw = new BufferedWriter(fw);
			bw.write(LL.print());
			bw.newLine();
			
			while(sc.hasNext()) {
				//System.out.println(LL.print());
				LL.insert(sc.next());
				bw.write(LL.print());
				bw.newLine();
			}
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		sc.close();
		try {
			bw.close();
			fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}		

		//System.out.println("Done");
		
		/* testing code
		LL.print();
		LL.insert("asdasd");
		LL.print();
		LL.insert("hello");
		LL.print();
		LL.insert("aaaa");
		LL.print();
		*/
	}//main

}//class
