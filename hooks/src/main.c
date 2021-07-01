#include "stdio.h"
/*#include "discrete_math.h"
#include "chunk_allocator.h"
#include "binary_tree.h" 
#include "file_parser.h"*/
#include "hash_table.c"
#include "trampoline_jump.c"
#include "quick_sort.c"
#include "windows.h"
#include "LAL.h"

// NOTE(MIGUEL): for the love of god dont put these in the main function...
#define WIN32_EXAMPLE_SELECT (00)
#include "windows_programming/example_switch.h"

//#include "windows_programming/pipes.c"

u32 main(u32 arg_count, u8 *command_line[])
{
    //~ TRAMPOLINE JUMP
    trampoline_jump(arg_count, command_line);

    return 0;
}