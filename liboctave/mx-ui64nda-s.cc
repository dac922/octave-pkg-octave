// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-ui64nda-s.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "uint64NDArray.h"
NDS_BIN_OPS (uint64NDArray, uint64NDArray, double)
NDS_CMP_OPS1 (uint64NDArray, , double, , uint64_t)
NDS_BOOL_OPS2 (uint64NDArray, double, octave_uint64::zero, 0.0)
