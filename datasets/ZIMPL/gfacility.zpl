# Based on https://www.gurobi.com/documentation/8.1/examples/facility_py.html by Gurobi Optimization, LLC
#
# Facility location: a company currently ships its product from 5 plants
# to 4 warehouses. It is considering closing some plants to reduce
# costs. What plant(s) should the company close, in order to minimize
# transportation and fixed costs?
#
# Note that this example uses lists instead of dictionaries.  Since
# it does not work with sparse data, lists are a reasonable option.
#
# Based on an example from Frontline Systems:
#   http://www.solver.com/disfacility.htm
# Used with permission.

set WAREHOUSES := {1 to 4};
# Warehouse demand in thousands of units
param demand[WAREHOUSES] := <1> 15, <2> 18, <3> 14, <4> 20;

set PLANTS := {1 to 5};
# Plant capacity in thousands of units
param capacity[PLANTS] := <1> 20, <2> 22, <3> 17, <4> 19, <5> 18;

# Fixed costs for each plant
param fixedCosts[PLANTS] := <1> 12000, <2> 15000, <3> 17000, <4> 13000, <5> 16000;

# Transportation costs per thousand units
param transCosts[WAREHOUSES * PLANTS] :=
    |    1,    2,    3,    4,    5|
|  1| 4000, 2000, 3000, 2500, 4500|
|  2| 2500, 2600, 3400, 3000, 4000|
|  3| 1200, 1800, 2600, 4100, 3000|
|  4| 2200, 2600, 3100, 3700, 3200|;

# Plant open decision variables: open[p] == 1 if plant p is open.
var open[PLANTS] binary;

# Transportation decision variables: transport[w,p] captures the
# optimal quantity to transport to warehouse w from plant p
var transport[WAREHOUSES * PLANTS] real >= 0;

minimize cost:
    sum <p> in PLANTS: fixedCosts[p] * open[p] + sum <w,p> in WAREHOUSES * PLANTS: transCosts[w,p] * transport[w,p];

### END OF TEMPLATE ###

# Production constraints
# Note that the right-hand limit sets the production to zero if the plant
# is closed
subto production:
    forall <p> in PLANTS:
        sum <w> in WAREHOUSES: transport[w, p] <= capacity[p] * open[p];

# Demand constraints
subto demand:
    forall <w> in WAREHOUSES:
        sum <p> in PLANTS: transport[w, p] == demand[w];

