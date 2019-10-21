set N := {1 to 5};
set K := {1 to 2};
param d := 2.7;
# param M := 1e6;

var x[<i> in N] real >= i - i * max(K) * d <= i + 2 * i * max(K) * d;
var b[<k> in K] binary;

### END OF TEMPLATE ###

# subto LB:
#    forall <j> in K:
#        forall <i> in N:
#            x[i] + 1e6 * (1 - b[j]) >= i * j;

subto LB:
    forall <j> in K:
        forall <i> in N:
            vif b[j] == 1 then x[i] >= i * j end;

#subto UB:
#    forall <j> in K:
#        forall <i> in N:
#            x[i] - 1e6 * (1 - b[j]) <= i * j + i * d;

subto UB:
    forall <j> in K:
        forall <i> in N:
            vif b[j] == 1 then x[i] <= i * j + i * d end;


subto altenative:
    sum <j> in K: b[j] >= 1;