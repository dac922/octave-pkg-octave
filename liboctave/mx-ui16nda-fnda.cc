// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-ui16nda-fnda.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "uint16NDArray.h"
#include "fNDArray.h"
NDND_BIN_OPS (uint16NDArray, uint16NDArray, FloatNDArray)
NDND_CMP_OPS (uint16NDArray, , FloatNDArray, )
NDND_BOOL_OPS2 (uint16NDArray, FloatNDArray, octave_uint16::zero, static_cast<float>(0.0))
