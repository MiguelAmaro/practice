
internal OperatingSystem OperatingSystem_get_from_context(void)
{
    OperatingSystem result = OperatingSystem_null;
    
#if   OS_WINDOWS
    result = OperatingSystem_windows;
#elif OS_LINUX
    result = OperatingSystem_linux;
#elif OS_MAC
    result = OperatingSystem_mac;
#endif
    
    return result;
}

internal Architecture Architecture_get_from_context(void)
{
    Architecture result = Architecture_null;
    
#if   ARCH_X64
    result = Architecture_x64;
#elif ARCH_X86
    result = Architecture_x86;
#elif ARCH_ARM32
    result = Architecture_arm32;
#elif ARCH_ARM64
    result = Architecture_arm64;
#endif
    
    return result;
}


internal u8 *OperatingSystem_get_string(OperatingSystem   os)
{
    u8 *result = "(null)";
    
    switch(os)
    {
        case OperatingSystem_windows:
        {
            result = "windows";
        }break;
        case OperatingSystem_linux:
        {
            result = "linux";
        }break;
        case OperatingSystem_mac:
        {
            result = "mac";
        }break;
    }
    
    return result;
}

internal u8 *   Architecture_get_string(Architecture    arch)
{
    u8 *result = "(null)";
    
    switch(arch)
    {
        case Architecture_x64:
        {
            result = "x64";
        }break;
        case Architecture_x86:
        {
            result = "x86";
        }break;
        case Architecture_arm32:
        {
            result = "arm32";
        }break;
        case Architecture_arm64:
        {
            result = "arm64";
        }break;
    }
    
    return result;
}

internal u8 *        WeekDay_get_string(WeekDay      weekday)
{
    u8 *result = "(null)";
    
    switch(weekday)
    {
        case WeekDay_sunday:
        {
            result = "sunday";
        }break;
        case WeekDay_monday:
        {
            result = "monday";
        }break;
        case WeekDay_tuesday:
        {
            result = "tuesday";
        }break;
        case WeekDay_wednesday:
        {
            result = "wednesday";
        }break;
        
        case WeekDay_thursday:
        {
            result = "thursday";
        }break;
        
        case WeekDay_friday:
        {
            result = "friday";
        }break;
        
        case WeekDay_saturday:
        {
            result = "saturday";
        }break;
    }
    
    return result;
}

internal u8 *          Month_get_string(Month    month)
{
    u8 *result = "(null)";
    
    switch(month)
    {
        case Month_jan:
        {
            result = "jan";
        }break;
        case Month_feb:
        {
            result = "feb";
        }break;
        case Month_mar:
        {
            result = "mar";
        }break;
        case Month_apr:
        {
            result = "apr";
        }break;
        case Month_may:
        {
            result = "may";
        }break;
        case Month_jun:
        {
            result = "jun";
        }break;
        case Month_jul:
        {
            result = "jul";
        }break;
        case Month_aug:
        {
            result = "aug";
        }break;
        case Month_sep:
        {
            result = "sep";
        }break;
        case Month_nov:
        {
            result = "nov";
        }break;
        case Month_dec:
        {
            result = "dec";
        }break;
    }
    
    return result;
}



//~ FLOAT CONSTANT FUNCTIONS
//https:\h-schmidt.net/FloatConverter/IEEE754.html

internal f32
f32_infinity(void)
{
    union
    { 
        f32 f;
        u32 u;
    } r;
    
    r.u = 0x7f800000;
    
    return r.f;
}

internal f32
f32_infinity_negative(void)
{
    union
    { 
        f32 f;
        u32 u;
    } r;
    
    r.u = 0xff800000;
    
    return r.f;
}


internal f64
f64_infinity(void)
{
    union
    { 
        f64 f;
        u64 u;
    } r;
    
    r.u = 0x7ff0000000000000;
    
    return r.f;
}


internal f64
f64_infinity_negative(void)
{
    union
    { 
        f64 f;
        u64 u;
    } r;
    
    r.u = 0xfff0000000000000;
    
    return r.f;
}

internal f32
f32_abs(f32 x)
{
    union
    { 
        f64 f;
        u64 u;
    } r;
    
    r.u &= 0x7fffffff;
    
    return r.f;
}

internal f64
f64_abs(f64 x)
{
    union
    { 
        f64 f;
        u64 u;
    } r;
    
    r.u &= 0x7fffffffffffffff;
    
    return r.f;
}

//~ VECTOR FUNCIONS

internal V2s32 V2s32_init   (s32 x, s32 y)
{
    V2s32 result = { x, y };
    return result;
}

internal void V2s32_scale   (f32   scalar, V2s32 b, V2s32 *dest)
{
    V2s32 result = { (s32)(scalar * b.x), (s32)(scalar * b.y) };
    *dest = result;
    
    return;
}

internal void V2s32_add     (V2s32      a, V2s32 b, V2s32 *dest)
{
    V2s32 result = { a.x + b.x, a.y + b.y };
    *dest = result;
    
    return;
}

