set N := {1 to 5};
set K := {1 to 2};
param d := 2.7;
# param M := 1e6;
param slope1 := 3.7320508076; # cot(pi/12)
param slope2 := 0.2679491924; # tan(pi/12)

var x[N] real >= -1 <= 2 * max(K) + d;
var b[K] binary;

### END OF TEMPLATE ###

# subto plane1:
#    forall <j> in K:
#        forall <i> in N:
#            forall <l> in N with i < l:
#                x[i] * slope1 - x[l] * slope2 + 1e6 * (1 - b[j]) >= 2 * j - 2;

subto plane1:
    forall <j> in K:
        forall <i> in N:
            forall <l> in N with i < l:
                vif b[j] == 1 then x[i] * slope1 - x[l] * slope2 >= 2 * j - 2 end;


# subto plane2:
#     forall <j> in K:
#        forall <i> in N:
#            forall <l> in N with i < l:
#                x[l] * slope1 - x[i] * slope2 + 1e6 * (1 - b[j]) >= 2 * j - 2;

subto plane2:
    forall <j> in K:
        forall <i> in N:
            forall <l> in N with i < l:
                vif b[j] == 1 then x[l] * slope1 - x[i] * slope2 >= 2 * j - 2 end;


# subto plane3:
#     forall <j> in K:
#         sum <i> in N: x[i] - 1e6 * (1 - b[j]) <= j * d;

subto plane3:
    forall <j> in K:
        vif b[j] == 1 then sum <i> in N: x[i] <= j * d end;


subto altenative:
    sum <j> in K: b[j] >= 1;
