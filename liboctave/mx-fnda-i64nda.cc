// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-fnda-i64nda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "int64NDArray.h"
#include "fNDArray.h"
NDND_BIN_OPS (int64NDArray, FloatNDArray, int64NDArray)
NDND_CMP_OPS (FloatNDArray, , int64NDArray, )
NDND_BOOL_OPS2 (FloatNDArray, int64NDArray, static_cast<float>(0.0), octave_int64::zero)
