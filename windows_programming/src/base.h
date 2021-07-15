/* date = July 5th 2021 5:22 pm */

#ifndef BASE_H
#define BASE_H

//~ 

#define true  (1)
#define false (0)

#define readonly        const
#define internal        static
#define local_persist   static
#define global          static

#define KILOBYTES(size) (size * 1024)
#define MEGABYTES(size) (KILOBYTES(size) * 1024)
#define GIGABYTES(size) (MEGABYTES(size) * 1024)


//~ ENVIRONMENT INFO
// https:/sourceforge.net/p/predef/wiki/compilers/

/// COMPILER: CLANG
#if defined(__clang__)
#   define COMPILER_CLANG (1)
/// OPERATING SYSTEMS
#   if   defined(_WIN32)
#   define OS_WINDOWS  (1)
#   elif defined(__gnu_linux__)
#   define OS_LINUX    (1)
#   elif defined(__APPLE__) && defined(__MACH__)
#   define OS_MAC      (1)
#   else
#   error missing os detection
#   endif
/// ARCHITECTURES
#   if   defined(__amd64__) 
#   define ARCH_X64    (1)
// TODO(MIGUEL): verify this works for clang
#   elif defined(__i386__) 
#   define ARCH_X86    (1)
#   elif defined(__arm__) 
#   define ARCH_ARM32  (1)
#   elif defined(__aarch64__) 
#   define ARCH_ARM64  (1)
#   else
#   error missing arch detection
#   endif

/// COMPILER: MSVC
#elif   defined(_MSC_VER)  
#   define COMPILER_CL (1)
/// OPERATING SYSTEMS
#   if   defined(_WIN32)
#   define OS_WINDOWS  (1)
#   else
#   error missing os detection
#   endif
/// ARCHITECTURES
#   if   defined(_M_AMD64) 
#   define ARCH_X64    (1)
#   elif defined(_M_I86)
#   define ARCH_X86    (1)
#   elif defined(_M_ARM)
#   define ARCH_ARM32  (1)
#   else
#   error missing arch detection
#   endif

/// COMPILER: GCC
#elif defined(__GNUC__)
#   define COMPILER_GCC (1)
/// OPERATING SYSTEMS
#   if   defined(_WIN32)
#   define OS_WINDOWS  (1)
#   elif defined(__gnu_linux__)
#   define OS_LINUX    (1)
#   elif defined(__APPLE__) && defined(__MACH__)
#   define OS_MAC      (1)
#   else
#   error missing os detection
#   endif
/// ARCHITECTURES
#   if   defined(__amd64__) 
#   define ARCH_X64    (1)
#   elif defined(__i386__) 
#   define ARCH_X86    (1)
#   elif defined(__arm__) 
#   define ARCH_ARM32  (1)
#   elif defined(__aarch64__) 
#   define ARCH_ARM64  (1)
#   else
#   error missing arch detection
#   endif

#else
#   error no context cracking for this compiler
#endif

// NOTE(MIGUEL): zero filling context macros 
#if !defined(COMPILER_CL)
#    define  COMPILER_CL    (0)
#endif
#if !defined(COMPILER_CLANG)
#    define  COMPILER_CLANG (0)
#endif
#if !defined(COMPILER_GCC)
#    define  COMPILER_GCC   (0)
#endif

#if !defined(OS_WINDOWS)
#    define  OS_WINDOWS (0)
#endif
#if !defined(OS_LINUX)
#    define  OS_LINUX   (0)
#endif
#if !defined(OS_MAC)
#    define  OS_MAC     (0)
#endif

#if !defined(ARCH_X64)
#    define  ARCH_X64   (0)
#endif
#if !defined(ARCH_X86)
#    define  ARCH_X86   (0)
#endif
#if !defined(ARCH_ARM32)
#    define  ARCH_ARM32 (0)
#endif
#if !defined(ARCH_ARM64)
#    define  ARCH_ARM64 (0)
#endif

//~ HELPER MACROS
#if !defined(ENABLE_ASSERT)
#define ENABLE_ASSERT
#endif


#define STMNT(statement) do{ statement }while(0)


#if !defined(ASSERT_BREAK )
#define ASSERT_BREAK() (*(int *)0x00 = 0)
#endif

#ifdef ENABLE_ASSERT
#define ASSERT(expression) STMNT(if (!(expression)){ASSERT_BREAK();})
#else
#define ASSERT(expression)
#endif

#define STRINGIFY_(string) #string
#define STRINGIFY(string)  STRINGIFY_(string)

#define GLUE_(A, B) A##B
#define GLUE(A, B) GLUE_(A, B)

#define ARRAY_COUNT(array) (sizeof(array) / sizeof(*(array)))

#define INT_FROM_PTR(pointer) (unsigned long long)((char *)pointer - (char *)0x00)
#define PTR_FROM_INT(integer) (            void *)((char *)0x00    + (integer   ))