internal void V2s32_sub     (V2s32      a, V2s32 b, V2s32 *dest)
{
    V2s32 result = { a.x - b.x, a.y - b.y };
    *dest = result;
    
    return;
}

internal f32  V2s32_dot     (V2s32      a, V2s32 b             )
{
    f32 result = (a.x * b.x) + (a.y * b.y);
    return result;
}

internal void V2s32_cross   (V2s32      a, V2s32 b, V2s32 *dest)
{
    return;
}

internal void V2s32_hadamard(V2s32      a, V2s32 b, V2s32 *dest)
{
    V2s32 result = { a.x * b.x, a.y * b.y };
    *dest = result;
    
    return;
}

//-
internal V2f32 V2f32_init   (f32 x, f32 y)
{
    V2f32 result = { x, y };
    return result;
}

internal void V2f32_scale   (f32   scalar, V2f32 b, V2f32 *dest)
{
    V2f32 result = { scalar * b.x, scalar * b.y };
    *dest = result;
    
    return;
}

internal void V2f32_add     (V2f32      a, V2f32 b, V2f32 *dest)
{
    V2f32 result = { a.x + b.x, a.y + b.y };
    *dest = result;
    
    return;
}

internal void V2f32_sub     (V2f32      a, V2f32 b, V2f32 *dest)
{
    V2f32 result = { a.x - b.x, a.y - b.y };
    *dest = result;
    
    return;
}

internal f32  V2f32_dot     (V2f32      a, V2f32 b             )
{
    f32 result = (a.x * b.x) + (a.y * b.y);
    return result;
}

internal void V2f32_cross   (V2f32      a, V2f32 b, V2f32 *dest)
{
    return;
}

internal void V2f32_hadamard(V2f32      a, V2f32 b, V2f32 *dest)
{
    V2f32 result = { a.x * b.x, a.y * b.y };
    *dest = result;
    
    return;
}

//-
internal V3f32 V3f32_init    (f32 x, f32 y, f32 z)
{
    V3f32 result = { x, y, z };
    return result;
}

internal void V3f32_scale   (f32   scalar, V3f32 b, V3f32 *dest)
{
    V3f32 result = { scalar * b.x, scalar * b.y, scalar * b.z };
    *dest = result;
    
    return;
}

internal void V3f32_add     (V3f32      a, V3f32 b, V3f32 *dest)
{
    V3f32 result = { a.x + b.x, a.y + b.y, a.z + b.z };
    *dest = result;
    
    return;
}

internal void V3f32_sub     (V3f32      a, V3f32 b, V3f32 *dest)
{
    V3f32 result = { a.x - b.x, a.y - b.y, a.z - b.z };
    *dest = result;
    
    return;
}

internal f32  V3f32_dot     (V3f32      a, V3f32 b              )
{
    f32 result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    return result;
}

internal void V3f32_cross   (V3f32      a, V3f32 b, V3f32 *dest)
{
    return;
}

internal void V3f32_hadamard(V3f32      a, V3f32 b, V3f32 *dest)
{
    V3f32 result = { a.x * b.x, a.y * b.y, a.z * b.z };
    *dest = result;
    
    return;
}

internal V4f32 V4f32_init    (f32 x, f32 y, f32 z, f32 w)
{
    V4f32 result = { x, y, z, w };
    return result;
}

internal void V4f32_scale   (f32   scalar, V4f32 b, V4f32 *dest)
{
    V4f32 result = { scalar * b.x, scalar * b.y, scalar * b.z, scalar * b.w };
    *dest = result;
    
    return;
}

