// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-i64nda-i8nda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "int64NDArray.h"
#include "int8NDArray.h"
NDND_CMP_OPS (int64NDArray, , int8NDArray, )
NDND_BOOL_OPS2 (int64NDArray, int8NDArray, octave_int64::zero, octave_int8::zero)
