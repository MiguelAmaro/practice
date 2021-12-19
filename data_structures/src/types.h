/* date = December 13th 2021 1:58 pm */

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#define KILOBYTES(size) (         (size) * 1024LL)
#define MEGABYTES(size) (KILOBYTES(size) * 1024LL)
#define GIGABYTES(size) (MEGABYTES(size) * 1024LL)
#define TERABYTES(size) (GIGABYTES(size) * 1024LL)


#define ASSERT(expression) if(!(expression)){ *(u32 *)0x00 = 0; }
#define ARRAY_COUNT(array) (sizeof(array) / sizeof(array[0]))
#define NULLPTR (void *)0

typedef size_t memory_index;

typedef uint8_t  u8 ;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef  int8_t  s8 ;
typedef  int16_t s16;
typedef  int32_t s32;
typedef  int64_t s64;

typedef  int8_t  b8 ;
typedef  int16_t b16;
typedef  int32_t b32;
typedef  int64_t b64;

typedef float f32;
typedef float f64;


#endif //TYPES_H
