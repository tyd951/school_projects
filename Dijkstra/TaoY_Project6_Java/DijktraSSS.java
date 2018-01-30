import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class DijktraSSS {
	int numNodes;
	int sourceNode;
	int minNode;
	int currentNode;
	int newCost;
	int costMatrix[][];
	int fatherAry[];
	int toDoAry[];
	int bestCostAry[];
	int count=0;
	
	public void loadCostMatrix(String in){
		Scanner sc = null;
		try {
			sc = new Scanner(new File(in));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		//load # of node and source node
		if(sc.hasNext()){
			numNodes = sc.nextInt();
			if(sc.hasNext()){
				sourceNode = sc.nextInt();
			}	
		}
		
		//initialize arrays
		costMatrix = new int[numNodes + 1][numNodes + 1];
		fatherAry = new int[numNodes + 1];
		toDoAry = new int[numNodes + 1];
		bestCostAry = new int[numNodes + 1];
		
		for(int i = 0; i < numNodes + 1; i++){
			fatherAry[i] = i;
			toDoAry[i] = 1;
			bestCostAry[i] = 99999;
			for(int j = 0; j < numNodes + 1;j++){
				costMatrix[i][j] = 99999;
			}
			costMatrix[i][i] = 0;
		}
		
		//load date to costmatrix
		int start = 0;
		int end = 0;
		int distance = 0;
		while(sc.hasNext()) {
			start = sc.nextInt();
			end = sc.nextInt();
			distance = sc.nextInt();
			costMatrix[start][end] = distance;
		}
		sc.close();
		
		System.out.println("costMatrix:");
		for(int i = 1; i < numNodes + 1; i++){
			for(int j = 1; j < numNodes + 1;j++){
				System.out.print(costMatrix[i][j] + "   ");
			}
			System.out.println();
		}
	}
	
	public void setBestCostAry(){
		for(int i = 1; i < numNodes + 1; i++){
			bestCostAry[i] = costMatrix[sourceNode][i];
		}
	}
	
	public void setToDoAry(){
		toDoAry[sourceNode] = 0;
	}
	
	public void setFatherAry(){
		for(int i = 1; i < numNodes + 1; i++){
			fatherAry[i] = sourceNode;
		}
	}
	
	public void findMinNode(){
		int min = 99999;
		for(int i = 1; i < numNodes + 1; i++){
			if(toDoAry[i] == 1 && bestCostAry[i] < min){
				minNode = i;
				min = bestCostAry[i];
			}
		}
	}
	
	public boolean isAllZero(){
		for(int i = 1; i< numNodes + 1; i++){
			if(toDoAry[i] == 1){
				return false;
			}
		}
		return true;
	}
	
	public void computeCost(){
		newCost = bestCostAry[minNode] + costMatrix[minNode][currentNode];
	}
	
	public void markMinNode(){
		toDoAry[minNode] = 0;
	}
	
	public void changeFather(){
		fatherAry[currentNode] = minNode;
	}
	
	public void changeCost(){
		bestCostAry[currentNode] = newCost;
	}
	
	
	public void debugPrint(){
		System.out.println("====================================");
		System.out.println("loop " + count + ": ");
		System.out.println("the sourceNode is:" + sourceNode);
		
		System.out.print("fatherAry: ");
		for(int i = 1; i < numNodes + 1; i++){
			System.out.print(fatherAry[i]+" ");
		}
		System.out.println();
		
		System.out.print("bestCostAry: ");
		for(int i = 1; i < numNodes + 1; i++){
			System.out.print(bestCostAry[i]+" ");
		}
		System.out.println();
		
		System.out.print("toDoAry: ");
		for(int i = 1; i < numNodes + 1; i++){
			System.out.print(toDoAry[i]+" ");
		}
		System.out.println();
		
		count++;
	}
	
	public void Dijkstras(){
		for(currentNode = 1; currentNode< numNodes + 1; currentNode++){
			if(toDoAry[currentNode] == 1){
				computeCost();
				if(newCost < bestCostAry[currentNode]){
					changeCost();
					changeFather();
					debugPrint();
				}
			}
		}
	}
	
	public void printShortestPath(){
		int temp = 0;
		System.out.println("====================================");
		System.out.println("There are " + numNodes + " nodes in the input graph.");
		System.out.println("====================================");
		System.out.println("Source node = " + sourceNode);
		System.out.println("The shortest paths from the source node " + sourceNode + " are:");
		for(currentNode = 1; currentNode< numNodes + 1; currentNode++){
			System.out.print("The path from " + sourceNode + " to "+ currentNode + " : " + currentNode);
			temp = fatherAry[currentNode];
			while(temp != sourceNode){
				System.out.print("<--" + temp);
				temp = fatherAry[temp];
			}
			System.out.println("<--" + temp + "   ||||  Cost: " + bestCostAry[currentNode]);			
		}
	}
	
}
