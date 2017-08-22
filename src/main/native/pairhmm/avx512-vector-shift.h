#ifdef PRECISION
#include "debug.h"

inline void CONCAT(CONCAT(_vector_shift,SIMD_ENGINE), PRECISION) (UNION_TYPE &x, MAIN_TYPE shiftIn, MAIN_TYPE &shiftOut)
{

   IF_256f xlow, xhigh;

   xlow.f = _mm512_extractf32x8_ps(x.d, 0);
   xhigh.f = _mm512_extractf32x8_ps(x.d, 1);


   IF_MAIN_TYPE shiftOut0, shiftOut1, shiftOut2;
   shiftOut0.i = _mm256_extract_epi32(xlow.i,3);

   shiftOut1.i = _mm256_extract_epi32(xlow.i,7);
   shiftOut2.i = _mm256_extract_epi32(xhigh.i,3);
   IF_MAIN_TYPE shiftOutH,shiftInH;
    shiftOutH.i =_mm256_extract_epi32 (xhigh.i, 7);
    shiftOut = shiftOutH.f;
   shiftInH.f = shiftIn;


   xlow.i = _mm256_slli_si256(xlow.i,4 );
   xhigh.i = _mm256_slli_si256(xhigh.i,4 );
   
   xlow.i = _mm256_insert_epi32(xlow.i, shiftInH.i, 0);
   xlow.i = _mm256_insert_epi32(xlow.i, shiftOut0.i,4);
   xhigh.i = _mm256_insert_epi32(xhigh.i, shiftOut1.i,0);
   xhigh.i = _mm256_insert_epi32(xhigh.i, shiftOut2.i,4); 
   
   x.d = _mm512_insertf32x8(x.d, xlow.f, 0);
   x.d = _mm512_insertf32x8(x.d, xhigh.f, 1);

  
   
   

   //for(int i=0;i<16;i++) DBG("IN %f", x.f[i]);
    //IF_128 xlowl , xlowh, xhighl, xhighh ;
    /* cast x to xlowll */
    //xlowl.f = VEC_EXTRACT_128(x.d,0);
    /* extract x,1 to xhighh */
   // xhighh.f = VEC_EXTRACT_128(x.d, 3);
    /* extract x,3, to xlowlh */
   // xlowh.f = VEC_EXTRACT_128(x.d, 1);
    /* extract x,2 to xhighl */
   // xhighl.f = VEC_EXTRACT_128(x.d, 2);

    /* extract xlowl[3] */
   // IF_128 shiftOutL128;
    //shiftOutL128.i = _mm_srli_si128(xlowl.i, SHIFT_CONST1);
    /* extract xhighh[3] */
    //IF_MAIN_TYPE shiftOutH;
    //shiftOutH.i = VEC_EXTRACT_UNIT(xhighh.i, SHIFT_CONST2);
    //shiftOut = shiftOutH.f;

    //IF_128 Shift1, Shift2;
    //Shift1.i = _mm_srli_si128(xlowh.i, SHIFT_CONST1);
    //Shift2.i = _mm_srli_si128(xhighl.i, SHIFT_CONST1);

   // xlowl.i = _mm_slli_si128 (xlowl.i, SHIFT_CONST3);
    /* shift xhigh */
   // xhighh.i = _mm_slli_si128 (xhighh.i, SHIFT_CONST3);

   // xlowh.i = _mm_slli_si128(xlowh.i, SHIFT_CONST3);
   // xhighl.i = _mm_slli_si128(xhighl.i, SHIFT_CONST3); 

    /*movss shiftIn to xlow[0] */
   // _128_TYPE shiftIn128 = VEC_SET1_VAL128(shiftIn);
   // xlowl.f = VEC_MOVE(xlowl.f , shiftIn128);

   // xlowh.f = VEC_MOVE(xlowh.f, shiftOutL128.f);
   // xhighl.f = VEC_MOVE(xhighl.f, Shift1.f);
    /*movss xlow[3] to xhigh[0] */
   // xhighh.f = VEC_MOVE(xhighh.f, Shift2.f);
    
    /* cast xlow to x */
   // x.d = VEC_INSERT_VAL(x.d, xlowl.f,0);
   // x.d = VEC_INSERT_VAL(x.d, xlowh.f, 1);

    /* insert xhigh to x,1 */
   // x.d = VEC_INSERT_VAL(x.d, xhighh.f,3 );
   // x.d = VEC_INSERT_VAL(x.d, xhighl.f, 2);
 //for(int i=0;i<16;i++) DBG("OUT %f", x.f[i]);
}


