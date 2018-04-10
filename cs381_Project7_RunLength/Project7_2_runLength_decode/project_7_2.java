public class project_7_2 {
	public static void main(String[] args) {
		try{
			System.out.println("argument 1:" + args[0]);
			System.out.println("argument 2:" + args[1]);
		}catch(ArrayIndexOutOfBoundsException e){
			System.out.println("no arguments");
			System.exit(0);
		}
		System.out.println("Method 1) Decode without zero and no wrap-around");
		System.out.println("Method 2) Decode without zero and wrap-around");
		System.out.println("Method 3) Decode with zero and no wrap-around");
		System.out.println("Method 4) Decode with zero and wrap-around");
		new runLengthDecoder(args[0], args[1]).decode();
	}
}
