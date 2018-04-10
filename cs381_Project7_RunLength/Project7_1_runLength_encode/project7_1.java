import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class project7_1 {
	public static void main(String[] args) {
		int method = 0;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try{
			System.out.println("argument 1:" + args[0]);
			System.out.println("argument 2:" + args[1]);
		}catch(ArrayIndexOutOfBoundsException e){
			System.out.println("no arguments");
			System.exit(0);
		}
		
		System.out.println("Which method do you want to encode? ");
		System.out.println("Method 1) Encode without zero and no wrap-around");
		System.out.println("Method 2) Encode without zero and wrap-around");
		System.out.println("Method 3) Encode with zero and no wrap-around");
		System.out.println("Method 4) Encode with zero and wrap-around");
		System.out.println("Give me a number (1,2,3,4)");
		try{
			method = Integer.parseInt(br.readLine());
		} catch (IOException e) {
			e.printStackTrace();
		} catch(NumberFormatException e){
			System.out.println("input is not a number!");
			System.exit(0);
		}
		if(method < 1 || method > 4){
			System.out.println("invaild number!");
			System.exit(0);
		}
		
		runLengthEncoder rle = new runLengthEncoder(method, args[0], args[1]);
		rle.encode();
	}
}