inline void CONCAT(CONCAT(_vector_shift_last,SIMD_ENGINE), PRECISION) (UNION_TYPE &x, MAIN_TYPE shiftIn)
{


   IF_256f xlow, xhigh;

   xlow.f = _mm512_extractf32x8_ps(x.d, 0);
   xhigh.f = _mm512_extractf32x8_ps(x.d, 1);


   IF_MAIN_TYPE shiftOut0, shiftOut1, shiftOut2;
   shiftOut0.i = _mm256_extract_epi32(xlow.i,3);

   shiftOut1.i = _mm256_extract_epi32(xlow.i,7);
   shiftOut2.i = _mm256_extract_epi32(xhigh.i,3);
//   IF_MAIN_TYPE shiftOutH;
  //  shiftOutH.i =_mm256_extract_epi32 (xhigh.i, 7);
   // shiftOut = shiftOutH.f;

    IF_MAIN_TYPE shiftInH;

   shiftInH.f = shiftIn;
   xlow.i = _mm256_slli_si256(xlow.i,4 );
   xhigh.i = _mm256_slli_si256(xhigh.i,4 );

   xlow.i = _mm256_insert_epi32(xlow.i, shiftInH.i, 0);
   xlow.i = _mm256_insert_epi32(xlow.i, shiftOut0.i,4);
   xhigh.i = _mm256_insert_epi32(xhigh.i, shiftOut1.i,0);
   xhigh.i = _mm256_insert_epi32(xhigh.i, shiftOut2.i,4);

   x.d = _mm512_insertf32x8(x.d, xlow.f, 0);
   x.d = _mm512_insertf32x8(x.d, xhigh.f, 1);


//    for(int i=0;i<16;i++) DBG("IN %f", x.f[i]);
   // IF_128 xlowl , xlowh, xhighl, xhighh;
    /* cast x to xlow */
   // xlowl.f = VEC_CAST_256_128(x.d);
    /* extract x,1 to xhigh */
   // xhighh.f = VEC_EXTRACT_128(x.d, 3);
    /* extract x,3, to xlowlh */
   // xlowh.f = VEC_EXTRACT_128(x.d,1 );
    /* extract x,2 to xhighl */
   // xhighl.f = VEC_EXTRACT_128(x.d,2 );
    /* extract xlow[3] */
    
   // IF_128 shiftOutL128;
   // shiftOutL128.i = _mm_srli_si128(xlowl.i, SHIFT_CONST1);
    /*movss shiftIn to xlow[0] */
   // _128_TYPE shiftIn128 = VEC_SET1_VAL128(shiftIn);

   // IF_128 Shift1, Shift2;
   // Shift1.i = _mm_srli_si128(xlowh.i, SHIFT_CONST1);
   // Shift2.i = _mm_srli_si128(xhighl.i, SHIFT_CONST1);


    //xlowh.i = _mm_slli_si128(xlowh.i, SHIFT_CONST3);
    //xhighl.i = _mm_slli_si128(xhighl.i, SHIFT_CONST3);

    //xlowl.i = _mm_slli_si128 (xlowl.i, SHIFT_CONST3);
    /* shift xhigh */
    //xhighh.i = _mm_slli_si128 (xhighh.i, SHIFT_CONST3);
    //xlowl.f = VEC_MOVE(xlowl.f , shiftIn128);
    /*movss xlow[3] to xhigh[0] */
    //xlowh.f = VEC_MOVE(xlowh.f, shiftOutL128.f);

     //xhighl.f = VEC_MOVE(xhighl.f, Shift1.f);
    /*movss xlow[3] to xhigh[0] */
   // xhighh.f = VEC_MOVE(xhighh.f, Shift2.f);

    /* cast xlow to x */
 //x.d = VEC_INSERT_VAL(x.d, xlowl.f,0);
    /* insert xhigh to x,1 */
   // x.d = VEC_INSERT_VAL(x.d, xhighh.f, 3);
   // x.d = VEC_INSERT_VAL(x.d, xhighl.f, 2);
   // x.d = VEC_INSERT_VAL(x.d, xlowh.f, 1);
//for(int i=0;i<16;i++) DBG("OUT %f", x.f[i]);
}

#endif
