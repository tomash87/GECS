# Based on https://www.gurobi.com/documentation/8.1/examples/sudoku_py.html by Gurobi Optimization, LLC
#
# Sudoku example.

# The Sudoku board is a 9x9 grid, which is further divided into a 3x3 grid
# of 3x3 grids.  Each cell in the grid must take a value from 0 to 9.
# No two grid cells in the same row, column, or 3x3 subgrid may take the
# same value.
#
# In the MIP formulation, binary variables x[i,j,v] indicate whether
# cell <i,j> takes value 'v'.  The constraints are as follows:
#   1. Each cell must take exactly one value (sum_v x[i,j,v] = 1)
#   2. Each value is used exactly once per row (sum_i x[i,j,v] = 1)
#   3. Each value is used exactly once per column (sum_j x[i,j,v] = 1)
#   4. Each value is used exactly once per 3x3 subgrid (sum_grid x[i,j,v] = 1)

set N := {1 to 9};
param s := sqrt(max(N));
set S[<n> in N] := {<i, j> in {floor((n-1)/s) * s + 1 to (floor((n-1)/s)+1) * s} * {((n-1) mod s) * s + 1 to (((n-1) mod s)+1) * s} };
# initial grid with empty fields (denoted by 0)
param grid[N * N] :=
   | 1, 2, 3, 4, 5, 6, 7, 8, 9|
| 1| 0, 2, 8, 4, 7, 6, 3, 0, 0|
| 2| 0, 0, 0, 8, 3, 9, 0, 2, 0|
| 3| 7, 0, 0, 5, 1, 2, 0, 8, 0|
| 4| 0, 0, 1, 7, 9, 0, 0, 4, 0|
| 5| 3, 0, 0, 0, 0, 0, 0, 0, 0|
| 6| 0, 0, 9, 0, 0, 0, 1, 0, 0|
| 7| 0, 5, 0, 0, 8, 0, 0, 0, 0|
| 8| 0, 0, 6, 9, 2, 0, 0, 0, 5|
| 9| 0, 0, 2, 6, 4, 5, 0, 0, 8|;

# Create our 3-D array of model variables
# Fix variables associated with cells whose values are pre-specified
var vars[<i, j, v> in N * N * N] integer >= (if grid[i,j] == v then 1 else 0 end) <= 1;

### END OF TEMPLATE ###

# Each cell must take one value
subto one:
    forall <i, j> in N * N:
        sum <v> in N: vars[i, j, v] == 1;

# Each value appears once per row
subto unique_row:
    forall <i, v> in N * N:
        sum <j> in N: vars[i, j, v] == 1;

# Each value appears once per column
subto unique_col:
    forall <j, v> in N * N:
        sum <i> in N: vars[i, j, v] == 1;

# Each value appears once per subgrid
subto subgrid:
    forall <n> in N:                                # for each subgrid
        forall <v> in N:                            # for each number
            sum <i, j> in S[n]: vars[i, j, v] == 1; # only one variable equals 1

