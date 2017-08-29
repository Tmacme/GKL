#ifdef PRECISION
#include "debug.h"

inline void CONCAT(CONCAT(_vector_shift,SIMD_ENGINE), PRECISION) (UNION_TYPE &x, MAIN_TYPE shiftIn, MAIN_TYPE &shiftOut)
{

    IF_256 xhigh;  
    IF_MAIN_TYPE shiftOutH,shiftInH;
 xhigh.f = VEC_EXTRACT_256(x.d, 1); 
shiftOutH.i = VEC_EXTRACT_UNIT(xhigh.i, SHIFT_CONST2); 
 shiftOut = shiftOutH.f;  
    _512_INT_TYPE idx = VEC_SET1();
    x.i = VEC_PERMUTE(idx,x.i);
//    shiftOutH.f = _mm512_cvtss_f32(x.d);
    idx = VEC_SET2(); 
    x.i = VEC_AND(x.i, idx);
    shiftInH.f = shiftIn; 
    idx = VEC_SET3(shiftInH.i);
    x.i = VEC_OR(x.i, idx);    
       
/*
    IF_256 xlow, xhigh;  
    xlow.f = VEC_EXTRACT_256(x.d, 0); 
    IF_MAIN_TYPE shiftOut0, shiftOut1, shiftOut2;
    xhigh.f = VEC_EXTRACT_256(x.d, 1); 
     
    shiftOut0.i = VEC_EXTRACT_UNIT(xlow.i, SHIFT_CONST1); 
    IF_MAIN_TYPE shiftOutH,shiftInH;
   shiftOut1.i = VEC_EXTRACT_UNIT(xlow.i, SHIFT_CONST2); 

    shiftInH.f = shiftIn; 

    shiftOut2.i = VEC_EXTRACT_UNIT(xhigh.i, SHIFT_CONST1); 

    xlow.i = VEC_SHIFT_LEFT(xlow.i, SHIFT_CONST3);

    shiftOutH.i = VEC_EXTRACT_UNIT(xhigh.i, SHIFT_CONST2);  
 
    xhigh.i = VEC_SHIFT_LEFT(xhigh.i, SHIFT_CONST3); 
     
    xlow.i = VEC_INSERT_VAL(xlow.i, shiftInH.i, 0); 
    xlow.i = VEC_INSERT_VAL(xlow.i, shiftOut0.i, SHIFT_CONST3); 
    shiftOut = shiftOutH.f;  

    xhigh.i = VEC_INSERT_VAL(xhigh.i, shiftOut1.i, 0); 
    xhigh.i = VEC_INSERT_VAL(xhigh.i, shiftOut2.i, SHIFT_CONST3); 
    
    x.d = VEC_INSERT_VEC(x.d, xlow.f, 0); 
    x.d = VEC_INSERT_VEC(x.d, xhigh.f, 1); 

*/
//-----------------------
/*-

   IF_256 xlow, xhigh; 
 
    xhigh.f = VEC_EXTRACT_256(x.d, 1); 
    xlow.f = VEC_EXTRACT_256(x.d, 0);
 

IF_MAIN_TYPE shiftOut0, shiftOut1, shiftOut2; 
     
    shiftOut0.i = VEC_EXTRACT_UNIT(xlow.i, SHIFT_CONST1); 
    shiftOut1.i = VEC_EXTRACT_UNIT(xlow.i, SHIFT_CONST2); 
    shiftOut2.i = VEC_EXTRACT_UNIT(xhigh.i, SHIFT_CONST1); 
    IF_MAIN_TYPE shiftOutH,shiftInH; 
    shiftOutH.i = VEC_EXTRACT_UNIT(xhigh.i, SHIFT_CONST2); 
  
    shiftOut = shiftOutH.f; 
    shiftInH.f = shiftIn; 
    
    UNION_TYPE xtemp1;

    xtemp1.i = VEC_BSHIFT_LEFT(x.i, SHIFT_CONST4);
  
    xlow.f = VEC_EXTRACT_256(xtemp1.d, 0);

    xhigh.i = VEC_EXTRACT_256(xtemp2.d, 0);
    shiftOutH.i = VEC_EXTRACT_UNIT(xhigh.i, SHIFT_CONST3);

    xlow.i = VEC_INSERT_VAL(xlow.i, shiftInH.i, 0); 
    
    xtemp1.d = VEC_INSERT_VEC(xtemp1.d, xlow.f, 0);
  */ 

}

inline void CONCAT(CONCAT(_vector_shift_last,SIMD_ENGINE), PRECISION) (UNION_TYPE &x, MAIN_TYPE shiftIn)
{
/*

IF_256 xlow, xhigh;


    xhigh.f = VEC_EXTRACT_256(x.d, 1);


    IF_MAIN_TYPE shiftInH;

    shiftInH.f = shiftIn;

    UNION_TYPE xtemp;

    xtemp.i = VEC_BSHIFT_LEFT(x.i, SHIFT_CONST4);

    x.i = VEC_BSHIFT_RIGHT(x.i, SHIFT_CONST5);

    xlow.f = VEC_EXTRACT_256(xtemp.d, 0);

    xlow.i = VEC_INSERT_VAL(xlow.i, shiftInH.i, 0);

    xtemp.d = VEC_INSERT_VEC(xtemp.d, xlow.f, 0);

    x.d = VEC_XOR(xtemp.d, x.d);
*/
//-------------
    IF_MAIN_TYPE shiftInH;
    _512_INT_TYPE idx = _mm512_set_epi32(14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,15);
    x.i = VEC_PERMUTE(idx,x.i);
//    shiftOutH = _mm512_cvtss_f32(x.d);
    idx = _mm512_set_epi32(0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0x0);
    x.i = _mm512_and_epi32(x.i, idx);
    shiftInH.f = shiftIn;
    idx = _mm512_set_epi32(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,shiftInH.i);
    x.i = _mm512_or_epi32(x.i, idx);


/*
   IF_256 xlow, xhigh;

   xlow.f = VEC_EXTRACT_256(x.d, 0);
   xhigh.f = VEC_EXTRACT_256(x.d, 1);

   IF_MAIN_TYPE shiftOut0, shiftOut1, shiftOut2;

   IF_MAIN_TYPE shiftInH;

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
*/
}
#endif
