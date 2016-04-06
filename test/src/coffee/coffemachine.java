package coffee;
/*
Question: 
Lenovo wants to make sure that all of its Engineers are close to a coffee machine.
Given a floor plan of the office showing the locations of all the coffee machines,
determine how far each engineer is from the nearest coffee machine.

The office can be represented as a 2D array where each cell contains exactly one of the following:
an engineer's desk, a wall (impassable) or a coffee machine. Distance is defined as the number of
steps the engineer would have to take to reach a coffee machine by moving up, down,
left and right to adjacent rooms without being able to pass through walls.

The function must return a 2D integer array containing the distances.

At a first step please describe the different ways you would consider for solving this task.
 Also indicate the pros and cons for each alternative, then you will need to implement it.

Our interview has a hard stop at 45 minutes.
*/

/******************************************/
/*
Assumptions: 
The matrix is in int[m][n], represents the floor map 
1.Employee is initialized to be int: Integer.MAX_VALUE. 
	But it can be any positive number after the calculation, represents its distance to nearest coffee machine
2.coffe machine is int: -1
3.wall is int: -2 . 
The matrix representing the floor is not empty// 

input: the matrix of the floor in above description
result: the same matrix, with engineer updated to be the number of steps needed to reach a nearest coffee machine

 //Approch 3
 // DFS search
 start form the coffemachine    
     scan the matrix, when find an coffemachine, start the DFS and update each value in the matrix.
     o((mn)^2) time complexity
     
     findengineer(matrix, result, n,i+1,j)
     findengineer(matrix, result, n,i-1,j)
     findengineer(matrix, result, n,i,j+1)
     findengineer(matrix, result, n,i,j-1)
     matrix[i][j] = 1
     
     */


public class coffemachine{
	final int ENGINEER = Integer.MAX_VALUE;
	final int COFEEMACHINE = -1;
	final int WALL = -2;
    public int[][] matrix = null;
    public int m = -1;
    public int n = -1;

    public coffemachine(int[][] ma){
    	if(ma == null || ma.length == 0 || ma[0].length == 0) return;
        m = ma.length;
        n = ma[0].length;
        matrix = new int[m][n];
        for(int i = 0; i<m; i++){
        	for(int j = 0; j< n; j++){
        		matrix[i][j] = ma[i][j];
        	}
        }
    } 
    
    public int[][] findengineer(){    
        //validate the matrix
        if(matrix == null || m < 0 || n < 0) return new int[0][0];

        for(int i = 0; i< m; i++){
            for(int j = 0; j < n; j++){
                if(matrix[i][j] == COFEEMACHINE)
                	findengineerHelper(i, j, 0);
            }
        }
        
        return matrix;
    }
    //use length to track the steps so far. 
    //Call next recursion only when new length is smaller than previous one
    public void findengineerHelper(int i, int j, int length){
        
        if(i+1<m && matrix[i+1][j] > length+1 ){ //length is larger than 0 so matrix[i+1][j] can not be machine or wall
            matrix[i+1][j] = length +1;
            findengineerHelper(i+1, j, length +1);
            }
        if(i-1>=0 && matrix[i-1][j] > length+1 ){ 
            matrix[i-1][j] = length +1;
            findengineerHelper(i-1, j, length +1);
            }
        if(j+1<n && matrix[i][j+1] > length+1 ){ 
            matrix[i][j+1] = length +1;
            findengineerHelper(i, j+1, length +1);
            }
        if(j-1>=0 && matrix[i][j-1] > length+1 ){ 
            matrix[i][j-1] = length +1;
            findengineerHelper(i, j-1, length +1);
            }
    }
    
    public int distance(int i, int j){
        if(matrix == null || i<0 || j<0 || i>= m || j>=n )
            return Integer.MAX_VALUE;
        return matrix[i][j];
    }

}     
     
     
     