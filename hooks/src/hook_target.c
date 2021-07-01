#include "LAL.h"

u32 main(u32 arg_count, u8 *command_line[])
{
    u32 a;
    u32 b;
    
    u32 c;
    u32 d;
    
    return 0;
}


u32 hook_me(u32 a, u32 b, u32 c, u32 d)
{
    
    d = a + b;
    b = c + b;
    d = a + b;
    a = a + b;
    d = a + b;
    a = c + b;
    d = d * b;
    b = d + d;
    d = a - b;
    d = d + b;
    b = c + b;
    d = d + b;
    
    
    return a + b + c + d;
}
