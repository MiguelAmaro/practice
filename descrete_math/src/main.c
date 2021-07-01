#include "windows.h"
#include "stdio.h"

#include "LAL.h"

#include "discrete_math.h"

b32 relation_1(u32 x, u32 y)
{
    return (x + 2) == y;
}

u32 main(u32 arg_count, u8 *command_line[])
{
    //~ DISCRETE MATH
    find_pairs_that_are_related(g_A, 5, g_A, 5, relation_1, g_R);
    free(g_R);
    
    //- LOGIC 
    u32 a = 0x1B6;
    u32 b = 0x31D;
    
    u8 bin[32 + (4 * 2) + 4 + 1] = { 0 };
    
    bin[32] = '\0';
    
#if 0
    //u32 offset = ;
    for(u32 i = 0; i < 4; i ++)
    {
        
        for(u32 j = 0; j < 8; j++)
        {
            u32 bit = ((a << (i * j)) & 0x800000);
            
            if(bit == 0)
            {
                bin[(i * j)] = '0';
            }
            else
            {
                bin[(i * j)] = '1';
            }
        }
        
    }
    
    
    printf(bin);
#endif
    
    return 0;
}