internal void V4f32_add     (V4f32      a, V4f32 b, V4f32 *dest)
{
    V4f32 result = { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
    *dest = result;
    
    return;
}

internal void V4f32_sub     (V4f32      a, V4f32 b, V4f32 *dest)
{
    V4f32 result = { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
    *dest = result;
    
    return;
}

internal f32  V4f32_dot     (V4f32      a, V4f32 b             )
{
    f32 result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
    return result;
}

internal void V4f32_cross   (V4f32      a, V4f32 b, V4f32 *dest)
{
    return;
}

internal void V4f32_hadamard(V4f32      a, V4f32 b, V4f32 *dest)
{
    V4f32 result = { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
    *dest = result;
    
    return;
}


//~ INTERVAL FUNCTIONS
internal I1f32 I1f32_init      (f32 min, f32 max)
{
    I1f32 result = { min, max };
    if(max < min)
    {
        result.max = min;
        result.min = max;
    }
    
    return result;
}

internal b32   I1f32_overlaps  (I1f32 a, I1f32 b)
{
    b32    result = ((b.min < a.max) && (a.min < b.max));
    return result;
}

internal b32   I1f32_contains  (I1f32 range, f32 position)
{
    b32    result = ((range.max >= position) && (range.min <= position));
    return result;
}

internal f32   I1f32_dimensions(I1f32 range    )
{
    f32    result = (range.max - range.min);
    return result;
}

internal f32   I1f32_center    (I1f32 range    )
{
    f32 result = (range.min + range.max) * 0.5f;
    return result;
}

//-
internal I1u64 I1u64_init      (u64 min, u64 max)
{
    I1u64 result = { min, max };
    if(max < min)
    {
        result.max = min;
        result.min = max;
    }
    
    return result;
}

internal u64   I1u64_dimensions(I1u64 range     )
{
    u64 result = (range.max - range.min);
    return result;
}

internal u64   I1u64_center    (I1u64 range     )
{
    u64 result = (u64)((range.min + range.max) * 0.5);
    return result;
}

//-
internal I2f32 I2f32_init(f32 min_x, f32 min_y, f32 max_x, f32 max_y)
{
    I2f32 result = { min_x, min_y, max_x, max_y};
    if(max_x < min_x)
    {
        result.min.x = max_x;
        result.max.x = min_x;
    }
    if(max_y < min_y)
    {
        result.min.y = max_y;
        result.max.y = min_y;
    }
    
    return result;
}

internal I2f32 I2f32_vec(V2f32 min, V2f32 max)
{
    I2f32 result = { min.x, min.y, max.x, max.y };
    return result;
}


internal I2f32 I2f32_range(I1f32 x, I1f32 y)
{
    I2f32 result = I2f32_init( x.min, y.min, x.max, y.max );
    return result;
}

internal b32   I2f32_overlaps  (I2f32 a, I2f32 b)
{
    b32 result = ((b.x0 < a.x1) && (a.x0 < b.x1) &&
                  (b.y0 < a.y1) && (a.y0 < b.y1));
    return result;
}

internal b32   I2f32_contains  (I2f32 range, V2f32 position)
{
    b32 result = ((range.x0 <= position.x) && (position.x < range.x1) &&
                  (range.y0 <= position.y) && (position.y < range.y1));
    return result;
}

internal V2f32 I2f32_dimensions(I2f32 range    )
{
    V2f32 result = V2f32_init(range.x1 - range.x0,
                              range.y1 - range.y0);
    return result;
}

internal V2f32 I2f32_center    (I2f32 range    )
{
    V2f32 result = { 0 };
    V2f32_scale(0.5f, range.min, &result);
    V2f32_scale(0.5f, range.max, &result);
    
    return result;
}

internal I1f32 I2f32_axis(I2f32 range, Axis axis)
{
    I1f32 result = { range.p[0].v[axis], range.p[1].v[axis] };
    return result;
}

//-
internal I2s32  I2s32_init(s32 min_x, s32 min_y, s32 max_x, s32 max_y)
{
    I2s32 result = { min_x, min_y, max_x, max_y};
    if(max_x < min_x)
    {
        result.min.x = max_x;
        result.max.x = min_x;
    }
    if(max_y < min_y)
    {
        result.min.y = max_y;
        result.max.y = min_y;
    }
    
    return result;
}

internal b32   I2s32_overlaps  (I2s32 a, I2s32 b)
{
    b32 result = ((b.x0 < a.x1) && (a.x0 < b.x1) &&
                  (b.y0 < a.y1) && (a.y0 < b.y1));
    return result;
}

internal b32   I2s32_contains  (I2s32 range, V2s32 position)
{
    b32 result = ((range.x0 <= position.x) && (position.x < range.x1) &&
                  (range.y0 <= position.y) && (position.y < range.y1));
    
    return result;
}

internal V2s32 I2s32_dimensions(I2s32 range     )
{
    V2s32 result = V2s32_init(range.x1 - range.x0,
                              range.y1 - range.y0);
    return result;
}

internal V2s32 I2s32_center    (I2s32 range     )
{
    V2s32 result = { 0 };
    V2s32_scale(0.5f, range.min, &result);
    V2s32_scale(0.5f, range.max, &result);
    
    return result;
}




//~ MATH FUNCTIONS
#include <math.h>


internal f32 f32_sqrt(f32 x)
{
    f32 result = sqrtf(x);
    return result;
}

internal f32 f32_sin (f32 x)
{
    f32 result = sinf(x);
    return result;
}
internal f32 f32_cos (f32 x)
{
    f32 result = cosf(x);
    return result;
}
internal f32 f32_tan (f32 x)
{
    f32 result = tanf(x);
    return result;
}

internal f32 f32_ln(f32 x)
{
    f32 result = logf(x);
    return result;
}

//-
internal f64 f64_sqrt(f64 x)
{
    f64 result = sqrtf(x);
    return result;
}
internal f64 f64_sin (f64 x)
{
    f64 result = sinf(x);
    return result;
}
internal f64 f64_cos (f64 x)
{
    f64 result = cosf(x);
    return result;
}
internal f64 f64_tan (f64 x)
{
    f64 result = tanf(x);
    return result;
}

internal f64 f64_ln(f64 x)
{
    f64 result = log(x);
    return result;
}
//-
internal f32
lerp(f32 a, f32 b, f32 t)
{
    f32 result = a + (b - a) * t;
    
    return result;
}

internal f32
unlerp(f32 a, f32 b, f32 x)
{
    f32 result = 0.0f;
    if(a != b)
    {
        result = (x - a) / (b - a);
    }
    
    return result;
}