#define MEMBER(type, member) (((type *)0x00)->member)
#define MEMBER_OFFSET(type, member) INT_FROM_PTR(&MEMBER(type, member))

#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))
#define CLAMP(a, x, b) (((x)<(a)) ?(a): \
((b)<(x)) ?(h):(x))

#define CLAMPTOP(a, b) MIN(a, b)
#define CLAMPBOT(a, b) MAX(a, b)

#include <string.h>
#define MEMORY_ZERO(pointer, size) memset((pointer), 0, (size))
#define MEMORY_ZERO_STRUCT(pointer)       MEMORY_ZERO((pointer), sizeof(*(pointer)))
#define MEMORY_ZERO_ARRAY(pointer)        MEMORY_ZERO((pointer), sizeof(  pointer))
#define MEMORY_ZERO_TYPED(pointer, count) MEMORY_ZERO((pointer), sizeof(*(pointer)) * (count))

#define MEMORY_MATCH(a, b, size) memcmp((a),(b),(size)) == 0

#define MEMORY_COPY(destination, source, size) memmove((destination),(source),(size))
#define MEMORY_COPY_STRUCT(destination, source)        MEMORY_COPY((destination), (source), \
MIN(sizeof(*(destination)), sizeof(*(source))))

#define MEMORY_COPY_ARRAY(destination, source)         MEMORY_COPY((destination), (source), \
MIN(sizeof(destination), sizeof(source)))

#define MEMORY_COPY_TYPED(destination, source, count)  MEMORY_COPY((destination), (source), \
MIN(sizeof(*(destination)), sizeof(*(source))) * (count))

//~ BASIC TYPES


#include <stdint.h>
#define NULLPTR       ((void *)0x00)

typedef size_t   memory_index;

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

typedef void VoidFunc(void);


//~ BASIC CONSTANTS

#include "base.c"

global s8  min_s8  = (s8 )0x80;
global s16 min_s16 = (s16)0x8000;
global s32 min_s32 = (s32)0x80000000;
global s64 min_s64 = (s64)0x8000000000000000llu;

global s8  max_s8  = (s8 )0x7f;
global s16 max_s16 = (s16)0x7fff;
global s32 max_s32 = (s32)0x7fffffff;
global s64 max_s64 = (s64)0x7fffffffffffffffllu;

global u8  max_u8  = (u8 )0xff;
global u16 max_u16 = (u16)0xffff;
global u32 max_u32 = (u32)0xffffffff;
global u64 max_u64 = (u64)0xffffffffffffffffllu;

global f32 machine_epsilon_f32 = 1.1920929e-7f;
global f32 e_f32          = 2.71828182846f;
global f32 pi_f32         = 3.141592265359f;
global f32 tau_f32        = 6.28318530718f;
global f32 gold_big_f32   = 1.61803398875f;
global f32 gold_small_f32 = 0.61803398875f;

global f64 machine_epsilon_f64 = 2.220446e-7;
global f64 e_f64          = 2.71828182846;
global f64 pi_f64         = 3.141592265359;
global f64 tau_f64        = 6.28318530718;
global f64 gold_big_f64   = 1.61803398875;
global f64 gold_small_f64 = 0.61803398875;

//~ SYMBOLIC CONSTANT

typedef enum Axis Axis;
enum Axis
{
    Axis_x,
    Axis_y,
    Axis_z,
    Axis_w,
}; 

//~ BASIC CONSTANT FUNCTIONS

internal f32 f32_infinity(void);
internal f32 f32_infinity_negative(void);

internal f64 f64_infinity(void);
internal f64 f64_infinity_negative(void);

//~ COMPOUND TYPES

/// VECTORS
typedef union V2s32 V2s32;
union V2s32
{
    struct
    {
        s32 x;
        s32 y;
    };
    s32 v[2];
};

typedef union V2f32 V2f32;
union V2f32
{
    struct
    {
        f32 x;
        f32 y;
    };
    f32 v[2];
};

typedef union V3f32 V3f32;
union V3f32
{
    struct
    {
        f32 x;
        f32 y;
        f32 z;
    };
    f32 v[3];
};

typedef union V4f32 V4f32;
union V4f32
{
    struct
    {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    };
    f32 v[4];
};

/// INTERVALS
typedef union I1f32 I1f32;
union I1f32
{
    struct
    {
        f32 min;
        f32 max;
    };
    f32 v[2];
};

typedef union I1u64 I1u64;
union I1s64
{
    struct
    {
        u64 min;
        u64 max;
    };
    struct
    {
        u64 first;
        u64 opl;
    };
    u64 v[2];
};

