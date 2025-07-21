#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Use a structure
struct LRResult {
    float a;
    float b;
};

// Read from file function:
void readFile(const char* filename, int** xvalues, int** yvalues, int* n) {
    FILE* fptr;// Pointer for the file.
    fptr = fopen(filename, "r"); // Opening the file

    if (fptr == NULL) {
        fprintf(stderr, "Error opening file\n");
        perror("Error");
        exit(-1);
    } else {
        printf("File successfully opened.\n");
    }

    // Initialise variables for use in counting line total in file.
    int totalLines = 0;
    char c;
    //figure out EOF and use that for a for loop. as n will equal the total amount.
    while ((c = fgetc(fptr)) != EOF) {
        if(c == '\n'){
            totalLines++;
        }
    }
    printf("Total lines in file: %d\n", totalLines);

    // Assign totalLines to n. This will be used later in LRResult.
    *n = totalLines;
    // Using malloc to assign memory for the arrays, depending upon file length.
    *xvalues = (int*)malloc(totalLines * sizeof(int));
    *yvalues = (int*)malloc(totalLines * sizeof(int));

    rewind(fptr); // reusing pointer

    // Read values from file, store in arrays
    for(int i = 0;  i < totalLines; i++) {
        fscanf(fptr, "%d,%d", *xvalues + i, *yvalues + i);
    }

    // Close file
    fclose(fptr);
}

// Function here:
struct LRResult linearRegression(int* xvalues, int* yvalues, int* n) {
    struct LRResult result;
    int sumx = 0, sumy = 0, sumxy = 0, sumxsq = 0;
    float x, y;

    // Check if both denominators are 0
    if (*n == 0) {
        result.a = 0;
        result.b = 0;
        printf("Can't divide by 0.\n");
    }

    for(int i = 0; i < *n; i++) { //Calculate the sum of x values.
        sumx += xvalues[i];
    }

    for(int i = 0; i < *n; i++) { //Calculate the sum of y values.
        sumy += yvalues[i];
    }

    for(int i = 0; i < *n; i++) { //Calculate the sum of x values sqrt.
        sumxsq += (xvalues[i] * xvalues[i]);
    }

    for(int i = 0; i < *n; i++) { //Calculate the sum of xy values.
        sumxy += (xvalues[i] * yvalues[i]);
    }

    // Formula for calculating linear regression coefficients
    result.a = (float)(sumy * sumxsq - sumx * sumxy) / (*n * sumxsq - sumx * sumx); //y intercept
    result.b = (float)(*n * sumxy - sumx * sumy) / (*n * sumxsq - sumx * sumx); //gradient
    printf("Calculate LR: Sumx: %d, Sumy: %d Sumxsq: %d, Sumxy: %d, n: %d\n", sumx, sumy, sumxsq, sumxy, *n);
    printf("\n");
    printf("This is to test y: %.20f\n", result.a);
    printf("This is to test gradient: %.20f\n", result.b);
    printf("\n");
    return result;
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE * fptr;
    int* xvalues;
    int* yvalues;
    int n;

    float a;
    float b;

    float x_input;

    readFile(filename, &xvalues, &yvalues, &n);

    struct LRResult results = linearRegression(xvalues, yvalues, &n); //Call linear Regression function
    a = results.a;
    b = results.b;


    printf("Linear Equation: y = %.10fx + %.10f\n", b, a);

    // y=mx+c  Mx = b, C= a
    printf("Enter a value of x: "); //Ask user to type in value of x to calculate y.
    scanf("%f", &x_input);
    float y_output = results.b * x_input + results.a;
    printf("For x = %.2f, y = %.2f\n", x_input, y_output);

    // Clear the memory
    free(xvalues);
    free(yvalues);

    return 0;
}
