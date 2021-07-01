#include "windows.h"
#include "LAL.h"

typedef u32 hooker(u32 a, u32 b, u32 c, u32 d);

u32 hook_me(u32 a, u32 b, u32 c, u32 d)
{
    
    d = a + b;
    b = c + b;
    d = a + b;
    a = a + b;
    d = a + b;
    a = c + b;
    d = d + b;
    b = d + d;
    d = a + b;
    d = d + b;
    b = c + b;
    d = d + b;
    
    
    return a + b + c + d;
}

u32 inserted(u32 a, u32 b, u32 c, u32 d)
{
    b = d + d;
    d = a + b;
    d = d + b;
    b = c + b;
    d = d + b;
    
    return a;
}

u32 trampoline_jump(u32 arg_count, u8 *command_line[])
{
    u32 a = 5;
    u32 b = 8;
    
    u32 c = 10;
    u32 d = 2;
    
    u8 g_string[256];
    
    hooker *func_a = &hook_me ;
    hooker *func_b = &inserted;
    
    wsprintf(g_string, "func A adr: %p | func B adr: %p | offset: %x\n", func_a, func_b, (u64)func_a - (u64)func_b);
    
    OutputDebugString(g_string);
    
    hook_me(a, b, c, d);
    
    return 0;
}
