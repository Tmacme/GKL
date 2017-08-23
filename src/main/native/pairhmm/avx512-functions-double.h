#ifdef PRECISION
#undef PRECISION
#undef MAIN_TYPE
#undef MAIN_TYPE_SIZE
#undef UNION_TYPE
#undef IF_128
#undef IF_MAIN_TYPE
#undef SHIFT_CONST1
#undef SHIFT_CONST2
#undef SHIFT_CONST3
#undef _128_TYPE
#undef SIMD_TYPE
#undef AVX_LENGTH
#undef HAP_TYPE
#undef MASK_TYPE
#undef MASK_ALL_ONES
#undef IF_256
#undef _256_TYPE

#undef SET_VEC_ZERO
#undef VEC_OR
#undef VEC_ADD
#undef VEC_SUB
#undef VEC_MUL
#undef VEC_DIV
#undef VEC_BLEND
#undef VEC_BLENDV
#undef VEC_CAST_256_128
#undef VEC_EXTRACT_128
#undef VEC_EXTRACT_UNIT
#undef VEC_SET1_VAL128
#undef VEC_MOVE
#undef VEC_CAST_128_256
#undef VEC_INSERT_VAL
#undef VEC_CVT_128_256
#undef VEC_SET1_VAL
#undef VEC_POPCVT_CHAR
#undef VEC_LDPOPCVT_CHAR
#undef VEC_CMP_EQ
#undef VEC_SET_LSE
#undef SHIFT_HAP
#undef MASK_VEC
#undef VEC_SSE_TO_AVX
#undef VEC_SHIFT_LEFT_1BIT
#undef MASK_ALL_ONES
#undef COMPARE_VECS
#undef _256_INT_TYPE
#undef BITMASK_VEC
#undef VEC_EXTRACT_256
#undef VEC_INSERT_VEC
#undef VEC_SHIFT_LEFT
#endif

#define PRECISION d
#define MAIN_TYPE double
#define MAIN_TYPE_SIZE 64
#define UNION_TYPE mix_D256
#define IF_128 IF_128d
#define IF_256 IF_256d
#define IF_MAIN_TYPE IF_64
#define SHIFT_CONST1 1
#define SHIFT_CONST2 3
#define SHIFT_CONST3 2
#define _128_TYPE __m128d
#define SIMD_TYPE __m512d
#define _256_INT_TYPE __m256i
#define _256_TYPE __m256d
#define AVX_LENGTH 8 
#define HAP_TYPE __m128i
#define MASK_TYPE uint64_t
#define MASK_ALL_ONES 0xFFFFFFFFFFFFFFFF
#define MASK_VEC MaskVec_D256

#define SET_VEC_ZERO(__vec)                     \
    __vec= _mm512_setzero_pd()

#define VEC_OR(__v1, __v2)                      \
    _mm512_or_pd(__v1, __v2)

#define VEC_ADD(__v1, __v2)                     \
    _mm512_add_pd(__v1, __v2)

#define VEC_SUB(__v1, __v2)                     \
    _mm512_sub_pd(__v1, __v2)

#define VEC_MUL(__v1, __v2)                     \
    _mm512_mul_pd(__v1, __v2)

#define VEC_DIV(__v1, __v2)                     \
    _mm512_div_pd(__v1, __v2)

#define VEC_BLEND(__v1, __v2, __mask)           \
    _mm256_blend_pd(__v1, __v2, __mask)

#define VEC_BLENDV(__v1, __v2, __mask)      \
    _mm256_blendv_pd(__v1, __v2, __mask)

#define VEC_CAST_256_128(__v1)                  \
    _mm512_castpd512_pd128 (__v1)

#define VEC_EXTRACT_256(__v1, __im)             \
    _mm512_extractf64x4_pd (__v1, __im)

#define VEC_EXTRACT_UNIT(__v1, __im)            \
    _mm256_extract_epi32(__v1, __im)

#define VEC_SET1_VAL128(__val)                  \
    _mm_set1_pd(__val)

#define VEC_MOVE(__v1, __val)                   \
    _mm_move_sd(__v1, __val)

#define VEC_CAST_128_256(__v1)                  \
    _mm512_castpd128_pd128(__v1)

#define VEC_INSERT_VAL(__v1, __val, __pos)      \
    _mm256_insert_epi64(__v1, __val, __pos)

#define VEC_INSERT_VEC(__v1, __v2, __pos)     \
     _mm512_insertf64x4(__v1, __v2, __pos)

#define VEC_CVT_128_256(__v1)                   \
    _mm512_cvtepi32_pd(__v1)

#define VEC_SET1_VAL(__val)                     \
    _mm512_set1_pd(__val)

#define VEC_POPCVT_CHAR(__ch)                   \
    _mm512_cvtepi32_pd(_mm256_set1_epi32(__ch))

#define VEC_LDPOPCVT_CHAR(__addr)               \
    _mm512_cvtepi32_pd(_mm256_load_si256((__m256i const *)__addr))

#define VEC_CMP_EQ(__v1, __v2)                  \
    _mm512_cmp_pd(__v1, __v2, _CMP_EQ_OQ)

#define VEC_SET_LSE(__val)                      \
    _mm512_set_pd(zero, zero, zero, zero, zero, zero, zero, __val);

#define SHIFT_HAP(__v1, __val)                  \
    __v1 = _mm_insert_epi32(_mm_slli_si128(__v1, 4), __val.i, 0)

#define VEC_SSE_TO_AVX(__vsLow, __vsHigh, __vdst)       \
    __vdst = _mm512_castpd256_pd512(__vsLow) ;            \
__vdst = _mm512_insertf64x4(__vdst, __vsHigh, 1) ;

#define VEC_SHIFT_LEFT_1BIT(__vs)               \
    __vs = _mm256_slli_epi64(__vs, 1)

#define VEC_SHIFT_LEFT(__vs, __val)        \
    __vs = _mm256_slli_si256(__vs, __val)


#define COMPARE_VECS(__v1, __v2, __first, __last) {                     \
    double* ptr1 = (double*) (&__v1) ;                                  \
    double* ptr2 = (double*) (&__v2) ;                                  \
    for (int ei=__first; ei <= __last; ++ei) {                          \
        if (ptr1[ei] != ptr2[ei]) {                                       \
            std::cout << "Double Mismatch at " << ei << ": "                \
            << ptr1[ei] << " vs. " << ptr2[ei] << std::endl ;     \
            exit(0) ;                                                       \
        }                                                                 \
    }                                                                   \
}

class BitMaskVec_double {

    MASK_VEC low_, high_ ;
    SIMD_TYPE combined_ ;

    public:
    inline MASK_TYPE& getLowEntry(int index) {
        return low_.masks[index] ;
    }
    inline MASK_TYPE& getHighEntry(int index) {
        return high_.masks[index] ;
    }

    inline const _256_TYPE getLowVec() {
        return low_.vecf;
    }

     inline const _256_TYPE getHighVec() {
        return high_.vecf;
    }


    inline const SIMD_TYPE& getCombinedMask() {
        VEC_SSE_TO_AVX(low_.vecf, high_.vecf, combined_) ;
        return combined_ ;
    }

    inline void shift_left_1bit() {
        VEC_SHIFT_LEFT_1BIT(low_.vec) ;
        VEC_SHIFT_LEFT_1BIT(high_.vec) ;
    }

} ;

#define BITMASK_VEC BitMaskVec_double
