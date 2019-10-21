from libc.math cimport fabs
from libc.math cimport log
cimport cython

@cython.initializedcheck(False)
@cython.boundscheck(False)
@cython.wraparound(False)
@cython.cdivision(True)
@cython.embedsignature(True)
def precision(const double[:, :] Xv, const double[:, :] Pv):
    cdef double threshold = Xv.shape[1] / log(Xv.shape[0])
    cdef int i, j, k
    cdef int tp = 0
    cdef double denominator
    cdef double sum
    range_j = range(Xv.shape[0])
    range_k = range(Xv.shape[1])
    for i in range(Pv.shape[0]):
        for j in range_j:
            sum = 0.0
            for k in range_k:
                denominator = fabs(Pv[i, k]) + fabs(Xv[j, k])
                if denominator > 1e-6:
                    sum += fabs(Pv[i, k] - Xv[j, k]) / denominator
            if sum <= threshold:
                tp += 1
                break
    return float(tp) / float(Pv.shape[0])
