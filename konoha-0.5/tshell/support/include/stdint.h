#ifndef _DEFINE_H_STDINT_
#define _DEFINE_H_STDINT_

#include <basic.h>

typedef W  int32_t;
typedef H  int16_t;
typedef B  int8_t;
typedef UW uint32_t;
typedef UH uint16_t;
typedef UB uint8_t;

/* Definitions below relies on the fact that the target is 32-bit CPU */
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
typedef W intptr_t;
typedef UW uintptr_t;

#endif /* _DEFINE_H_STDINT_ */
