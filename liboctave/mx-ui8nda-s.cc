// DO NOT EDIT -- generated by mk-ops
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Array-util.h"
#include "mx-ui8nda-s.h"
#include "mx-op-defs.h"
#include "boolMatrix.h"
#include "boolNDArray.h"
#include "uint8NDArray.h"
NDS_BIN_OPS (uint8NDArray, uint8NDArray, double)
NDS_CMP_OPS1 (uint8NDArray, , double, , uint8_t)
NDS_BOOL_OPS2 (uint8NDArray, double, octave_uint8::zero, 0.0)
