#ifdef PRECISION
#include "debug.h"

inline void CONCAT(CONCAT(_vector_shift,SIMD_ENGINE), PRECISION) (UNION_TYPE &x, MAIN_TYPE shiftIn, MAIN_TYPE &shiftOut)
{

   IF_256 xlow, xhigh;

   xlow.f = VEC_EXTRACT_256(x.d, 0);
   xhigh.f = VEC_EXTRACT_256(x.d, 1);

   IF_MAIN_TYPE shiftOut0, shiftOut1, shiftOut2;
   IF_MAIN_TYPE shiftOutH,shiftInH;
   
   shiftOut0.i = VEC_EXTRACT_UNIT(xlow.i, SHIFT_CONST1);
   shiftOut1.i = VEC_EXTRACT_UNIT(xlow.i, SHIFT_CONST2);
   shiftOut2.i = VEC_EXTRACT_UNIT(xhigh.i, SHIFT_CONST1);
   shiftOutH.i = VEC_EXTRACT_UNIT(xhigh.i, SHIFT_CONST2); 

   shiftOut = shiftOutH.f;
   shiftInH.f = shiftIn;
   xlow.i = VEC_SHIFT_LEFT(xlow.i, SHIFT_CONST3);
   xhigh.i = VEC_SHIFT_LEFT(xhigh.i, SHIFT_CONST3);
   
   xlow.i = VEC_INSERT_VAL(xlow.i, shiftInH.i, 0);
   xlow.i = VEC_INSERT_VAL(xlow.i, shiftOut0.i, SHIFT_CONST3);
   xhigh.i = VEC_INSERT_VAL(xhigh.i, shiftOut1.i, 0);
   xhigh.i = VEC_INSERT_VAL(xhigh.i, shiftOut2.i, SHIFT_CONST3);
  
   x.d = VEC_INSERT_VEC(x.d, xlow.f, 0);
   x.d = VEC_INSERT_VEC(x.d, xhigh.f, 1);

}

inline void CONCAT(CONCAT(_vector_shift_last,SIMD_ENGINE), PRECISION) (UNION_TYPE &x, MAIN_TYPE shiftIn)
{


   IF_256 xlow, xhigh;

   xlow.f = VEC_EXTRACT_256(x.d, 0);
   xhigh.f = VEC_EXTRACT_256(x.d, 1);

   IF_MAIN_TYPE shiftOut0, shiftOut1, shiftOut2;

   IF_MAIN_TYPE shiftOutH,shiftInH;

   shiftOut0.i = VEC_EXTRACT_UNIT(xlow.i, SHIFT_CONST1);
   shiftOut1.i = VEC_EXTRACT_UNIT(xlow.i, SHIFT_CONST2);
   shiftOut2.i = VEC_EXTRACT_UNIT(xhigh.i, SHIFT_CONST1);

   shiftInH.f = shiftIn;
   xlow.i = VEC_SHIFT_LEFT(xlow.i, SHIFT_CONST3);
   xhigh.i = VEC_SHIFT_LEFT(xhigh.i, SHIFT_CONST3);

   xlow.i = VEC_INSERT_VAL(xlow.i, shiftInH.i, 0);
   xlow.i = VEC_INSERT_VAL(xlow.i, shiftOut0.i, SHIFT_CONST3);
   xhigh.i = VEC_INSERT_VAL(xhigh.i, shiftOut1.i, 0);
   xhigh.i = VEC_INSERT_VAL(xhigh.i, shiftOut2.i, SHIFT_CONST3);

   x.d = VEC_INSERT_VEC(x.d, xlow.f, 0);
   x.d = VEC_INSERT_VEC(x.d, xhigh.f, 1);

}
#endif
