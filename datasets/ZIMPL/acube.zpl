set N := {1 to 5};
set K := {1 to 2};
param d := 2.7;
param M := 1e6;

var x[<i> in N] real >= i - i * max(K) * d <= i + 2 * i * max(K) * d;
var b[<k> in K] binary;

### END OF TEMPLATE ###

subto LB:
    forall <j> in K:
        forall <i> in N:
            x[i] - M * b[j] >= i * j - M;

subto UB:
    forall <j> in K:
        forall <i> in N:
            x[i] + M * b[j] <= i * j + i * d + M;

subto altenative:
    sum <j> in K: b[j] >= 1;

