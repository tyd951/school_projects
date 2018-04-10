import java.io.*;
import java.util.Scanner;

public class runLengthDecoder {
	int method;
	String infile;
	String outfile;
	int numRows = 0;
	int numCols = 0;
	int minVal = 0;
	int maxVal = 0;
	
	public runLengthDecoder(String in, String out) {
		infile = in;
		outfile = out;
	}

	public void decode() {
		Scanner sc = null;
		FileOutputStream fos = null;
		int srow = 0;
		int scol = 0;
		int greyScale = 0;
		int length = 0;
		int totalCount = 0;
		
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
		method = sc.nextInt();
		if(method < 1 || method > 4){
			System.out.println("invaild method number");
			System.exit(0);
		}
		
		try {
			fos = new FileOutputStream(outfile);
			System.setOut(new PrintStream(fos));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		System.out.println(numRows + " " + numCols + " " + minVal + " " + maxVal);
		if(method == 1){
			while(sc.hasNextInt()){
				srow = sc.nextInt();
				scol = sc.nextInt();
				greyScale = sc.nextInt();
				length = sc.nextInt();
				while(totalCount < (srow*numCols + scol)){
					System.out.print(0 + " ");
					totalCount ++;
					if(totalCount % numCols == 0){
						System.out.println();
					}
				}
				while(length > 0){
					System.out.print(greyScale + " ");
					totalCount ++;
					length --;
				}
				if(totalCount % numCols == 0){
					System.out.println();
				}
			}
			while(totalCount < numCols*numRows){
				System.out.print(0 + " ");
				totalCount ++;
			}
		}
		else if(method == 2){
			while(sc.hasNextInt()){
				srow = sc.nextInt();
				scol = sc.nextInt();
				greyScale = sc.nextInt();
				length = sc.nextInt();
				while(totalCount < (srow*numCols + scol)){
					System.out.print(0 + " ");
					totalCount ++;
					if(totalCount % numCols == 0){
						System.out.println();
					}
				}
				while(length > 0){
					System.out.print(greyScale + " ");
					totalCount ++;
					if(totalCount % numCols == 0){
						System.out.println();
					}
					length --;
				}
				
			}
			while(totalCount < numCols*numRows){
				System.out.print(0 + " ");
				totalCount ++;
			}
		}
		else if(method == 3){
			while(sc.hasNextInt()){
				srow = sc.nextInt();
				scol = sc.nextInt();
				greyScale = sc.nextInt();
				length = sc.nextInt();

				while(length > 0){
					System.out.print(greyScale + " ");
					totalCount ++;
					length --;
				}
				if(totalCount % numCols == 0){
					System.out.println();
				}
			}
		}
		else if(method == 4){
			while(sc.hasNextInt()){
				srow = sc.nextInt();
				scol = sc.nextInt();
				greyScale = sc.nextInt();
				length = sc.nextInt();

				while(length > 0){
					System.out.print(greyScale + " ");
					totalCount ++;
					if(totalCount % numCols == 0){
						System.out.println();
					}
					length --;
				}	
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
