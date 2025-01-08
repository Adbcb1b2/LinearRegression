#include <stdlib.h>
#include <stdio.h>

// Initialise a struct
struct RegressionResult {
    float a;
    float b;
};

void readFile(const char* filename, int** xvals, int** yvals, int* n){
    
    // Initialise file pointer
    FILE* fptr;
    
    // Open the file in read mode
    fptr = fopen(filename, "r"); 
    
    // Error check
    if(fptr == NULL){
        printf("Error opening the file %s\n", filename);
        exit(-1); //Exit program if file can't be opened
    }else{
        printf("File opened successfully\n");
    }
    
    // Initialise variables to count lines and to store values read from line
    int line_count = 0;
    int x, y;

    // Count the number of lines in the file
    // fscanf returns the number of matched items
    while(fscanf(fptr, "%d,%d", &x, &y) == 2){
        line_count++;
        }
    printf("line count = %d\n", line_count);
    
    // Assign value of line_count to n, to be used later on
    *n = line_count;
    
    // Allocate memory for arrays according to length of file
    *xvals = (int*)malloc(line_count * sizeof(int));
    *yvals = (int*)malloc(line_count * sizeof(int));
    
    // Go back to the beginning of the file
    rewind(fptr);
    
    // Read values from file, store in arrays
    for(int i = 0;  i < line_count; i++){
        fscanf(fptr, "%d,%d", *xvals + i, *yvals + i);
    }
        
    
    // Close the file    
    fclose(fptr);
    

}


struct RegressionResult LinearRegression(int* xvals, int* yvals, int* n){
	struct RegressionResult result;
	
	// If n = 0, both denominators are 0 (error)
	if(*n == 0){
		result.a = 0;
		result.b = 0;
		printf("Error: Cann't divide by 0\n");
	}
		
	// Sum of x vals
	int sum_x = 0;
	for(int i = 0; i < *n; i++){
		sum_x += xvals[i];
	
	}
	printf("Sum of x = %d\n", sum_x); // test
	
	
	// Sum of y vals
	int sum_y = 0;
	for(int i = 0; i < *n; i++){
		sum_y +=yvals[i];
	}
	printf("Sum of y = %d \n", sum_y); // test
	
	
	// Sum of (x vals)^2
	int sum_xsq = 0;
	for(int i = 0; i < *n; i++){
		sum_xsq += (xvals[i] * xvals[i]);
	}
	printf("Sum of x^2 = %d \n", sum_xsq);
	
	// Sum of xy
	int sum_xy = 0;
	for(int i = 0; i < *n; i++){
		sum_xy += (xvals[i] * yvals[i]);
	}
	printf("Sum of xy = %d\n", sum_xy);
	
		
	// Calculate y intercept
	result.a = (float)(sum_y * sum_xsq - sum_x * sum_xy)/(*n * sum_xsq - sum_x * sum_x);
	
	//  Calculate gradient
	result.b = (float)(*n * sum_xy - sum_x * sum_y)/(*n * sum_xsq - sum_x * sum_x);
	
	// Return the struct
	return result;
}


void main(int argc, char** argv){
	
    const char* filename = argv[1];
    int n;
    int* xvals;
    int* yvals;
    
    float a;
    float b;
    
    float x;
    float y;
    
    // Read the file, store data in appropriate variables
    readFile(filename, &xvals, &yvals, &n);
    
    // Call the linear regression function on the values read from file
    struct RegressionResult regressionResult = LinearRegression(xvals, yvals, &n);
    
    // Get the values from the struct
    a = regressionResult.a;
    b = regressionResult.b;
    
   	// Use calculated values to display equation of straight line
    printf("The equation of your line is: \n");
    printf("y = %fx + %f\n", b, a);
    
    // Calculate the value of y when x is inputted
    printf("Enter an x value to calculate y\n");
    scanf("%f", &x);
    y = b * x + a;
    printf("y = %f\n",y);
    

    // Free the memory   
    free(xvals);
    free(yvals);

}
