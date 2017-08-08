#include <stdint.h>
#include "pairhmm_common.h"
#include "Context.h"

#include "avx-types.h"

#define SIMD_ENGINE avx

#define avx512

#ifdef avx512

#include "avx512-functions-float.h"
#include "avx512-vector-shift.h"
#include "avx-pairhmm-template.h"

//template double compute_full_prob_avxd<double>(testcase* tc);
template float compute_full_prob_avxs<float>(testcase* tc);

#else

#include "avx-functions-float.h"
#include "avx-vector-shift.h"
#include "avx-pairhmm-template.h"

//template double compute_full_prob_avxd<double>(testcase* tc);
template float compute_full_prob_avxs<float>(testcase* tc);
#endif 

//#include "avx-functions-double.h"
//#include "avx-vector-shift.h"
//#include "avx-pairhmm-template.h"

