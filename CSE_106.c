#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 5000

// Function prototypes
void generateGraph(int n, int graph[n][n]);
void calculateDegrees(int n, int graph[n][n], int inDegrees[n], int outDegrees[n]);
int sumArray(int n, int *array);

// Function to generate a random directed graph represented by an adjacency matrix
void generateGraph(int n, int graph[n][n]) {
    // Generating random directed edges
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                graph[i][j] = rand() % 2; // Randomly assign 0 or 1
            } else {
                graph[i][j] = 0; // No self-loops
            }
        }
    }
}

// Function to calculate in-degrees and out-degrees of all vertices
void calculateDegrees(int n, int graph[n][n], int inDegrees[n], int outDegrees[n]) {
    for (int i = 0; i < n; i++) {
        inDegrees[i] = 0;
        outDegrees[i] = 0;
        for (int j = 0; j < n; j++) {
            outDegrees[i] += graph[i][j];
            inDegrees[j] += graph[i][j];
        }
    }
}

// Function to sum elements of an array
int sumArray(int n, int *array) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }
    return sum;
}

int main() {
    int n_values[] = {1000, 2000, 3000, 4000, 5000};
    int num_n = sizeof(n_values) / sizeof(n_values[0]);
    
    srand(time(NULL)); // Seed for random number generation (moved to main)

    for (int k = 0; k < num_n; k++) {
        int n = n_values[k];
        
        // Dynamic memory allocation
        int (*graph)[n] = malloc(n * sizeof(*graph));
        int *inDegrees = malloc(n * sizeof(int));
        int *outDegrees = malloc(n * sizeof(int));

        clock_t start, end;
        double cpu_time_used;

        start = clock(); // Start timing

        generateGraph(n, graph);
        calculateDegrees(n, graph, inDegrees, outDegrees);

        end = clock(); // End timing
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000; // Time in milliseconds

        printf("For n = %d\n", n);
        printf("Sum of in-degrees: %d\n", sumArray(n, inDegrees));
        printf("Sum of out-degrees: %d\n", sumArray(n, outDegrees));
        printf("Time taken: %f ms\n\n", cpu_time_used);

        // Free allocated memory
        free(graph);
        free(inDegrees);
        free(outDegrees);
    }

    return 0;
}