typedef union I2s32 I2s32;
union I2s32
{
    struct
    {
        V2s32 min;
        V2s32 max;
    };
    struct
    {
        V2s32 p0;
        V2s32 p1;
    };
    struct
    {
        s32 x0;
        s32 y0;
        s32 x1;
        s32 y1;
    };
    V2s32 p[2];
    s32   v[4];
};

typedef union I2f32 I2f32;
union I2f32
{
    struct
    {
        V2f32 min;
        V2f32 max;
    };
    struct
    {
        V2f32 p0;
        V2f32 p1;
    };
    struct
    {
        f32 x0;
        f32 y0;
        f32 x1;
        f32 y1;
    };
    V2f32 p[2];
    f32   v[4];
};

/// VECTOR FUNCIONS
internal void V2s32_init    (V2s32  *this, s32 x, s32 y);
internal void V2s32_scale   (s32   scalar, V2s32 b, V2s32 *dest);
internal void V2s32_add     (V2s32      a, V2s32 b, V2s32 *dest);
internal void V2s32_sub     (V2s32      a, V2s32 b, V2s32 *dest);
internal void V2s32_dot     (V2s32      a, V2s32 b, V2s32 *dest);
internal void V2s32_cross   (V2s32      a, V2s32 b, V2s32 *dest);
internal void V2s32_hadamard(V2s32      a, V2s32 b, V2s32 *dest);

internal void V2f32_init    (V2f32  *this, f32 x, f32 y);
internal void V2f32_scale   (f32   scalar, V2f32 b, V2f32 *dest);
internal void V2f32_add     (V2f32      a, V2f32 b, V2f32 *dest);
internal void V2f32_sub     (V2f32      a, V2f32 b, V2f32 *dest);
internal void V2f32_dot     (V2f32      a, V2f32 b, V2f32 *dest);
internal void V2f32_cross   (V2f32      a, V2f32 b, V2f32 *dest);
internal void V2f32_hadamard(V2f32      a, V2f32 b, V2f32 *dest);

internal void V3f32_init    (V3f32  *this, f32 x, f32 y, f32 z);
internal void V3f32_scale   (f32   scalar, V3f32 b, V3f32 *dest);
internal void V3f32_add     (V3f32      a, V3f32 b, V3f32 *dest);
internal void V3f32_sub     (V3f32      a, V3f32 b, V3f32 *dest);
internal void V3f32_dot     (V3f32      a, V3f32 b, V3f32 *dest);
internal void V3f32_cross   (V3f32      a, V3f32 b, V3f32 *dest);
internal void V3f32_hadamard(V3f32      a, V3f32 b, V3f32 *dest);

internal void V4f32_init    (V4f32  *this, f32 x, f32 y, f32 z, f32 w);
internal void V4f32_scale   (f32   scalar, V4f32 b, V4f32 *dest);
internal void V4f32_add     (V4f32      a, V4f32 b, V4f32 *dest);
internal void V4f32_fub     (V4f32      a, V4f32 b, V4f32 *dest);
internal void V4f32_dot     (V4f32      a, V4f32 b, V4f32 *dest);
internal void V4f32_cross   (V4f32      a, V4f32 b, V4f32 *dest);
internal void V4f32_hadamard(V4f32      a, V4f32 b, V4f32 *dest);

/// INTERVALS FUNCTIONS
internal void I1f32_init      (I1f32 *this, f32 min, f32 max);
internal b32  I1f32_overlaps  (I1f32 a, I1f32 b);
internal b32  I1f32_contains  (I1f32 a, I1f32 b);
internal b32  I1f32_center    (I1f32 a, I1f32 b);
internal b32  I1f32_dimensions(I1f32 a, I1f32 b);

internal void I1u64_init      (I1u64 *this, u64 min, u64 max);
internal u64  I1u64_dimensions(I1u64 a, I1u64 b);

internal void I2s32_init();
internal b32  I2s32_overlaps(I2s32 a, I2s32 b, I2s32 *dest);
internal b32  I2s32_contains(I2s32 a, I2s32 b);

internal I2f32_init();
internal b32  I2f32_overlaps  (I1f32 a, I1f32 b);
internal b32  I2f32_contains  (I1f32 a, I1f32 b);
internal b32  I2f32_center    (I1f32 a, I1f32 b);
internal f32  I2f32_dimensions(I1f32 a, I1f32 b);



//~ MATH FUNCTIONS

internal f32 f32_sqrt(f32 x);
internal f32 f32_sin (f32 x);
internal f32 f32_cos (f32 x);
internal f32 f32_tan (f32 x);
internal f32 f32_ln  (f32 x);

internal f64 f64_sqrt(f64 x);
internal f64 f64_sin (f64 x);
internal f64 f64_cos (f64 x);
internal f64 f64_ln  (f64 x);

internal f32 lerp  (f32 a, f32 b, f32 t);
internal f32 unlerp(f32 a ,f32 b, f32 x);

#endif //BASE_H

