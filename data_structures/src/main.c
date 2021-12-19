#include "windows.h"

// C STD Library
#include "stdio.h"

#include "types.h"

#define U32_MAX (0xFFffffff)

#include "binary_tree.h" 
#include "hash_table.h"
#include "linked_list.h"
//Algorithms
#include "quick_sort.c"
#include "memory.h"
#include "disjointsets.h"

u32 main(u32 arg_count, u8 *command_line[])
{
    u32    MemoryBlockSize = KILOBYTES(4);
    LPVOID MemoryBlock     = VirtualAlloc(MemoryBlock,
                                          MemoryBlockSize,
                                          MEM_COMMIT | MEM_RESERVE,
                                          PAGE_READWRITE);
    
    memory_arena Arena;
    MemoryArenaInit(&Arena, MemoryBlockSize, MemoryBlock);
    
    //~ QUICK SORT
#if 0
    s32 array[] = { 1, 5, 33, 52, 10, 3, 9, 2, 4, 3 };
    s32 array_len = sizeof(array) / sizeof(array[0]);
    
    //array_print(array, array_len);
    quick_sort(array, array_len, 0, array_len - 1);
#endif
    
	//~ BINARY TREE
#if 0
    bt_node *BtRoot;
    BinaryTreeInit  (BtRoot, &Arena);
    BinaryTreeInsert(BtRoot, 2, &Arena);
#endif
    //~ DISJOINT SETS
    u32 Edges[][2] = 
    {
        {0, 1}, {0, 2}, {1, 3},
        {4, 8}, {5, 6}, {5, 7},
    };
    
    ds DSet;
    DSet.NodeCount = 10;
    DSet.RelTable = MEMORY_ARENA_PUSH_ARRAY(&Arena, DSet.NodeCount, u32);
    
    DSInit(&DSet, Edges, ARRAY_COUNT(Edges,));
    
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