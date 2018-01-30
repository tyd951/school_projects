import java.io.*;
import java.util.Arrays;
import java.util.Scanner;
/**
 * @author Yida
 */
public class Project2 {
	/**
	 * @param myAry
	 * @param arg
	 */
	public static void printAry(int[] myAry,String arg){
		BufferedWriter bw = null;
		FileWriter fw = null;
		try {
			fw = new FileWriter(arg);
			bw = new BufferedWriter(fw);
			//ignore ASCII code 0-32
			for(int i = 33; i < 256; i++){
				if(myAry[i] !=0){
					char[] c= Character.toChars(i);
					bw.write(c[0] + "  # " + myAry[i]);
					bw.newLine();
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				bw.close();
				fw.close();
			} catch (IOException e) {
				e.printStackTrace();
			}	
		}
	}//method printAry
	
	public static void main(String[] args) {
		char charIn = 0;
		int index;
		int[] charCounts = new int[256];
		Arrays.fill(charCounts,0);// initialize all my array elements to 0
		Scanner scan = null;
		
		try {
			scan = new Scanner(new File(args[0]));
			scan.useDelimiter("");//user scanner to read char by char
			
			while(scan.hasNext()){
				charIn = scan.next().charAt(0);
				index = (int)charIn;
				if(index>=0 && index<256){
					charCounts[index]++;
				}
				//System.out.print(charIn+":");
				//System.out.println((int)charIn);
				//System.out.println(Character.toChars((int)charIn));
				//System.out.println(charIn);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} finally{
			if(scan != null)scan.close();
			
		}
		/*
		for(int i = 33; i < 256; i++){
			if(charCounts[i] !=0){
				char[] c= Character.toChars(i);
				System.out.println(c[0] + ":" + charCounts[i]);
			}
		}
		*/
		printAry(charCounts,args[1]);
	}//main
}//class
