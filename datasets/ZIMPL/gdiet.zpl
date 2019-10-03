# Based on https://www.gurobi.com/documentation/8.1/examples/diet_py.html by Gurobi Optimization, LLC
#
# Solve the classic diet model, showing how to add constraints
# to an existing model.
#
# Nutrition guidelines, based on
# USDA Dietary Guidelines for Americans, 2005
# http://www.health.gov/DietaryGuidelines/dga2005/


set CAT := {"kcal", "protein", "fat", "sodium"};
param minNutr[CAT] := <"kcal"> 1800, <"protein"> 91, <"fat"> 0, <"sodium"> 0;
param maxNutr[CAT] := <"kcal"> 2200, <"protein"> 1E10, <"fat"> 65, <"sodium"> 1779;

set FOOD := {"hamburger", "chicken", "hot dog", "fries", "macaroni", "pizza", "salad", "milk", "ice cream"};
set DIARY := {"milk", "ice cream"};
# param diaryUB := 6;
param cost[FOOD] := <"hamburger"> 2.49, <"chicken"> 2.89, <"hot dog"> 1.50, <"fries"> 1.89, <"macaroni"> 2.09, <"pizza"> 1.99, <"salad"> 2.49, <"milk"> 0.89, <"ice cream"> 1.59;

# Nutrition values for the foods
param nutr[FOOD * CAT] :=
            |"kcal","protein","fat","sodium"|
|"hamburger"|   410,       24,   26,    730 |
|"chicken"  |   420,       32,   10,   1190 |
|"hot dog"  |   560,       20,   32,   1800 |
|"fries"    |   380,        4,   19,    270 |
|"macaroni" |   320,       12,   10,    930 |
|"pizza"    |   320,       15,   12,    820 |
|"salad"    |   320,       31,   12,   1230 |
|"milk"     |   100,        8,  2.5,    125 |
|"ice cream"|   330,        8,   10,    180 |;

# Create decision variables for the foods to buy
var buy[FOOD] real >= 0;

# The objective is to minimize the costs
minimize cost:
    sum <f> in FOOD: cost[f] * buy[f];

### END OF TEMPLATE ###

# Nutrition constraints
subto nutrLB:
    forall <c> in CAT:
        sum <f> in FOOD: nutr[f, c] * buy[f] >= minNutr[c];

subto nutrUB:
    forall <c> in CAT:
        sum <f> in FOOD: nutr[f, c] * buy[f] <= maxNutr[c];

#subto limitDiary:
#    sum <f> in DIARY: buy[f] <= diaryUB;

