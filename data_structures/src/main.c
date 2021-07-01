#include "windows.h"

// C STD Library
#include "stdio.h"

#include "LAL.h"
#include "memory_arena.h"

#include "binary_tree.h" 
#include "hash_table.h"
#include "linked_list.h"
//Algorithms
#include "quick_sort.c"

u32 main(u32 arg_count, u8 *command_line[])
{
    //~ QUICK SORT
    /*
    s32 array[] = { 1, 5, 33, 52, 10, 3, 9, 2, 4, 3 };
    s32 array_len = sizeof(array) / sizeof(array[0]);
        
    //array_print(array, array_len);
    quick_sort(array, array_len, 0, array_len - 1);
    */
    
	//~ BINARY TREE
    
    memory_arena arena;
    LPVOID memory_block = NULLPTR;
    u32    memory_block_size = KILOBYTES(4);
    
    VirtualAlloc(memory_block,
                 memory_block_size,
                 MEM_COMMIT | MEM_RESERVE,
                 PAGE_READWRITE);
    
    
    memory_arena_init(&arena, memory_block_size, memory_block);
    
    Bt_node *bt_root = MEMORY_ARENA_PUSH_STRUCT(memory_block, Bt_node);
    
    binary_tree_init  (bt_root);
    binary_tree_insert(bt_root, 2);
    
    
    //~ HASH TABLES
    
    item items[] = 
    {
        {"foo", 10},
        {"bar", 42},
        {"bazz", 36},
        {"buzz", 7},
        {"bob", 11},
        {"jane", 100},
        {"x", 200}
    };
    
    u32 num_items = sizeof(items[0]) / sizeof(items);
    item* found = linear_search(items, num_items, "bob");
    
    if (!found)
    {
        return 1;
    }
    
    return 0;
}