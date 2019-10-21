# Based on https://www.gurobi.com/documentation/8.1/examples/workforce1_py.html by Gurobi Optimization, LLC
#
# Assign workers to shifts; each worker may or may not be available on a
# particular day.

set SHIFTS := {"Mon1", "Tue2", "Wed3", "Thu4", "Fri5", "Sat6", "Sun7",
"Mon8", "Tue9", "Wed10", "Thu11", "Fri12", "Sat13", "Sun14"};
set WORKERS := {"Amy", "Bob", "Cathy", "Dan", "Ed", "Fred", "Gu"};

# Number of workers required for each shift
param shiftRequirements[SHIFTS] :=
    <"Mon1"> 3,
    <"Tue2"> 2,
    <"Wed3"> 4,
    <"Thu4"> 4,
    <"Fri5"> 5,
    <"Sat6"> 6,
    <"Sun7"> 5,
    <"Mon8"> 2,
    <"Tue9"> 2,
    <"Wed10"> 3,
    <"Thu11"> 4,
    <"Fri12"> 6,
    <"Sat13"> 7,
    <"Sun14"> 5;

# Amount each worker is paid to work one shift
param pay[WORKERS] :=
    <"Amy"> 10,
    <"Bob"> 12,
    <"Cathy"> 10,
    <"Dan"> 8,
    <"Ed"> 8,
    <"Fred"> 9,
    <"Gu"> 11;

# Worker availability
param availability[WORKERS * SHIFTS] :=
    <"Amy", "Tue2"> 1,
    <"Amy", "Wed3"> 1,
    <"Amy", "Fri5"> 1,
    <"Amy", "Sun7"> 1,
    <"Amy", "Tue9"> 1,
    <"Amy", "Wed10"> 1,
    <"Amy", "Thu11"> 1,
    <"Amy", "Fri12"> 1,
    <"Amy", "Sat13"> 1,
    <"Amy", "Sun14"> 1,
    <"Bob", "Mon1"> 1,
    <"Bob", "Tue2"> 1,
    <"Bob", "Fri5"> 1,
    <"Bob", "Sat6"> 1,
    <"Bob", "Mon8"> 1,
    <"Bob", "Thu11"> 1,
    <"Bob", "Sat13"> 1,
    <"Cathy", "Wed3"> 1,
    <"Cathy", "Thu4"> 1,
    <"Cathy", "Fri5"> 1,
    <"Cathy", "Sun7"> 1,
    <"Cathy", "Mon8"> 1,
    <"Cathy", "Tue9"> 1,
    <"Cathy", "Wed10"> 1,
    <"Cathy", "Thu11"> 1,
    <"Cathy", "Fri12"> 1,
    <"Cathy", "Sat13"> 1,
    <"Cathy", "Sun14"> 1,
    <"Dan", "Tue2"> 1,
    <"Dan", "Wed3"> 1,
    <"Dan", "Fri5"> 1,
    <"Dan", "Sat6"> 1,
    <"Dan", "Mon8"> 1,
    <"Dan", "Tue9"> 1,
    <"Dan", "Wed10"> 1,
    <"Dan", "Thu11"> 1,
    <"Dan", "Fri12"> 1,
    <"Dan", "Sat13"> 1,
    <"Dan", "Sun14"> 1,
    <"Ed", "Mon1"> 1,
    <"Ed", "Tue2"> 1,
    <"Ed", "Wed3"> 1,
    <"Ed", "Thu4"> 1,
    <"Ed", "Fri5"> 1,
    <"Ed", "Sun7"> 1,
    <"Ed", "Mon8"> 1,
    <"Ed", "Tue9"> 1,
    <"Ed", "Thu11"> 1,
    <"Ed", "Sat13"> 1,
    <"Ed", "Sun14"> 1,
    <"Fred", "Mon1"> 1,
    <"Fred", "Tue2"> 1,
    <"Fred", "Wed3"> 1,
    <"Fred", "Sat6"> 1,
    <"Fred", "Mon8"> 1,
    <"Fred", "Tue9"> 1,
    <"Fred", "Fri12"> 1,
    <"Fred", "Sat13"> 1,
    <"Fred", "Sun14"> 1,
    <"Gu", "Mon1"> 1,
    <"Gu", "Tue2"> 1,
    <"Gu", "Wed3"> 1,
    <"Gu", "Fri5"> 1,
    <"Gu", "Sat6"> 1,
    <"Gu", "Sun7"> 1,
    <"Gu", "Mon8"> 1,
    <"Gu", "Tue9"> 1,
    <"Gu", "Wed10"> 1,
    <"Gu", "Thu11"> 1,
    <"Gu", "Fri12"> 1,
    <"Gu", "Sat13"> 1,
    <"Gu", "Sun14"> 1
    default 0;

# Assignment variables: x[w,s] == 1 if worker w is assigned to shift s.
# Since an assignment model always produces integer solutions, we use
# continuous variables and solve as an LP.
var x[WORKERS * SHIFTS] real >= 0 <= 1;

# The objective is to minimize the total pay costs
minimize cost:
    sum <w, s> in WORKERS * SHIFTS: pay[w] * x[w,s];

### END OF TEMPLATE ###

# Constraints: assign exactly shiftRequirements[s] workers to each shift s
subto assignment:
    forall <s> in SHIFTS:
        sum <w> in WORKERS: x[w, s] == shiftRequirements[s];





