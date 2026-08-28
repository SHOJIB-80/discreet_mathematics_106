# discreet_mathematics_106

A small C program that generates random directed graphs (adjacency matrix), computes vertex in‑degrees and out‑degrees, and reports degree sums and timing for several vertex counts.

## Overview

This project contains a single C program that:

- Generates a random directed graph represented as an adjacency matrix (no self-loops).
- Computes in-degrees and out-degrees for every vertex.
- Prints the sum of in-degrees, the sum of out-degrees, and the time taken (in milliseconds) for the generation + degree computation.
- Runs the above for a set of predefined vertex counts (1000, 2000, 3000, 4000, 5000) to provide basic performance measurements.

The system is implemented as a command-line C program intended for performance/behavior observation of adjacency-matrix based graph operations.

## Features

* Random directed graph generation (adjacency matrix) without self-loops.
* Per-vertex in-degree and out-degree calculation.
* Sum of in-degrees and out-degrees printed for verification (they should match).
* Timing of graph generation + degree computation reported in milliseconds.
* Runs across multiple vertex sizes (1000..5000) in a loop.

## Technology Stack

| Technology | Purpose                            |
| ---------- | ---------------------------------- |
| C (C99)    | Program implementation             |
| libc       | I/O, memory allocation, timing     |
| gcc/clang  | Compilation                        |

## Project Structure

```text
discreet_mathematics_106/
├── CSE_106.c      # Main C source file
└── README.md      # This file
```

- CSE_106.c: Contains all program logic — graph generation, degree calculation, timing, and printing results.
- README.md: Project documentation.

## How the System Works

1. The program seeds the RNG using the current time (`srand(time(NULL))`).
2. For each n in {1000, 2000, 3000, 4000, 5000}:
   - Allocate an n × n adjacency matrix (int) on the heap and arrays for in/out degrees.
   - Fill every cell graph[i][j] with 0 or 1 at random (except graph[i][i] = 0 to avoid self-loops).
   - Compute out-degrees by summing each row and in-degrees by summing each column.
   - Sum the in-degree and out-degree arrays to print the totals.
   - Measure the elapsed CPU time for generation + degree computation using clock() and print it in milliseconds.
   - Free the allocated memory and continue to the next n.

System dataflow (conceptual):

User runs program
  ↓
C program (generateGraph → calculateDegrees → sumArray)
  ↓
Printed results (console): degree sums and timings

## Compilation

Compile the program with a C compiler that supports C99. Example using gcc:

```bash
gcc -std=c99 -O2 -Wall -Wextra -o CSE_106 CSE_106.c
```

- -std=c99: code uses C99-compatible features.
- -O2: recommended optimization for timing.
- -Wall -Wextra: enable common warnings.

## Running

After compilation, run the executable from the terminal:

```bash
./CSE_106
```

The program prints results for each n in the predefined list. Example output format:

```
For n = 1000
Sum of in-degrees: <integer>
Sum of out-degrees: <integer>
Time taken: <floating> ms

For n = 2000
...
```

Notes:
- The printed sums represent the total number of directed edges in the generated graph and, for a consistent adjacency matrix, the sum of in-degrees equals the sum of out-degrees.
- Timing measures the combined duration of generating the matrix and calculating degrees for each n.

## Code Overview

Key functions in CSE_106.c:

- generateGraph(int n, int graph[n][n])
  - Populates the adjacency matrix with random 0/1 values for each pair (i, j) where i != j. Self-loops are set to 0.

- calculateDegrees(int n, int graph[n][n], int inDegrees[n], int outDegrees[n])
  - Computes out-degree by summing each row and accumulates in-degree per column as it iterates.

- sumArray(int n, int *array)
  - Returns the sum of the integer array (used to sum degree arrays).

- main()
  - Controls the list of n values, allocates memory, seeds RNG, invokes the functions above, times the operations, prints results, and frees memory.

## Performance & Resource Considerations

- Memory usage: The adjacency matrix uses O(n^2) integers. For n = 5000, the matrix allocates approximately 25,000,000 ints (~95–100 MB depending on sizeof(int)). Ensure the system has sufficient memory before running the largest value.
- Time measurement uses clock() from <time.h>, which reports CPU time; the printed value is converted to milliseconds.
- Randomness: The program uses rand() seeded with time(NULL). Results are non-deterministic between runs.

## Testing

- There are no automated tests in this repository.
- Basic verification: for each run, verify that "Sum of in-degrees" equals "Sum of out-degrees"; these should match because every directed edge contributes exactly 1 to one out-degree and 1 to one in-degree.

## Known Limitations

* The program stores the full adjacency matrix in memory; this is not suitable for very large graphs where sparse representations would be more memory-efficient.
* Random graph generation uses rand() / RAND_MAX semantics; distribution is uniform over {0,1} per directed edge but may not be suitable for simulations requiring specific edge probabilities other than 0.5.
* No command-line options are provided — vertex sizes are hard-coded in main.
* No input validation or error reporting for allocation failures is provided (malloc return values are not checked).

## Security Considerations

* The project is a local command-line utility with no external input or networking; standard secure-coding practices for C (checking allocation results, bounds, and integer overflows) are not fully implemented here.

## License

No license file is present in the repository. The project has no explicit license declared.

## Author

Repository owner: SHOJIB-80
