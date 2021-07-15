

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