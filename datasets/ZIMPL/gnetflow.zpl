# Based on https://www.gurobi.com/documentation/8.1/examples/netflow_py.html by Gurobi Optimization, LLC
#
# Solve a multi-commodity flow problem.  Two products ('Pencils' and 'Pens')
# are produced in 2 cities ('Detroit' and 'Denver') and must be sent to
# warehouses in 3 cities ('Boston', 'New York', and 'Seattle') to
# satisfy demand ('inflow[h,i]').
#
# Flows on the transportation network must respect arc capacity constraints
# ('capacity[i,j]'). The objective is to minimize the sum of the arc
# transportation costs ('cost[i,j]').

# Base data
set COMMODITIES := {"Pencils", "Pens"};
set NODES := {"Detroit", "Denver", "Boston", "New York", "Seattle"};
param capacity[NODES * NODES] :=
    <"Detroit", "Boston"> 100,
    <"Detroit", "New York"> 80,
    <"Detroit", "Seattle"> 120,
    <"Denver", "Boston"> 120,
    <"Denver", "New York"> 120,
    <"Denver", "Seattle"> 120
    default 0;

# Cost for triplets commodity-source-destination
param cost[COMMODITIES * NODES * NODES] :=
    <"Pencils", "Detroit", "Boston"> 10,
    <"Pencils", "Detroit", "New York"> 20,
    <"Pencils", "Detroit", "Seattle"> 60,
    <"Pencils", "Denver", "Boston"> 40,
    <"Pencils", "Denver", "New York"> 40,
    <"Pencils", "Denver", "Seattle"> 30,
    <"Pens", "Detroit", "Boston"> 20,
    <"Pens", "Detroit", "New York"> 20,
    <"Pens", "Detroit", "Seattle"> 80,
    <"Pens", "Denver", "Boston"> 60,
    <"Pens", "Denver", "New York"> 70,
    <"Pens", "Denver", "Seattle"> 30
    default 1e10;

# Demand for pairs of commodity-city
param inflow[COMMODITIES * NODES] :=
    <"Pencils", "Detroit"> 50,
    <"Pencils", "Denver"> 60,
    <"Pencils", "Boston"> -50,
    <"Pencils", "New York"> -50,
    <"Pencils", "Seattle"> -10,
    <"Pens", "Detroit"> 60,
    <"Pens", "Denver"> 40,
    <"Pens", "Boston"> -40,
    <"Pens", "New York"> -30,
    <"Pens", "Seattle"> -30
    default 0;

# Create variables
var flow[COMMODITIES * NODES * NODES] integer >= 0;

minimize total_flow:
    sum <c, n1, n2> in COMMODITIES * NODES * NODES: cost[c, n1, n2] * flow[c, n1, n2];

### END OF TEMPLATE ###

# Arc-capacity constraints
subto arc_capacity:
    forall <i> in NODES:
        forall <j> in NODES:
            sum <c> in COMMODITIES: flow[c, i, j] <= capacity[i, j];

# Flow-conservation constraints
subto flow_conservation:
    forall <c> in COMMODITIES:
        forall <j> in NODES:
            sum <i> in NODES: flow[c, i, j] + inflow[c, j] == sum <i> in NODES: flow[c, j, i];
