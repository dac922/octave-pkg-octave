// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-fnda-fcnda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "fCNDArray.h"
#include "fNDArray.h"
NDND_BIN_OPS (FloatComplexNDArray, FloatNDArray, FloatComplexNDArray)
NDND_CMP_OPS (FloatNDArray, , FloatComplexNDArray, real)
NDND_BOOL_OPS2 (FloatNDArray, FloatComplexNDArray, static_cast<float>(0.0), static_cast<float>(0.0))
