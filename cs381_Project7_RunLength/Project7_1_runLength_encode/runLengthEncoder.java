import java.io.*;
import java.util.Scanner;

public class runLengthEncoder {
	int method;
	String infile;
	String outfile;
	int numRows = 0;
	int numCols = 0;
	int minVal = 0;
	int maxVal = 0;
	int greyScale = 0;
	
	public runLengthEncoder(int m, String in, String out){
		method = m;
		infile = in;
		outfile = out;
	}
	
	public void encode(){
		Scanner sc = null;
		FileOutputStream fos = null;
		try {
			fos = new FileOutputStream(outfile);
			System.setOut(new PrintStream(fos));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		try {
			sc = new Scanner(new File(infile));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			System.out.println("Cant find the file: " + infile);
		}
		
		numRows = sc.nextInt();
		numCols = sc.nextInt();
		minVal = sc.nextInt();
		maxVal = sc.nextInt();
		System.out.println(numRows + " " + numCols + " " + minVal + " " + maxVal);
		System.out.println(method);
		
		int count = 0;
		int currVal = 0;
		int totalCount = 0;
		int srow = 0;
		int scol = 0;
		
		if(method == 1){
			currVal = sc.nextInt();
			totalCount++;
			while(sc.hasNextInt()){
				greyScale = currVal;
				srow = (totalCount-1)/numCols;
				scol = (totalCount-1)%numCols;
				count = 1;
				
				if(sc.hasNextInt()){
					currVal = sc.nextInt();
					totalCount++;
				}
				
				while(currVal == greyScale){
					if((totalCount-1)%numCols == 0){
						break;
					}
					count++;
					if(sc.hasNextInt()){
						currVal = sc.nextInt();
						totalCount++;
					}
					else{
						break;
					}
				}
				if(greyScale != 0){
					System.out.println(srow +" "+ scol +" "+ greyScale +" "+ count);
				}
			}
		}
		
		else if(method == 2){
			currVal = sc.nextInt();
			totalCount++;
			while(sc.hasNextInt()){
				greyScale = currVal;
				srow = (totalCount-1)/numCols;
				scol = (totalCount-1)%numCols;
				count = 1;
				
				if(sc.hasNextInt()){
					currVal = sc.nextInt();
					totalCount++;
				}
				
				while(currVal == greyScale){
					count++;
					if(sc.hasNextInt()){
						currVal = sc.nextInt();
						totalCount++;
					}
					else{
						break;
					}
				}
				if(greyScale != 0){
					System.out.println(srow +" "+ scol +" "+ greyScale +" "+ count);
				}
			}
		}
		else if(method == 3){
			currVal = sc.nextInt();
			totalCount++;
			while(sc.hasNextInt()){
				greyScale = currVal;
				srow = (totalCount-1)/numCols;
				scol = (totalCount-1)%numCols;
				count = 1;
				
				if(sc.hasNextInt()){
					currVal = sc.nextInt();
					totalCount++;
				}
				
				while(currVal == greyScale){
					if((totalCount-1)%numCols == 0){
						break;
					}
					count++;
					if(sc.hasNextInt()){
						currVal = sc.nextInt();
						totalCount++;
					}
					else{
						break;
					}
				}
				System.out.println(srow +" "+ scol +" "+ greyScale +" "+ count);
			}
		}
		else if(method == 4){
			currVal = sc.nextInt();
			totalCount++;
			while(sc.hasNextInt()){
				greyScale = currVal;
				srow = (totalCount-1)/numCols;
				scol = (totalCount-1)%numCols;
				count = 1;
				
				if(sc.hasNextInt()){
					currVal = sc.nextInt();
					totalCount++;
				}
				
				while(currVal == greyScale){
					count++;
					if(sc.hasNextInt()){
						currVal = sc.nextInt();
						totalCount++;
					}
					else{
						break;
					}
				}
				System.out.println(srow +" "+ scol +" "+ greyScale +" "+ count);
			}
		}
		
		sc.close();
		try {
			fos.close();
			System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out)));
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		System.out.println("Done");
	}
}
